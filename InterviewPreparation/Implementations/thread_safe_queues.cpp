#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>
#include <optional>

int counter = 0;

void add() {
    for (int i = 0; i < (1 << 8); ++i) {
        counter = counter + 1;  // should cause a data race
    }
}

void write_data(std::atomic<bool> &ready, int &data) {
    data = 42;
    ready.store(true, std::memory_order_release);
}

int read_data_relaxed(const std::atomic<bool> &ready, const int &data) {
    while (!ready.load(std::memory_order_relaxed)) {
        //
    }
    return data;
}

int read_data_acquire(const std::atomic<bool> &ready, const int &data) {
    while (!ready.load(std::memory_order_acquire)) {
        //
    }
    return data;
}

template <typename T>
class LockingQueue {
private:
    std::queue<T> q;
    std::mutex m;
    std::condition_variable cv;

public:
    void push(T val) {
        // takes lock
        std::lock_guard<std::mutex> guard(m);  // just an RAII class that handles mutex locking

        // performs push
        q.push(std::move(val));

        // sends signal to wake exactly one thread that is waiting on the condvar.
        // no predicate is checked on notify_one(), which is why it is a design bug
        // to use one condvar for different threads that are waiting on unrelated predicates.
        cv.notify_one();

        // lock is released when the lock_guard's destructor runs
    }

    T pop() {
        // takes lock.
        // std::unique_lock is basically just a version of std::lock_guard
        // that allows manual locking/unlocking, which is needed for cv.wait().
        std::unique_lock<std::mutex> guard(m);

        // waits until queue is non-empty. (can, in fact, wait forever.)
        // conceptually, in a loop, it:
        // - gives up the lock AND puts the thread to sleep, atomically together
        // - waits until a thread wakeup, either spuriously or by notify_one()/notify_all()
        // - takes lock back
        // when does loop run multiple times? if spurious wakeup,
        // or if woken up but other thread takes data so predicate is false.
        // what is benefit of condvar over manually spinning right here?
        // no CPU time is consumed while thread is asleep.
        cv.wait(guard, [&]() { return !q.empty(); });

        // performs pop
        T val = std::move(q.front());
        q.pop();
        return val;

        // lock is released when the unique_lock's destructor runs
    }
};

template <typename T>
class LockFreeSPSCQueue {
private:
    // need to use circular buffer, as std::queue requires heap allocations.
    // for clarity: the locking queue could also be implemented with a circular buffer.
    size_t capacity;
    std::vector<T> buffer;
    std::atomic<size_t> head = 0;
    std::atomic<size_t> tail = 0;

public:
    explicit LockFreeSPSCQueue(size_t capacity) : capacity(capacity), buffer(capacity) {
        // one slot in the ring buffer is reserved, to distinguish full from empty.
        // it's just specific to this implementation; we could also maintain a size variable.
        assert(capacity >= 2);
    }

    bool push(T val) {
        // checks if full.
        // only use relaxed on tail, because the thread that calls push()
        // is the only thread that writes to tail.
        size_t curr_tail = tail.load(std::memory_order_relaxed);
        size_t next_tail = (curr_tail + 1) % capacity;
        size_t curr_head = head.load(std::memory_order_acquire);
        if (next_tail == curr_head) {
            return false;
        }

        // pushes data
        buffer[curr_tail] = std::move(val);
        tail.store(next_tail, std::memory_order_release);
        return true;
    }

    std::optional<T> pop() {
        // checks if empty
        size_t curr_head = head.load(std::memory_order_relaxed);
        size_t next_head = (curr_head + 1) % capacity;
        size_t curr_tail = tail.load(std::memory_order_acquire);
        if (curr_head == curr_tail) {
            return std::nullopt;
        }

        // pops data
        T val = std::move(buffer[curr_head]);
        head.store(next_head, std::memory_order_release);
        return val;
    }
};

int main() {
    // quick example of multithreading
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < (1 << 8); ++i) {
            std::thread t(add);
            threads.push_back(std::move(t));  // threads are not copyable, just like unique_ptr!
        }
        for (auto &t : threads) {
            // join() blocks calling thread until join()-ed thread finishes.
            // detach() lets the thread keep running until either:
            // (1) its top-level function that it's running completes
            // (2) the process completes (basically, main() finishes execution)
            // std::thread's destructor terminates the whole process (bad!)
            // if neither of those two are called by the time the destructor runs.
            t.join();
        }
        std::cout << "counter = " << counter << std::endl;
        std::cout << std::endl;
    }

    // quick example of memory orderings
    {
        // - compiler can freely reorder instructions, as long as the logic for a SINGLE
        // thread remains functionally unaffected
        // - in addition, writes (to variables) don't happen immediately, but are buffered
        // (in the "store buffer", which is even lower latency than cache or stack or heap),
        // so they can be out of order for that reason too
        // - memory orderings define how atomic operations can be reordered relative to
        // surrounding operations:
        //     - std::memory_order_relaxed: no additional constraints on instruction ordering
        //     - std::memory_order_release: to any thread loading with std::memory_order_acquire
        //     on the same variable, all operations before the store with std::memory_order_release
        //     are correctly seen by that load instruction
        //     - std::memory_order_seq_cst: atomic operations are not reordered relative to
        //     surrounding operations, and this ordering is globally seen by all threads
        //         - this is the default memory ordering

        // using relaxed is bad when a non-atomic variable is flagged by an atomic variable
        std::atomic<bool> ready = false;
        int data = 0;
        std::thread writer(write_data, std::ref(ready), std::ref(data));  // std::ref required to pass references into std::thread
        std::thread reader(read_data_relaxed, std::ref(ready), std::ref(data));
        writer.join();
        reader.join();
        std::cout << "after reading data with std::memory_order_relaxed, data = " << data << std::endl;

        // using release + acquire is correct when a non-atomic variable is flagged by an atomic variable
        ready = false;
        data = 0;
        writer = std::thread(write_data, std::ref(ready), std::ref(data));
        reader = std::thread(read_data_acquire, std::ref(ready), std::ref(data));
        writer.join();
        reader.join();
        std::cout << "after reading data with std::memory_order_acquire, data = " << data << std::endl;
        std::cout << std::endl;
    }

    // locking queue (doesn't matter if SPSC or MPMC,
    // since only one thread can push() or pop() at any given time)
    int operations = 1 << 12;
    {
        LockingQueue<int> queue;
        std::vector<std::thread> threads;
        std::vector<int> results;
        std::mutex results_lock;
        for (int i = 0; i < operations; ++i) {
            threads.push_back(std::thread([&]() {
                queue.push(i);
            }));
            threads.push_back(std::thread([&]() {
                int popped = queue.pop();
                std::lock_guard<std::mutex> guard(results_lock);
                results.push_back(popped);
            }));
        }
        for (auto &thread : threads) thread.join();
        std::cout << "number of pop() results from locking queue = " << results.size() << std::endl;
        std::cout << std::endl;
    }

    // lock-free SPSC queue
    {
        LockFreeSPSCQueue<int> queue(operations * 2);
        std::atomic<int> num_results = 0;
        std::thread pusher([&]() {
            for (int i = 0; i < operations; ++i) {
                queue.push(i);
            }
        });
        std::thread popper([&]() {
            for (int i = 0; i < operations; ++i) {
                if (queue.pop()) {
                    num_results += 1;
                }
            }
        });
        pusher.join();
        popper.join();
        std::cout << "number of pop() results from lock-free SPSC queue = " << num_results << std::endl;
    }

    // TODO: lock-free MPMC queue. the reason it's more complicated is that
    // multiple threads can write to the same variable (head/tail),
    // which causes the classic read-modify-write data race.
}

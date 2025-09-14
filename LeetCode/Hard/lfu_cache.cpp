/*
4: (3, 3, 4)
3: 
2: (4, 4, 2)



4: (3, 3, 4)
2: (4, 4, 2)

- we can store an LRU cache for each frequency
- in the LRU cache problem, we map from each key to a node in a doubly-linked list, which holds both the key and the value; we can probably do something similar here
- we can map from key to a node holding a key, value, and frequency
- we can also map from frequency to the doubly-linked list (which is the LRU cache) for that frequency. either we can just hold the sentinel nodes or make a whole class for a DLL
- we'll also need a doubly-linked list for the frequencies themselves, because then we can easily identify the lowest frequency as the tail of the list
- in addition, we need a map from frequency to the frequency node

- for inserting:
    - if it exists already:
        - find the frequency it's in (from the node)
        - remove it from that frequency list
        - if that frqeuency list is now empty, then delete that frequency
        - update the frequency in the node
        - if the new frequency doesn't have an associated list, create that frequency
        - insert the node into the new list
    - if it doesn't already exist:
        - see if it's at capacity, if so, then delete the LFU-LRU item and reduce size by 1
        - create a new node with this key-value-freq1
        - check if frequency 1 has a DLL, if not, then create one
        - finally, put the node into the frequency 1 list

- to delete:
    - identify the node, based on the key
    - remove the node from the frequency list
    - if that frequency's LRU is now empty, then delete that frequency completely (remove from frequency list and frequency map)
    - remove entry from key_to_node map

- to get:
    - if the key isn't in the key_to_node map, then -1
    - otherwise:
        - get the node from the key_to_node map
        - identify the frequency
        - remove the node from its current frequency
        - if that frequency's list is now empty, remove it
        - update the node's frequency
        - if the new frequency doesn't exist, add it
        - move the node into the front of that new frequency's LRU


- a map from frequency to DLL, where the DLL is literally the LRU cache for taht frequency
- map from key to node in those DLLs
- maintain a DLL of frequencies
- maintain a map from frequency to node in that new DLL
- keep track of the overall size of the LFU cache

review:
- why is it the case that we don't need a DLL for holding the frequencies? why is jsut a single variable enough?
    - well, what do we want to do? we want to always be able to accurately tell what the minimum frequency. when would it change? keep in mind, that if we are updating the frequency for some key, then if it's not the lowest frequency key, then the minimum frequency does not change.
    - suppose we are inserting some new, non-previously-existing key. the new minimum frequency will ALWAYS be 1, regardless of if we evict another key or not.
    - now, suppose we are inserting some existing key (or getting some key, since the frequency-related logic for these two operations is identical), and suppose the frqeuency of that key is equal to the minimum frequency. that frequency will move up, yeah. but if another key still has that frequency? the min freq doesn't change. however, if that's the only key with that frequency, then the new min frequency will always increment by 1.
- what are other frequency-related cases that we DON'T have to consider, and why don't we?
    - the frequency jumping up by more than 1. this won't happen. suppose we have frequencies like [3, 6, 8, 10]. could the min frequency jump up from like 3 to 6? no. why? in the case that the frequency-3 element is removed, it is being removed because we are adding something new into the cache, so the min frequency will be 1.
    - the min frequency decreasing to something other than 1.
    - simply speaking, the only things that can possibly happen to the frequency are that it increments by 1 (because the previously min frqeuency element moves up in frequency) or it gets set to 1 (since a new key is being inserted)
- when to evict the element?
    - in the LRU cache problem, it doesn't matter if you evict it before or after inserting the new element. this is because the newly inserted element will never take the spot of the LRU item, so you can insert something new, then evict the LRU item, and there won't be a bug where you accidentally delete the newly-inserted element.
    - this is not true for LFU cache. you should always evict the LFU item before inserting the new element, so that you don't accidentally insert an element then evict it. why do i say it's not true? suppose you have elements with frequencies (3, 5, 7), and you insert a new element so the frqeuencies are now (1, 3, 5, 7). you then see that it's over capacity and remove the LFU item, but the LFU item is that one with frequency 1, so you end up with the old data structure with frqeuencies (3, 5, 7), and the new item doesn't even get inserted.
- in what cases does this pattern of "use a hashmap to make linked lists more efficient" actually work?
    - primarily for deleting nodes and for inserting to the beginning or end of the list. if you have a pointer to the node (which can be maintained in O(1) with a hashmap), then deletion is O(1) since you can easily access the prev and next.
    - however, if you want to insert into arbitrary positions in the linked list, then you have a problem. to reach some position in a linked list, the worst case is O(n), unless you have a pointer to the node before or after the place where you want to insert.
*/

struct DLLNode {
    int key;
    int val;
    int freq;
    DLLNode *prev;
    DLLNode *next;

    DLLNode(int key, int val, int freq) {
        this->key = key;
        this->val = val;
        this->freq = freq;

        prev = nullptr;
        next = nullptr;
    }
};

struct DLL {
    DLLNode head;
    DLLNode tail;

    DLL() : head(-1, -1, -1), tail(-1, -1, -1) {
        head.next = &tail;
        tail.prev = &head;
    }

    bool is_empty() {
        return head.next == &tail;
    }
};


class LFUCache {
private:
    void insert_node_for_freq(DLLNode *node_ptr, int freq) {
        DLL *dll_ptr = freq_to_lru[freq];
        node_ptr->prev = &(dll_ptr->head);
        node_ptr->next = (dll_ptr->head).next;
        (dll_ptr->head).next->prev = node_ptr;
        (dll_ptr->head).next = node_ptr;
    }

    void increment_frequency(DLLNode *node_ptr) {
        // remove node from old frequency list
        node_ptr->prev->next = node_ptr->next;
        node_ptr->next->prev = node_ptr->prev;

        // if old frequency has an empty LRU list, then remove it
        if (freq_to_lru[node_ptr->freq]->is_empty()) {
            freq_to_lru.erase(node_ptr->freq);
            if (min_freq == node_ptr->freq) {
                min_freq += 1;
            }
        }

        node_ptr->freq += 1;

        // if new frequency doesn't exist, then add it
        if (
            freq_to_lru.find(node_ptr->freq) == freq_to_lru.end()
        ) {
            freq_to_lru[node_ptr->freq] = new DLL();
        }

        insert_node_for_freq(node_ptr, node_ptr->freq);
    }

    void evict() {
        DLL *dll_ptr = freq_to_lru[min_freq];
        DLLNode *evicting = dll_ptr->tail.prev;
        evicting->next->prev = evicting->prev;
        evicting->prev->next = evicting->next;
        size -= 1;
        key_to_node.erase(evicting->key);
    }

public:
    unordered_map<int, DLLNode*> key_to_node;
    unordered_map<int, DLL*> freq_to_lru;
    int size;
    int min_freq;
    int capacity;

    LFUCache(int capacity) {
        this->size = 0;
        this->capacity = capacity;
        this->key_to_node = unordered_map<int, DLLNode*>();
        this->freq_to_lru = unordered_map<int, DLL*>();
        this->min_freq = 0;
    }
    
    int get(int key) {
        if (key_to_node.find(key) == key_to_node.end()) {
            return -1;
        }

        DLLNode *node_ptr = key_to_node[key];
        increment_frequency(node_ptr);
        return node_ptr->val;
    }
    
    void put(int key, int value) {
        if (key_to_node.find(key) != key_to_node.end()) {
            DLLNode *node_ptr = key_to_node[key];
            increment_frequency(node_ptr);
            node_ptr->val = value;
        } else {
            if (size == capacity) {
                this->evict();
            }

            min_freq = 1;
            size += 1;
            
            if (freq_to_lru.find(1) == freq_to_lru.end()) {
                freq_to_lru[1] = new DLL();
            }

            DLLNode *node = new DLLNode(key, value, 1);
            key_to_node[key] = node;
            insert_node_for_freq(node, 1);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

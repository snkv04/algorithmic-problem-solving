/*
- why use a doubly-linked list? a regular list has O(1) access but O(n) insert/remove. a doubly-linked list has O(n) access but has O(1) insert/remove. if we already have direct access to the node, then the O(n) access doesn't matter. also, we use a doubly-linked list instead of a singly-linked list because in order to remove any links to a node when removing the node, we need to have access to the node before it, which is O(1) with a doubly-linked list but O(n) with a singly-linked list.
- why use a hashmap? it gives direct access to nodes in the doubly-linked list. put simply, what it does is change the O(n) bottleneck of doubly-linked lists into O(1) access.
- why do the close gaps logic? it's just how you remove nodes from doubly-linked lists.
- why always insert nodes at the beginning of the list? in an example test case, we can simulate the recency of each item by putting all the items in a list. whenever we want to consider an item as extremely recent (more recent than all of the other items), then in this visualization, we move it from wherever it was (such as if there were 3 items used after it, then it would be the fourth in the list) to the beginning of the list, because this means that it is now more recent than any other item
- why have pointers to the next and previous nodes instead of directly having their objects? it's just the standard way of having references to other objects in C++. it allows for constant-size references, which is efficient in terms of memory.
- what's at the core of an LRU cache? why can it be modeled by a list? the core of an LRU cache is the mapping between keys and values, so that we can lookup the value for a given key, and if the size of the cache gets to be too large, then the mapping that we remove is the one that was the least recently used. it can be modeled by a list because what we are effectively doing, by modeling it as a list, is conveying each mapping's recency through its index in the list.
- why insert and then check for capacity? why not check for capacity first? this is a little involved. there are two cases when we insert: either it's there already or it isn't. if it is, then the size of the cache doesn't change, whereas if it isn't, then the size of the cache does increase by 1. if we check for capacity first, then we'd have to add the additional condition of seeing if the key isn't already there (because if it is, then the size of the cache won't change, but the items will be moved around). this can be generalized into a more simple design pattern. if some condition has to be maintained (in this case, the max size of the cache), instead of checking before any operation if that operation might cause the condition to no longer be satisfied, which could cause some complicated logic, just try running the operation first and then alleviate any issues with the condition afterward.
*/

struct Node {
public:
    int key;
    int value;
    Node *prev;
    Node *next;

    Node(int key, int value) {
        this->key = key;
        this->value = value;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

class LRUCache {
public:
    Node *head;
    Node *tail;
    unordered_map<int, Node*> key_to_node;
    int capacity;

    LRUCache(int capacity) {
        this->head = new Node(-1, -1);
        this->tail = new Node(-1, -1);
        this->head->next = this->tail;
        this->tail->prev = this->head;
        this->key_to_node = unordered_map<int, Node*>();
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (key_to_node.find(key) == key_to_node.end()) {
            return -1;
        }

        // [s, (7,9), (3,5), (1,2), s]

        // move node to front
        Node *node = key_to_node[key];
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;

        return node->value;
    }
    
    void put(int key, int value) {
        /*
        if key-value mapping exists:
            remove the node from the list
            update the value
            insert it at the front
            set up a mapping [...]
        else:
            make a new node for it
            put it at the front
            set up a mapping in the key_to_node map

        flush out the least-recently-used if necessary
        */
        Node *node;
        if (key_to_node.find(key) != key_to_node.end()) {
            node = key_to_node[key];
            node->prev->next = node->next;
            node->next->prev = node->prev;
        } else {
            node = new Node(key, -1);
        }
        node->value = value;

        // insert the node at the beginning
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;

        // add or update the mapping from key to node
        key_to_node[key] = node;

        // evict least recently used
        if (key_to_node.size() > this->capacity) {
            // remove the last node
            Node *evicting = tail->prev;
            evicting->prev->next = tail;
            tail->prev = evicting->prev;

            // remove the entry for that node
            int evicted_key = evicting->key;
            key_to_node.erase(evicted_key);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

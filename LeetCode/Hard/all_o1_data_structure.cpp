struct DLLNode {
    int val;
    DLLNode *next;
    DLLNode *prev;

    DLLNode(int val) : val(val) {}
};

struct DLL {
    DLLNode head;
    DLLNode tail;

    DLL() : head(DLLNode(-1e9)), tail(DLLNode(1e9)) {
        head.next = &tail;
        tail.prev = &head;
    }

    bool isEmpty() {
        return head.next == &tail;
    }
};

class AllOne {
    /*
    - mapping from freq to DLL node for that freq
    - mapping from freq to set of strings
    - DLL of frequencies. can tell if no words if head->next is &tail
    - map from word to frequencies

    - when incrementing, a few different cases:
        - the word doesn't exist, so then we want to set its freq to 1:
            - freq 1 already exists: place string into freq 1
            - freq 1 doesn't exist:
                - make node in list
                - map freq to that freq node
        - the word exists:
            - it's the last one of its frequency:
                - if there is a next node and its the next frequency,
                delete current node and insert string into next node
                - if there isn't a node for next frequency, update current
                node to have next frequency
            - there are other words of that frequency:
                - if there is a node for next frequency, remove string from
                current node and add it to the next node
                - if there isn't, remove the string from the current node
                and make a new next node

    - when decrementing, a few different cases:
        - its frequency is 1:
            - it's the last word with freq 1: just delete the node, the
            frequency, and the word
            - it's not the last word with freq 1: just delete the word
        - its frequency isn't 1:
            - the analogue of all the others

    - for getting max or min key, just O(1) look at the DLL

    - the operations we need directly inform what data structures we need:
        - for a word, get its freq in O(1): map from word to freq
        - for a freq, get the words in O(1): map from freq to words
        - for a freq, insert and remove a word in O(1): the words for a freq
        should be a set, not a list
        - for a freq, update the words for that freq, the next freq, or
        the prev freq in O(1): put the frequencies into a DLL (one variable),
        and map from freq to the node in the DLL (another variable)
    */

private:
    DLL freqs;
    unordered_map<int, DLLNode*> freq_to_node;
    unordered_map<int, unordered_set<string>> freq_to_keys;
    unordered_map<string, int> key_to_freq;

public:
    AllOne() {
        // do nothing, everything is default-initialized
    }

    void _updateFrequency(string key, bool up) {
        // get the frequency and node for this key
        int frequency = key_to_freq[key];
        DLLNode *node = freq_to_node[frequency];

        // compute the next frequency and the frequency of the adjacent node
        int adjacent_freq = up
            ? freq_to_node[frequency]->next->val
            : freq_to_node[frequency]->prev->val;
        int new_freq = up ? (frequency + 1) : (frequency - 1);

        if (freq_to_keys[frequency].size() == 1) {
            // we move the key into the next frequency
            freq_to_keys.erase(frequency);
            freq_to_keys[new_freq].insert(key);
            key_to_freq[key] = new_freq;

            if (adjacent_freq == new_freq) {
                // delete this node
                node->next->prev = node->prev;
                node->prev->next = node->next;
                freq_to_node.erase(frequency);
            } else {
                // we just update this node to have a new frequency
                node->val = new_freq;
                freq_to_node.erase(frequency);
                freq_to_node[new_freq] = node;
            }
        } else {
            freq_to_keys[frequency].erase(key);
            freq_to_keys[new_freq].insert(key);
            key_to_freq[key] = new_freq;

            if (adjacent_freq == new_freq) {
                // do nothing
            } else {
                // make a new node for the new frequency
                DLLNode *left_node, *right_node;
                if (up) {
                    left_node = node;
                    right_node = node->next;
                } else {
                    left_node = node->prev;
                    right_node = node;
                }

                DLLNode *new_node = new DLLNode(new_freq);
                new_node->next = right_node;
                new_node->prev = left_node;
                right_node->prev = new_node;
                left_node->next = new_node;
                freq_to_node[new_freq] = new_node;
            }
        }
    }
    
    void inc(string key) {
        if (key_to_freq.find(key) == key_to_freq.end()) {
            // if needed, add a new node for the frequency 1
            if (freq_to_node.find(1) == freq_to_node.end()) {
                DLLNode *node = new DLLNode(1);
                node->next = freqs.head.next;
                node->prev = &(freqs.head);
                freqs.head.next->prev = node;
                freqs.head.next = node;
                freq_to_node[1] = node;
            }

            // match the key and frequency 1 to each other
            freq_to_keys[1].insert(key);
            key_to_freq[key] = 1;
        } else {
            _updateFrequency(key, true);
        }
    }
    
    void dec(string key) {
        if (key_to_freq[key] == 1) {
            if (freq_to_keys[1].size() == 1) {
                freq_to_keys.erase(1);

                DLLNode *node = freq_to_node[1];
                node->prev->next = node->next;
                node->next->prev = node->prev;
                freq_to_node.erase(1);
            } else {
                freq_to_keys[1].erase(key);
            }

            key_to_freq.erase(key);
        } else {
            _updateFrequency(key, false);
        }
    }
    
    string getMaxKey() {
        if (freqs.isEmpty()) {
            return "";
        }

        int max_freq = freqs.tail.prev->val;
        return *(freq_to_keys[max_freq].begin());
    }
    
    string getMinKey() {
        if (freqs.isEmpty()) {
            return "";
        }

        int min_freq = freqs.head.next->val;
        return *(freq_to_keys[min_freq].begin());
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

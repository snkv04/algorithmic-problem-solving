class Solution {
private:
    class Multiset {
    public:
        unordered_map<string, int> mp;

        void add(string s) {
            ++mp[s];
        }

        void remove(string s) {
            --mp[s];
            if (!mp[s]) mp.erase(s);
        }
    };

public:
    vector<int> findSubstring(string s, vector<string>& words) {
        /*
        - we know the window size is going to be the size of all of the
        words combined, or n * k if n is the number of words and k is the
        size of each word. so, we can just do a sliding window across the
        string.
        - however, we can't just directly check if each sliding window is a
        permutation of the words. how would that be done? would we iterate
        through all permutations of the words and check if it's equal to the
        substring made by the window? instead, what we actually want to do
        is check to see that the window contains all the words in the given
        word set. we can just check with a multiset comparison. for each
        window, we hold a multiset of all the words, and do a comparison with
        the actual multiset of words we are given. if it's equivalent, then
        the start index of the window gets added to the answer.
        - two caveats:
            - we can't just directly slide the window over the string. shifting
            over the characters for each window reconstruction would be way too
            slow. that would be O((n * k) * s.size()), or the size of the
            window times every possible window location. instead, note that
            since each word is the same size (let's assume that it's always
            30), if we were to move the window over by the words' size each
            time, then we can simply worry about only appending the word
            on the right and removing the word on the left each hop. also,
            there are 30 different possible start locations, so we just have
            to check each. (think of it like if two different windows' start
            indices are congruent mod 30, then they will be covered in the
            same pass, i.e. the pass with the same starting location in the
            interval [0, 29].) by making sure that we hop by 30 each time, we
            only have to consider the word at the start and end of the window,
            and by covering all start locations, we still cover every possible
            window. the time complexity would then be O(k * s.size()), which
            is much more manageable, because k is small.
            - for comparing multisets, if we were to compare the full
            multiset each window, then that could be as bad as checking 5000
            items for each of approximately 10^4 windows, which is too slow.
            however, note that on each hop of the window, we only change up
            to 2 items in the multiset corresponding to the window. if we
            keep track of a set stating which elements of the window are
            ALREADY equal to the corresponding elements in the original word
            set (based on frequency count), then we only have to update up to
            2 elements in that set for each hop of the window. this is much
            more manageable (it's like lazy updates), and for checking if
            the "equal" set has everything equal to the original word set,
            we just check to see if its size is equal to the number of
            distinct elements in the original word set.
        */
        
        Multiset original;
        for (string word : words) original.add(word);

        int n = words.size(), k = words[0].size();
        vector<int> ans;
        for (int mod = 0; mod < k; ++mod) {
            int mod_end = mod + n * k;
            if (mod_end > s.size()) break;

            Multiset current;
            unordered_set<string> equal;
            int start = mod, end = mod_end;
            for (int j = start; j < end; j += k) {
                string substr = s.substr(j, k);
                current.add(substr);

                if (
                    original.mp.find(substr) != original.mp.end() &&
                    original.mp[substr] == current.mp[substr]
                ) {
                    equal.insert(substr);
                } else {
                    equal.erase(substr);
                }
            }
            if (equal.size() == original.mp.size()) {
                ans.push_back(mod);
            }

            while (end + k <= s.size()) {
                string removing = s.substr(start, k), adding = s.substr(end, k);
                start += k;
                end += k;
                current.add(adding);
                current.remove(removing);

                if (
                    original.mp.find(adding) != original.mp.end() &&
                    original.mp[adding] == current.mp[adding]
                ) {
                    equal.insert(adding);
                } else {
                    equal.erase(adding);
                }
                if (
                    original.mp.find(removing) != original.mp.end() &&
                    original.mp[removing] == current.mp[removing]
                ) {
                    equal.insert(removing);
                } else {
                    equal.erase(removing);
                }

                if (equal.size() == original.mp.size()) {
                    ans.push_back(start);
                }
            }
        }
        return ans;
    }
};

class Solution {
private:
    int get_val(vector<int> &arr, int idx) {
        if (idx < 0) {
            return -1e9;
        } else if (idx >= arr.size()) {
            return 1e9;
        } else {
            return arr[idx];
        }
    };

    int get_count_from_first(int k, vector<int> &arr1, vector<int> &arr2) {
        int l = 0, r = arr1.size(), num_from_1 = -1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            int i1 = m - 1, i2 = k - m - 1;

            if (
                max(get_val(arr1, i1), get_val(arr2, i2)) <=
                min(get_val(arr1, i1+1), get_val(arr2, i2+1))
            ) {
                num_from_1 = m;
                break;
            } else if (get_val(arr1, i1) > get_val(arr2, i2)) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return num_from_1;
    }

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        /*
        - if total_nums = nums1.size() + nums2.size(), then the median
        can be defined as the total_nums/2+1'th smallest element among the
        merged arrays if total_nums is odd, and the average of the
        total_nums/2'th smallest element and the total_nums/2+1'th smallest
        element if total_nums is even.
        - alright, we can abstract that away into getting the k'th smallest
        element in the two arrays. how can we do that? first, observe that
        if we know that we're going to take x elements from the first array,
        then we need to take k-x elements from the second array, and those
        two together will constitute the k'th smallest elements from both
        arrays when merging. so we can just binary search on one array, as
        the index in the other array will be fixed.
            - as a side note, why do we only binary search on the smaller
            array? it will always be possible to get all of the elements from
            the larger array and none from the smaller array, but it isn't
            always possible to get all the elements from the smaller array
            (because that might not be enough to retrieve total_nums/2
            total elements). so, the range of values that we would have to
            binary search over if we were to binary search over the number
            of elements taken from the larger array would simply be less clean,
            that's all.
        - now, how does the binary search work? think about what we're really
        trying to do here, in terms of a brute-force approach. we want to merge
        the two arrays, and then take the k'th smallest element. the merged
        array is SORTED. if we look at the length-k prefix of that merged array,
        some elements come from arr1 and some come from arr2. let's look at a
        prefix of arr1 and a prefix of arr2. for those two to combine to be
        a valid prefix of the merged array, the prefixes must have all of their
        elements of the corresponding suffixes. and that's exactly what we're
        checking with this binary search. for a given selection of prefix from
        arr1 and prefix from arr2, we already fixed the length sum, so we just
        care if it's a valid prefix of the merged array. we already know that
        the prefixes and suffixes are sorted on their own, so we simply check
        to see that the prefixes are squarely to the left of the suffixes by
        seeing if the max of the last element of the two prefixes is leq the
        min of the first element of the two suffixes. if it is, then we've
        found the point at which we can "merge" the arrays, ensuring that the
        combined prefix is of length k. if arr1's prefix's last element is >
        the first element of arr2's suffix (we don't have to check its relation
        to arr1's suffix), then we have too many elements from arr1, so we move
        arr1's pointer left. otherwise, we move the pointer right.
            - keep in mind, this is more similar to the conventional idea of
            binary search (check if it's on the right place, if it's to the left,
            and if it's to the right) rather than binary search on a monotonic
            function (we want to find the first/last true value, so we check
            if a function returns true or false, and move left/right accordingly).
            in general, i should keep in mind that it's useful to consider which 
            of the two styles i should go with.
        - also, to deal with edge cases, it's relatively simple. we are checking
        if the max of two sorted prefixes is <= the min of two sorted suffixes.
        if any of these four entities are empty, we can replace it with infinity
        or negative infinity, and then the min or max will work properly.
        - one slight optimization: in the case that the total count of elements
        is even, then we want to get the k'th smallest element and (k+1)'th
        smallest element (where k = total_nums/2). instead of doing a binary
        search twice, just do it once, and then get the minimum element from the
        merged suffix (i.e., the minimum element from the two suffixes of the
        two arrays).
        */

        vector<int> arr1 = nums1, arr2 = nums2;
        if (arr1.size() > arr2.size()) {
            swap(arr1, arr2);
        }

        int total_elems = arr1.size() + arr2.size();
        int mid = (total_elems + 1) / 2;
        int count_from_first = get_count_from_first(mid, arr1, arr2);
        if (total_elems % 2) {
            return max(
                get_val(arr1, count_from_first - 1),
                get_val(arr2, mid - count_from_first - 1)
            );
        } else {
            return (
                max(
                    get_val(arr1, count_from_first - 1),
                    get_val(arr2, mid - count_from_first - 1)
                ) + min(
                    get_val(arr1, count_from_first),
                    get_val(arr2, mid - count_from_first)
                )
            ) / 2.0;
        }
    }
};

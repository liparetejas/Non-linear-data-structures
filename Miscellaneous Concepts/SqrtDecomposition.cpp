/*
    https://leetcode.com/problems/number-of-pairs-after-increment/solutions/

    https://www.youtube.com/watch?v=ZakhE_eaonY ( sqrt decompostion explained)

Problem: Number of Pairs After Increment

    Concept: SQRT Decomposition
    --------------------------------

    SQRT decomposition is a technique where we divide an array into blocks.

    If the array size is n, we usually choose:

        blockSize = sqrt(n)

    So instead of treating the whole array as one large array, we split it like this:

        nums2 = [a0, a1, a2, a3, a4, a5, a6, a7, a8]

    If blockSize = 3:

        Block 0: [a0, a1, a2]
        Block 1: [a3, a4, a5]
        Block 2: [a6, a7, a8]

    For any index i:

        block number = i / blockSize


    Why this helps:
    ---------------

    In this problem, we need to support two operations:

        1. Add val to nums2[l...r]
        2. Count pairs where nums1[i] + nums2[j] == total

    nums1 is very small, but nums2 can be large.

    For pair counting:

        nums1[i] + nums2[j] == total

    means:

        nums2[j] == total - nums1[i]

    So for every value in nums1, we only need to count how many times
    a target value appears in nums2.


    What each block stores:
    -----------------------

    For every block, we store a frequency map:

        freq[block][value] = count of value in this block

    We also store a lazy value:

        lazy[block] = value added to the whole block

    If an entire block is updated by +val, we do not update every element.
    We simply do:

        lazy[block] += val

    This is called lazy update.


    Important formula:
    ------------------

    nums[i] stores the base value.
    lazy[i / blockSize] stores the extra value added to its block.

    So the real current value is:

        nums[i] + lazy[i / blockSize]


    Query logic:
    ------------

    Suppose we want to count how many values are equal to target.

    In block b:

        real value = base value + lazy[b]

    We want:

        base value + lazy[b] == target

    So:

        base value == target - lazy[b]

    Therefore, in each block, we search:

        freq[b][target - lazy[b]]

    But we use find() instead of operator[] so that missing keys are not inserted.


    Complexity:
    -----------

    Range update:
        O(sqrt(n)) approximately

    Count query:
        O(nums1.size() * number_of_blocks)
        Since nums1.size() <= 5, this is also about O(sqrt(n)).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int blockSize;
    int blocks;

    vector<long long> nums;                       // base values of nums2
    vector<long long> lazy;                       // lazy addition for each block
    vector<unordered_map<long long, int>> freq;   // frequency map for each block

    void removeValue(int block, long long value) {
        freq[block][value]--;

        if (freq[block][value] == 0) {
            freq[block].erase(value);
        }
    }

    void updateOne(int index, long long val) {
        int block = index / blockSize;

        removeValue(block, nums[index]);
        nums[index] += val;
        freq[block][nums[index]]++;
    }

    void updateRange(int left, int right, long long val) {
        // If the range is small, update directly.
        if (right - left + 1 <= 2 * blockSize) {
            for (int i = left; i <= right; i++) {
                updateOne(i, val);
            }
            return;
        }

        // Update left partial block manually until left reaches block start.
        while (left % blockSize != 0) {
            updateOne(left, val);
            left++;
        }

        // Update right partial block manually until right reaches block end.
        while (right % blockSize != blockSize - 1) {
            updateOne(right, val);
            right--;
        }

        // Now all remaining blocks are complete blocks, so update lazily.
        while (left <= right) {
            int block = left / blockSize;
            lazy[block] += val;
            left += blockSize;
        }
    }

    int countValue(long long target) {
        int count = 0;

        for (int block = 0; block < blocks; block++) {
            long long neededBaseValue = target - lazy[block];

            auto it = freq[block].find(neededBaseValue);
            if (it != freq[block].end()) {
                count += it->second;
            }
        }

        return count;
    }

    vector<int> numberOfPairs(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums2.size();

        blockSize = sqrt(n);
        if (blockSize == 0) {
            blockSize = 1;
        }

        blocks = (n + blockSize - 1) / blockSize;

        nums.assign(n, 0);
        lazy.assign(blocks, 0);

        freq.clear();
        freq.resize(blocks);

        for (int i = 0; i < n; i++) {
            nums[i] = nums2[i];
            freq[i / blockSize][nums[i]]++;
        }

        vector<int> answer;

        for (auto& query : queries) {
            if (query[0] == 1) {
                int left = query[1];
                int right = query[2];
                long long val = query[3];

                updateRange(left, right, val);
            } else {
                long long total = query[1];
                int pairs = 0;

                for (int x : nums1) {
                    pairs += countValue(total - x);
                }

                answer.push_back(pairs);
            }
        }

        return answer;
    }
};

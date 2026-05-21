/*
https://leetcode.com/problems/next-permutation/

We want to rearrange the array to form the next greater permutation. If that's not possible
(i.e., it's the last permutation), we return the smallest one (i.e., sorted ascendingly).

To find this next permutation with minimal change, we need to find a digit that can be
increased slightly to make the number bigger and then rearrange the remaining part to be the
smallest possible.

- Traverse from the end and find the first index where the current digit is smaller than the
  next one (this is the "breaking point").
- Then again traverse from the end to find the first digit greater than the breaking point
  digit and swap them.
- Finally, reverse the part of the array to the right of the breaking point to get the
  smallest next permutation.
- If no such breaking point exists (entire array is descending), just reverse the whole array.

*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int firstSmaller = -1;
        int n = nums.size();
        for(int i = n - 2; i >= 0; i--) {
            if(nums[i] < nums[i + 1]) {
                firstSmaller = i;
                break;
            }
        }
        if(firstSmaller == -1) {
            // Last permutation
            reverse(nums.begin(), nums.end());
            return;
        }
        // Swap the firstSmaller with an element that is just greater than it
        for(int i = n - 1; i > firstSmaller; i--) {
            if(nums[i] > nums[firstSmaller]) {
                swap(nums[i], nums[firstSmaller]);
                break;
            }
        }
        reverse(nums.begin() + firstSmaller + 1, nums.end());
    }
};
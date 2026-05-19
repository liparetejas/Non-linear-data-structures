/*

https://leetcode.com/problems/smallest-unique-subarray/

Rolling Hash Logic

The idea of rolling hash is to represent every subarray of fixed length `l`
as a single numeric value called a hash.

Instead of comparing two subarrays element by element, we compare their hash
values. This makes checking subarrays much faster.

For a subarray:

    nums[i], nums[i + 1], nums[i + 2], ..., nums[i + l - 1]

we calculate its hash like this:

    hash = nums[i] * base^(l - 1)
         + nums[i + 1] * base^(l - 2)
         + nums[i + 2] * base^(l - 3)
         + ...
         + nums[i + l - 1]

This is similar to how a number is formed in decimal.

Example:

    123 = ((1 * 10 + 2) * 10 + 3)

Similarly, we build the hash like this:

    hash = 0;

    for (int i = 0; i < l; i++) {
        hash = (hash * base + nums[i]) % mod;
    }

Here:
    base = some large number
    mod  = large prime number

We use modulo because the hash value can become very large.


Rolling the hash:

Suppose we already have the hash of:

    nums[i], nums[i + 1], ..., nums[i + l - 1]

Now we want the hash of the next subarray:

    nums[i + 1], nums[i + 2], ..., nums[i + l]

Instead of recalculating everything, we update the hash in O(1).

The first element nums[i] is leaving the window.
Its contribution was:

    nums[i] * base^(l - 1)

So we remove it:

    hash = hash - nums[i] * base^(l - 1)

Then we shift the remaining elements by multiplying with base:

    hash = hash * base

Then we add the new element nums[i + l]:

    hash = hash + nums[i + l]

With modulo, this becomes:

    remove = nums[i] * power[l - 1] % mod;

    hash = (hash - remove + mod) % mod;
    hash = (hash * base + nums[i + l]) % mod;

The `+ mod` is added before taking `% mod` because subtraction can make
the hash negative.


Example:

Current subarray:

    [3, 5, 7]

Hash:

    3 * base^2 + 5 * base + 7

Next subarray:

    [5, 7, 2]

Remove 3 * base^2:

    5 * base + 7

Multiply by base:

    5 * base^2 + 7 * base

Add 2:

    5 * base^2 + 7 * base + 2

So now we have the hash of [5, 7, 2].


How it is used in this problem:

For a fixed length `l`, we compute the hash of every subarray of length `l`.

For each hash, we store its frequency:

    unordered_map<long long, int> mp;

    mp[hash]++;

After processing all subarrays of length `l`, if any hash appears exactly once,
then there exists a unique subarray of length `l`.

So:

    check(l) == true

means there is at least one unique subarray of length `l`.


Why binary search works:

If there is a unique subarray of length `l`, then there will also be a unique
subarray for some larger length.

So the answer pattern looks like:

    false false false true true true

Because of this monotonic behavior, we can binary search for the smallest
length where check(l) is true.


Overall:

    1. Choose a length l.
    2. Use rolling hash to calculate hashes of all subarrays of length l.
    3. Count the frequency of each hash.
    4. If any hash appears once, length l is valid.
    5. Binary search to find the smallest valid length.

Time complexity of each check(l):

    O(n)

because every subarray hash is calculated in constant time after the first one.

Note:
    This implementation uses single modulo hashing.
    Hash collisions are theoretically possible, but rare with a good base and mod.
    Double hashing can be used to reduce collision risk further.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool check(int l, vector<int>& nums) {
        int n = nums.size();

        long long hash = 0;
        long long base = 100001;
        long long mod = 1000000007;

        vector<long long> power(l + 1, 1);

        for (int i = 1; i <= l; i++) {
            power[i] = (power[i - 1] * base) % mod;
        }

        unordered_map<long long, int> mp;

        // Hash of first subarray of length l
        for (int i = 0; i < l; i++) {
            hash = (hash * base + nums[i]) % mod;
        }

        mp[hash]++;

        // Rolling hash for remaining subarrays of length l
        for (int i = l; i < n; i++) {
            long long remove = (power[l - 1] * nums[i - l]) % mod;

            hash = (hash - remove + mod) % mod;
            hash = (hash * base + nums[i]) % mod;

            mp[hash]++;
        }

        // If any hash appears only once,
        // then a unique subarray of length l exists
        for (auto& it : mp) {
            if (it.second == 1) {
                return true;
            }
        }

        return false;
    }

    int smallestUniqueSubarray(vector<int>& nums) {
        int i = 1;
        int j = nums.size();
        int ans = j;

        while (i <= j) {
            int mid = i + (j - i) / 2;

            if (check(mid, nums)) {
                ans = mid;
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 3, 2, 1};

    int answer = sol.smallestUniqueSubarray(nums);

    cout << "Smallest unique subarray length: " << answer << endl;

    return 0;
}
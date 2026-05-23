/*
https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/

KMP Algorithm

Goal:
    Find the first index where `needle` appears in `haystack`.

Why KMP:
    In brute force, we may compare the same characters again.
    KMP avoids this using the LPS array.

LPS:
    lps[i] = length of the longest proper prefix of needle[0...i]
             which is also a suffix.

Example:

    needle = "ababaca"

    char:  a b a b a c a
    lps:   0 0 1 2 3 0 1

Meaning:
    At each mismatch, LPS tells us where to continue in the needle.

Main rule:

    If mismatch happens at needle[j]:

        j = lps[j - 1]

    This avoids starting from index 0 again.

Steps:
    1. Build LPS array for needle.
    2. Match haystack and needle using two pointers.
    3. On mismatch, use LPS to shift needle.
    4. Return index if full needle is matched.

Time:
    O(n + m)

Space:
    O(m)
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> buildLPS(string& needle) {
        int m = needle.size();

        vector<int> lps(m, 0);

        int len = 0;
        int i = 1;

        while (i < m) {
            if (needle[i] == needle[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        return lps;
    }

    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();

        if (m == 0) {
            return 0;
        }

        vector<int> lps = buildLPS(needle);

        int i = 0; // pointer for haystack
        int j = 0; // pointer for needle

        while (i < n) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }

            if (j == m) {
                return i - j;
            }

            if (i < n && haystack[i] != needle[j]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;

    string haystack = "sadbutsad";
    string needle = "sad";

    int answer = sol.strStr(haystack, needle);

    cout << "First occurrence index: " << answer << endl;

    return 0;
}
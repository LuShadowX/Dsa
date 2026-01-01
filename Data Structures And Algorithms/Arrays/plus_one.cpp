/**
 * @file plus_one.cpp
 * @author LuShadowX
 * @brief Increment a large integer represented as an integer array.
 * @problem_link: https://leetcode.com/problems/plus-one/
 * @difficulty: Rank B (Fundamental Array Logic)
 * @logic: Backward traversal with carry propagation. 
 * If a digit is 9, it becomes 0 and the carry moves left.
 */

#include <iostream>
using namespace std;

class Solution {
public:
    /**
     * Increment the large integer by one.
     * Time Complexity: O(N) - Single pass through the digits.
     * Space Complexity: O(1) - Modification happens in-place (unless overflow occurs).
     */
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();

        // Step 1: Traverse the array from right to left
        for (int i = n - 1; i >= 0; i--) {
            // Case 1: Current digit is less than 9
            if (digits[i] < 9) {
                digits[i]++; // Increment and return immediately
                return digits;
            }
            
            // Case 2: Current digit is 9
            digits[i] = 0; // Set to 0 and let the loop continue (carry propagates)
        }

        // Step 3: Handle the 'All Nines' case (e.g., [9, 9, 9] -> [1, 0, 0, 0])
        // If the loop finished, it means we have a carry that reached the front.
        digits.insert(digits.begin(), 1); 
        
        return digits;
    }
};

// --- TEST BENCH ---
int main() {
    Solution sol;
    
    // Test Case: Overflow handling
    vector<int> test = {9, 9, 9};
    vector<int> result = sol.plusOne(test);

    cout << "INCREMENT RESULT: ";
    for (int d : result) {
        cout << d << " ";
    }
    cout << endl;

    return 0;
}
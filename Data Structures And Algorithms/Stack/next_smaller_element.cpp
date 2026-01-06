/**
 * @file next_smaller_element.cpp
 * @author LuShadowX
 * @brief Find the Next Smaller Element (NSE) for every element in an array.
 * @problem_link: https://www.geeksforgeeks.org/problems/next-smaller-element/1
 * @difficulty: Medium (Rank B)
 * @tags: Stack, Monotonic Stack, Array
 * @logic: Utilizes a Monotonic Increasing Stack approach.
 * 1. Initialize a result vector `arry` with -1.
 * 2. Use a stack `st` to store **indices** of elements. The stack will be maintained
 * such that the values `arr[st.top()]` are in non-decreasing order.
 * 3. Iterate through the array with index `i`.
 * 4. For the current element `arr[i]`:
 * a. While the stack is not empty AND `arr[i]` is SMALLER than the element
 * at the top index of the stack (`arr[st.top()]`):
 * i. We found the NSE for `arr[st.top()]`. It is `arr[i]`.
 * ii. Update the result array: `arry[st.top()] = arr[i]`.
 * iii. Pop the stack.
 * b. Push the current index `i` onto the stack to find its NSE later.
 * 5. Return the result vector.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Monotonic Stack Principle]
 * A monotonic stack is a data structure where elements are stored in a specific
 * sorted order (either non-increasing or non-decreasing).
 *
 * For the "Next Smaller Element" problem, we use an **increasing stack** of indices.
 * We are looking for the *first* element to the right that is smaller.
 *
 * - Why store indices? We need to update the result for a specific position.
 * - Why increasing? When we encounter a new element `X`, we compare it with
 * the top of the stack. If `X` is smaller, it is the NSE for the top element.
 * Because the stack is increasing, `X` might also be the NSE for the element
 * below the top, and so on. The `while` loop resolves these.
 * - What's left? Elements remaining in the stack at the end never found a smaller
 * element to their right. Their result remains `-1` as initialized.
 *
 * [Time Complexity Analysis]
 * We iterate through the array of size N once. Each index is pushed onto the
 * stack exactly once and popped at most once. All stack operations are O(1).
 * Total Time: T(N) = O(N).
 *
 * [Space Complexity Analysis]
 * We use a stack that can hold at most N indices (in the worst case of a sorted
 * array, e.g., [1, 2, 3, 4, 5], all indices are pushed).
 * Total Auxiliary Space: S(N) = O(N).
 * ============================================================================
 */

/**
 * MISSION: Next Smaller Element Protocol
 * RANK: B (Standard Monotonic Stack Application)
 * DEPARTMENT: Linear Data Structures & Pattern Matching
 * CHALLENGE:
 * Given an array `arr[0..N-1]` of integers, find the nearest smaller element to
 * the right for every element. If there is no smaller element to the right, the
 * result should be -1 for that element.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(N) allowed.
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    /**
     * Finds the next smaller element for each element in the array.
     * @param arr The input integer vector.
     * @return A vector containing the NSE for each position, or -1 if none exists.
     */
    vector<int> nextSmallerEle(vector<int>& arr) {
        // Stack stores indices, maintaining increasing order of values at those indices.
        stack<int> st;
        // Initialize result array with -1.
        vector<int> arry(arr.size(), -1);

        for (int i = 0; i < arr.size(); i++) {
            // Core Monotonic Logic:
            // While the current value is SMALLER than the value corresponding
            // to the index at the top of the stack, we have found an NSE.
            while (!st.empty() && arr[st.top()] > arr[i]) {
                int val = st.top(); // Get the index waiting for an NSE
                arry[val] = arr[i]; // The current element is its NSE
                st.pop(); // This index is resolved, remove it
            }
            // Push current index onto stack to find its NSE later.
            st.push(i);
        }
        // Indices remaining in the stack have no NSE to their right.
        // Their values in 'arry' are already -1 as initialized.
        return arry;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to print vector
void printVector(const vector<int>& vec) {
    cout << "[ ";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    cout << " ]" << endl;
}

// Helper to verify results
bool verifyResult(const vector<int>& result, const vector<int>& expected) {
    if (result.size() != expected.size()) return false;
    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i] != expected[i]) return false;
    }
    return true;
}

int main() {
    Solution solver;

    cout << "INITIATING NEXT SMALLER ELEMENT PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Standard example
    // Input: [4, 8, 5, 2, 25]
    // NSE for 4 is 2.
    // NSE for 8 is 5.
    // NSE for 5 is 2.
    // NSE for 2 is -1.
    // NSE for 25 is -1.
    // Expected: [2, 5, 2, -1, -1]
    vector<int> input1 = {4, 8, 5, 2, 25};
    vector<int> expected1 = {2, 5, 2, -1, -1};
    
    cout << "Input Array 1: "; printVector(input1);
    vector<int> result1 = solver.nextSmallerEle(input1);
    cout << "Result Array 1: "; printVector(result1);

    if (verifyResult(result1, expected1)) {
        cout << "Verification: SUCCESS." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: Sorted array (increasing)
    // Input: [1, 2, 3, 4, 5]
    // No element has a smaller one to its right.
    // Expected: [-1, -1, -1, -1, -1]
    vector<int> input2 = {1, 2, 3, 4, 5};
    vector<int> expected2 = {-1, -1, -1, -1, -1};
    
    cout << "Input Array 2: "; printVector(input2);
    vector<int> result2 = solver.nextSmallerEle(input2);
    cout << "Result Array 2: "; printVector(result2);

    if (verifyResult(result2, expected2)) {
        cout << "Verification: SUCCESS." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 3: Reverse sorted array (decreasing)
    // Input: [5, 4, 3, 2, 1]
    // Expected: [4, 3, 2, 1, -1]
    vector<int> input3 = {5, 4, 3, 2, 1};
    vector<int> expected3 = {4, 3, 2, 1, -1};

    cout << "Input Array 3: "; printVector(input3);
    vector<int> result3 = solver.nextSmallerEle(input3);
    cout << "Result Array 3: "; printVector(result3);

    if (verifyResult(result3, expected3)) {
        cout << "Verification: SUCCESS." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    return 0;
}
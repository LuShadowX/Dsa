/**
 * @file next_greater_element_circular.cpp
 * @author LuShadowX
 * @brief Find the Next Greater Element (NGE) for every element in a circular array.
 * @problem_link: https://www.geeksforgeeks.org/problems/next-greater-element-2/1
 * @difficulty: Medium (Rank B)
 * @tags: Stack, Monotonic Stack, Array, Circular Buffer
 * @logic: Utilizes a Monotonic Decreasing Stack approach.
 * 1. The stack stores *indices* of elements whose NGE has not yet been found.
 * The values at these indices form a decreasing sequence in the stack.
 * 2. To handle the circular property, we simulate iterating through the array
 * twice (up to `2 * N - 1`). We access elements using `arr[i % N]`.
 * 3. For current element `curr = arr[i % N]`:
 * a. While the stack is not empty AND `curr` is greater than the element
 * at the top index of the stack (`arr[st.top()]`):
 * i. We found the NGE for `arr[st.top()]`. It is `curr`.
 * ii. Update the result array at index `st.top()`.
 * iii. Pop the stack.
 * b. Push the current index `i % N` onto the stack.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Monotonic Stack Principle]
 * A monotonic stack is a stack whose elements are always sorted in a specific
 * order (increasing or decreasing).
 *
 * For the "Next Greater Element" problem, we use a **decreasing stack**.
 * Why? We want to keep track of elements that are waiting for a larger value
 * to appear. If we see a value smaller than the top, it doesn't resolve anything,
 * so we push it (maintaining decreasing order). If we see a larger value, it
 * resolves the NGE for smaller values sitting at the top of the stack.
 *
 * [The Circular Simulation Trick]
 * Array: `[A, B, C]` (Size N=3)
 * Conceptual Doubled Array: `[A, B, C, A, B, C]`
 *
 * Instead of creating the doubled array, we iterate `i` from `0` to `2N-1`.
 * Accessing `arr[i % N]` gives us the sequence:
 * i=0: arr[0] (A)
 * i=1: arr[1] (B)
 * i=2: arr[2] (C)
 * i=3: arr[0] (A) -> Wrap around achieved.
 * ...
 *
 * [Time Complexity Analysis]
 * Although the loop runs 2N times, each index is pushed onto the stack at most
 * once and popped at most once. Stack operations are O(1).
 * Total Time: T(N) = O(N).
 *
 * [Space Complexity Analysis]
 * We use a stack that can hold at most N indices (in the case of a reverse
 * sorted array, e.g., [3, 2, 1]).
 * Total Auxiliary Space: S(N) = O(N).
 * ============================================================================
 */

/**
 * MISSION: Next Greater Element (Circular) Protocol
 * RANK: B (Standard Monotonic Stack Application)
 * DEPARTMENT: Linear Data Structures & Pattern Matching
 * CHALLENGE:
 * Given a circular integer array `arr` (the next element of the last element is
 * the first element), return the Next Greater Number for every element.
 * The Next Greater Number of a number x is the first greater number to its
 * traversing-order next in the array. If it doesn't exist, return -1 for this number.
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
     * Finds the next greater element for each element in a circular array.
     * @param arr The input integer vector.
     * @return A vector containing the NGE for each position, or -1 if none exists.
     */
    vector<int> nextGreater(vector<int> &arr) {
        int n = arr.size();
        // Stack stores indices, maintaining decreasing order of values at those indices.
        stack<int> st;
        // Initialize result array with -1.
        vector<int> arry(n, -1);

        // Iterate as if through a doubled array to handle circularity.
        for (int i = 0; i < 2 * n; ++i) {
            // Calculate the actual index in the circular array.
            int currentIdx = i % n;
            int currentValue = arr[currentIdx];

            // Core Monotonic Logic:
            // While the current value is greater than the value corresponding
            // to the index at the top of the stack, we have found an NGE.
            while (!st.empty() && arr[st.top()] < currentValue) {
                int indexToBeResolved = st.top();
                st.pop();
                // Update the result for the resolved index.
                arry[indexToBeResolved] = currentValue;
            }

            // Push current index onto stack to find its NGE later.
            // Important: Only push during the first pass (i < n) to avoid
            // unnecessary duplicate processing on the second pass, although
            // pushing up to 2*N-1 doesn't break correctness, just slightly less efficient.
            // Your original code pushes up to 2*n, which is fine. Let's stick to that.
             st.push(currentIdx);
        }
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

    cout << "INITIATING CIRCULAR NGE PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Standard circular example
    // Input: [1, 2, 1]
    // NGE for 1 (at idx 0) is 2.
    // NGE for 2 (at idx 1) is none (-1), even wrapping around.
    // NGE for 1 (at idx 2) wraps around to find 2 at idx 0.
    // Expected: [2, -1, 2]
    vector<int> input1 = {1, 2, 1};
    vector<int> expected1 = {2, -1, 2};
    
    cout << "Input Array 1: "; printVector(input1);
    vector<int> result1 = solver.nextGreater(input1);
    cout << "Result Array 1: "; printVector(result1);

    if (verifyResult(result1, expected1)) {
        cout << "Verification: SUCCESS." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: Reverse sorted array
    // Input: [3, 2, 1]
    // Wrapping around allows finding larger elements.
    // Expected: [-1, 3, 3]
    vector<int> input2 = {3, 2, 1};
    vector<int> expected2 = {-1, 3, 3};
    
    cout << "Input Array 2: "; printVector(input2);
    vector<int> result2 = solver.nextGreater(input2);
    cout << "Result Array 2: "; printVector(result2);

    if (verifyResult(result2, expected2)) {
        cout << "Verification: SUCCESS." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    return 0;
}
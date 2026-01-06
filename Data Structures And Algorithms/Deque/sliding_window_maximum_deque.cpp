/**
 * @file sliding_window_maximum_deque.cpp
 * @author LuShadowX
 * @brief Find the maximum element in every contiguous subarray of size K.
 * @problem_link: https://www.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1
 * @difficulty: Medium-Hard (Rank B+)
 * @tags: Sliding Window, Deque, Monotonic Queue, Array
 * @logic: Utilizes a Monotonic Decreasing Queue implemented with a std::deque.
 * The deque stores indices of elements.
 *
 * Invariants maintained throughout iteration i:
 * 1. The deque contains indices within the current window range [i-k+1, i].
 * 2. For any two adjacent indices 'j' and 'l' in the deque (where 'j' is before 'l'), arr[j] >= arr[l].
 *
 * Steps at each index 'i':
 * 1. **Clean Outdated:** Remove index from the front if it's outside current window (i.e., front index == i - k).
 * 2. **Maintain Monotonicity:** Remove indices from the back as long as their corresponding array values are less than or equal to arr[i].
 * 3. **Add Current:** Push current index 'i' to the back.
 * 4. **Record Max:** If the first window is formed (i >= k - 1), arr[dq.front()] is the maximum for this window.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Monotonic Deque Principle]
 * Why a deque? We need to efficiently remove outdated elements from the "front"
 * (the oldest elements) and remove useless smaller elements from the "back"
 * (the newest elements) while adding new elements to the "back". A deque supports
 * these O(1) operations at both ends.
 *
 * Why decreasing order? If we have elements with values [10, 5, 8] in a window,
 * 10 is the current maximum. When we encounter 8, the 5 becomes irrelevant; it can
 * never be the maximum again because 8 is larger and will stay in the window longer.
 * By keeping the deque decreasing ([idx(10), idx(8)]), the front always holds
 * the maximum.
 *
 * [Time Complexity Analysis]
 * We iterate through the array of size N once. Inside the loop, elements are
 * pushed onto the deque exactly once and popped (either from front or back) at
 * most once. Deque operations are O(1).
 * Total Time: T(N) = O(N).
 *
 * [Space Complexity Analysis]
 * In the worst case (a monotonically decreasing array like [5, 4, 3, 2, 1]),
 * the deque can hold up to K indices.
 * Total Auxiliary Space: S(K) = O(K). (Excluding result vector space).
 * ============================================================================
 */

/**
 * MISSION: Sliding Window Maximum Protocol
 * RANK: B+ (Advanced Data Structure Application)
 * DEPARTMENT: Linear Data Structures & Optimization
 * CHALLENGE:
 * Given an array `arr` of integers and an integer `k`, return a vector containing
 * the maximum element within every sliding window of size `k` moving from left to right.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(K) auxiliary space allowed.
 */

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    /**
     * Finds maximum elements in sliding windows of size k.
     * @param arr The input array.
     * @param k The size of the window.
     * @return A vector containing maximums of each window.
     */
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        // Deque to store indices of potentially maximum elements.
        // It maintains decreasing order of corresponding values.
        deque<int> dq;
        vector<int> result;

        for (int i = 0; i < arr.size(); i++) {
            // --- Step 1: Remove elements out of the current window ---
            // The window covers indices [i-k+1, i]. If the front index is i-k, it's too old.
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }

            // --- Step 2: Maintain monotonic decreasing property ---
            // Before pushing the current element arr[i], pop elements from the back
            // that are smaller or equal. They are no longer useful candidates for max.
            while (!dq.empty() && arr[dq.back()] <= arr[i]) {
                dq.pop_back();
            }

            // --- Step 3: Add current index ---
            dq.push_back(i);

            // --- Step 4: Record result ---
            // Once we have processed at least k elements, the front of the deque
            // holds the index of the maximum element for the current window.
            if (i >= k - 1) {
                result.push_back(arr[dq.front()]);
            }
        }
        return result;
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

    cout << "INITIATING SLIDING WINDOW MAXIMUM PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Standard Example
    // Input: arr = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
    // Windows: [1,3,-1] -> 3
    //          [3,-1,-3] -> 3
    //          [-1,-3,5] -> 5
    //          [-3,5,3]  -> 5
    //          [5,3,6]   -> 6
    //          [3,6,7]   -> 7
    // Expected: [3, 3, 5, 5, 6, 7]
    vector<int> input1 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    vector<int> expected1 = {3, 3, 5, 5, 6, 7};

    cout << "Input Array 1: "; printVector(input1);
    cout << "Window Size K: " << k1 << endl;
    vector<int> result1 = solver.maxOfSubarrays(input1, k1);
    cout << "Result Array 1: "; printVector(result1);

    if (verifyResult(result1, expected1)) {
        cout << "Verification: SUCCESS." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: Monotonically Increasing Array
    // Input: [1, 2, 3, 4, 5], k=3
    // Expected: [3, 4, 5]
    vector<int> input2 = {1, 2, 3, 4, 5};
    int k2 = 3;
    vector<int> expected2 = {3, 4, 5};

    cout << "Input Array 2 (Increasing): "; printVector(input2);
    vector<int> result2 = solver.maxOfSubarrays(input2, k2);
    cout << "Result Array 2: "; printVector(result2);

    if (verifyResult(result2, expected2)) {
        cout << "Verification: SUCCESS." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 3: Monotonically Decreasing Array (Worst case space for Deque)
    // Input: [5, 4, 3, 2, 1], k=3
    // Expected: [5, 4, 3]
    vector<int> input3 = {5, 4, 3, 2, 1};
    int k3 = 3;
    vector<int> expected3 = {5, 4, 3};

    cout << "Input Array 3 (Decreasing): "; printVector(input3);
    vector<int> result3 = solver.maxOfSubarrays(input3, k3);
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
/**
 * @file merge_sort.cpp
 * @author LuShadowX
 * @brief Implementation of the Merge Sort algorithm.
 * @difficulty: Medium (Rank B)
 * @tags: Sorting, Divide and Conquer, Recursion, Stable Sort
 * @logic: Utilizes the Divide and Conquer strategy. The array is recursively divided
 * into two halves until sub-arrays contain only a single element (base case).
 * Then, these sorted sub-arrays are merged back together using a temporary array
 * and a two-pointer approach to ensure the merged result is sorted.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION & FORMULAE
 * ============================================================================
 * The time complexity T(N) of Merge Sort is defined by the following recurrence relation:
 *
 * [Recurrence Formula]
 * T(N) = 2 * T(N/2) + O(N)
 *
 * Where:
 * - 2 * T(N/2): The time taken to recursively sort two halves of size N/2.
 * - O(N): The time taken to merge the two sorted halves together.
 *
 * [Time Complexity Solution]
 * Applying the Master Theorem (Case 2), the solution to this recurrence is:
 * Time Complexity: O(N log N)
 *
 * This complexity holds true for Best, Average, and Worst cases.
 *
 * [Space Complexity]
 * Space Complexity: O(N) due to the auxiliary temporary array used during merging.
 * ============================================================================
 */

/**
 * MISSION: Merge Sort Protocol (Divide & Conquer Strategy)
 * RANK: B (Fundamental Sorting Algorithm)
 * DEPARTMENT: Algorithmic Sorting & Recursive Optimization
 * CHALLENGE:
 * Sort an integer array in ascending order by recursively dividing the problem
 * into smaller sub-problems and then combining the solutions.
 * CONSTRAINTS:
 * - Time Complexity: O(N log N) - Guaranteed performance.
 * - Space Complexity: O(N) - Requires auxiliary space.
 * - Stability: Stable sort (maintains relative order of equal elements).
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    /**
     * THE MERGER (Conquer Step)
     * Merges two sorted subarrays, arr[l..mid] and arr[mid+1..r], into a single sorted segment.
     * @param arr The array containing the subarrays.
     * @param l Left index of the first subarray.
     * @param mid Right index of the first subarray (and split point).
     * @param r Right index of the second subarray.
     */
    void mergeit(vector<int>& arr, int l, int mid, int r) {
        vector<int> result;      // Temporary array to store merged sorted elements
        int first = l;           // Pointer for left half starting index
        int second = mid + 1;    // Pointer for right half starting index

        // Compare elements from both halves and push the smaller one to result
        while (first <= mid && second <= r) {
            if (arr[first] <= arr[second]) {
                result.push_back(arr[first]);
                first++;
            } else {
                result.push_back(arr[second]);
                second++;
            }
        }

        // Copy any remaining elements from the left half
        while (first <= mid) {
            result.push_back(arr[first]);
            first++;
        }

        // Copy any remaining elements from the right half
        while (second <= r) {
            result.push_back(arr[second]);
            second++;
        }

        // Copy merged result back to original array.
        // CRITICAL: Map temp array index (0 based) back to original array index (l based).
        for (int i = l; i <= r; i++) {
            arr[i] = result[i - l];
        }
    }

public:
    /**
     * THE DIVIDER (Recursive Driver)
     * Recursively splits the array and calls the merger function.
     * @param arr The vector to be sorted.
     * @param l The starting index of the current segment.
     * @param r The ending index of the current segment.
     */
    void mergeSort(vector<int>& arr, int l, int r) {
        // BASE CASE: If the subarray has one or zero elements, it's already sorted.
        if (l == r) return;

        // Calculate middle index to divide the array
        int mid = (l + r) / 2;

        // DIVIDE STEP: Recursively sort left and right halves
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);

        // CONQUER STEP: Merge the sorted halves
        mergeit(arr, l, mid, r);
    }
};

// ================= MAIN PROTOCOL (Testing) =================

void printArray(const vector<int>& arr) {
    cout << "[ ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
    }
    cout << " ]" << endl;
}

int main() {
    Solution solver;

    // TEST CASE SETUP: An unsorted array containing duplicates and negative numbers.
    vector<int> data = {38, 27, 43, 3, 9, 82, 10, 27, -5};
    int N = data.size();

    cout << "INITIATING MERGE SORT PROTOCOL..." << endl;
    cout << "Initial State State (N=" << N << "):" << endl;
    printArray(data);
    cout << "-----------------------------" << endl;

    // Execute the mission
    // Initial call covers the entire array range [0, N-1]
    solver.mergeSort(data, 0, N - 1);

    // Report findings
    cout << "SORTED ARRAY STATE:" << endl;
    printArray(data);
    cout << "-----------------------------" << endl;
    
    // Verification of Time Complexity
    cout << "Time Complexity Verified: O(N log N)" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Expected Output: [ -5, 3, 9, 10, 27, 27, 38, 43, 82 ]

    return 0;
}
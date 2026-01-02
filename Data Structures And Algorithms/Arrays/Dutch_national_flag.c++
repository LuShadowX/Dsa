/**
 * @file sort_012_dnf.cpp
 * @author LuShadowX
 * @brief Sort an array of 0s, 1s, and 2s using the Dutch National Flag Algorithm.
 * @problem_link: https://www.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s4231/1
 * @difficulty: Medium (Rank B) - Often categorized as Easy but optimal solution requires specific technique.
 * @tags: Array, Sorting, Three Pointers, Dutch National Flag Algorithm
 * @logic: Uses three pointers to partition the array in a single pass.
 * - 'low' tracks the boundary of 0s placed at the beginning.
 * - 'mid' traverses the array, processing unknown elements.
 * - 'high' tracks the boundary of 2s placed at the end.
 * Invariant maintained:
 * arr[0...low-1] = 0
 * arr[low...mid-1] = 1
 * arr[high+1...end] = 2
 */
/**
 * MISSION: Dutch National Flag Protocol (Tri-Partition Sort)
 * RANK: B (Foundational Partitioning Technique)
 * DEPARTMENT: Algorithms & Data Structure Optimization
 * CHALLENGE:
 * Given an array consisting solely of 0s, 1s, and 2s, sort the array in ascending order.
 * The operation must be performed in-place without using extra space for another array.
 * CONSTRAINTS:
 * - Time Complexity: O(N) - A strictly one-pass solution.
 * - Space Complexity: O(1) - In-place modification.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * Executes the Dutch National Flag partitioning routine.
     * @param arr The vector containing 0s, 1s, and 2s to be sorted in-place.
     */
    void sort012(vector<int>& arr) {
        int low = 0;          // Pointer for the 0 region boundary
        int mid = 0;          // Scanning pointer for current element
        int high = arr.size() - 1; // Pointer for the 2 region boundary

        // Iterate until the scanning pointer 'mid' crosses the 'high' boundary.
        while(mid <= high){
            if(arr[mid] == 0){
                // Case 0: Current element is 0.
                // Swap it to the 'low' region. Both 'low' and 'mid' advance.
                swap(arr[low], arr[mid]);
                low++;
                mid++;
            }
            else if(arr[mid] == 1){
                // Case 1: Current element is 1.
                // It is already in the correct region relative to 'low'. Just advance 'mid'.
                mid++;
            }
            else {
                // Case 2: Current element is 2 (arr[mid] == 2).
                // Swap it to the 'high' region.
                swap(arr[mid], arr[high]);
                // CRITICAL: Only decrement 'high'. Do NOT increment 'mid'.
                // The element swapped in from arr[high] is unknown and must be processed by 'mid' in the next iteration.
                high--;
            }
        }
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

    // TEST CASE SETUP:
    // Constructing an unsorted vector of 0s, 1s, and 2s.
    vector<int> data = {0, 2, 1, 2, 0, 1, 0, 2, 1};

    cout << "INITIATING DUTCH NATIONAL FLAG SORT PROTOCOL..." << endl;
    cout << "Initial State State:" << endl;
    printArray(data);
    cout << "-----------------------------" << endl;

    // Execute the mission (in-place update)
    solver.sort012(data);

    // Report findings
    cout << "SORTED ARRAY STATE:" << endl;
    printArray(data);
    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Expected Output: [ 0, 0, 0, 1, 1, 1, 2, 2, 2 ]

    return 0;
}
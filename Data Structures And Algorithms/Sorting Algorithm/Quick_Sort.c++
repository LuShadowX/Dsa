/**
 * @file quick_sort.cpp
 * @author LuShadowX
 * @brief Implementation of the Quick Sort algorithm.
 * @difficulty: Medium (Rank B)
 * @tags: Sorting, Divide and Conquer, Recursion, Unstable Sort
 * @logic: Utilizes the Divide and Conquer strategy based on partitioning.
 * 1. Selection: Pick a 'pivot' element (in this implementation, the first element).
 * 2. Partitioning: Rearrange the array so that all elements smaller than or equal to
 * the pivot come before it, and all elements greater come after it. The pivot
 * is now in its final sorted position.
 * 3. Recursion: Recursively apply the above steps to the sub-array to the left
 * of the pivot and the sub-array to the right of the pivot.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION & FORMULAE
 * ============================================================================
 * The time complexity T(N) of Quick Sort depends on the balance of the partitions.
 *
 * [Average Case Recurrence]
 * If the pivot partitions the array roughly in half each time:
 * T(N) = 2 * T(N/2) + O(N) (Partitioning takes linear time)
 * Solution (Master Theorem): O(N log N)
 *
 * [Worst Case Recurrence]
 * If the pivot is always the smallest or largest element (highly unbalanced split):
 * T(N) = T(N-1) + O(N)
 * Solution: O(N^2)
 *
 * [Space Complexity]
 * O(log N) on average due to recursion stack depth. O(N) in worst case.
 * Unlike Merge Sort, Quick Sort is an in-place sort (O(1) auxiliary array space).
 * ============================================================================
 */

/**
 * MISSION: Quick Sort Protocol (Partitioning Strategy)
 * RANK: B (Highly Efficient General-Purpose Sort)
 * DEPARTMENT: Algorithmic Sorting & Recursive Optimization
 * CHALLENGE:
 * Sort an integer array by repeatedly partitioning the array around a chosen
 * pivot element, placing the pivot in its correct sorted position, and
 * recursively sorting the surrounding sub-arrays.
 * CONSTRAINTS:
 * - Time Complexity: O(N log N) average, O(N^2) worst case.
 * - Space Complexity: O(log N) average stack space.
 * - Stability: Unstable sort (relative order of equal elements might change).
 */

#include <iostream>
#include <vector>
#include <algorithm> // For std::swap

using namespace std;

class Solution {
public:
    /**
     * THE RECURSIVE DRIVER
     * Main function to execute Quick Sort recursively.
     * @param arr The vector to be sorted.
     * @param low The starting index of the current segment.
     * @param high The ending index of the current segment.
     */
    void quickSort(vector<int>& arr, int low, int high) {
        // Base condition: If the array has 0 or 1 element, it is sorted.
        if (low < high) {

            // Partition the array and get the pivot's final index
            int part = partition(arr, low, high);

            // Recursively sort the left part (before pivot)
            quickSort(arr, low, part - 1);
            
            // Recursively sort the right part (after pivot)
            quickSort(arr, part + 1, high);
        }
    }

    /**
     * THE PARTITIONER (Core Logic)
     * Rearranges the array around a pivot.
     * Uses the first element as the pivot.
     * @param arr The vector to partition.
     * @param low The starting index.
     * @param high The ending index.
     * @return The final sorted index of the pivot element.
     */
    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[low];   // Choose first element as pivot
        int l = low;            // Left pointer seeking elements > pivot
        int h = high;           // Right pointer seeking elements <= pivot

        // Continue until pointers cross
        while (l <= h) {

            // Move left pointer right until an element strictly greater than pivot is found.
            // Boundary check (l <= high) is crucial.
            while (l <= high && arr[l] <= pivot) {
                l++;
            }

            // Move right pointer left until an element less than or equal to pivot is found.
            // Boundary check (h >= low) is crucial.
            while (h >= low && arr[h] > pivot) {
                h--;
            }

            // If pointers haven't crossed, swap the mispaced elements.
            if (l < h) {
                swap(arr[l], arr[h]);
            }
        }

        // CRITICAL STEP: Place pivot in its correct position.
        // 'h' now points to the last element <= pivot. Swap pivot (at arr[low]) with arr[h].
        swap(arr[low], arr[h]);

        return h;   // Return the final position of pivot
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper to print the array status
void printArray(const vector<int>& arr) {
    cout << "[ ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
    }
    cout << " ]" << endl;
}

int main() {
    Solution solver;

    // TEST CASE SETUP: An unsorted array containing duplicates, negative numbers, and already sorted sections.
    vector<int> data = {4, 2, 8, 3, 1, 5, 7, 1, -2, 4};
    int N = data.size();

    cout << "INITIATING QUICK SORT PROTOCOL..." << endl;
    cout << "Initial State State (N=" << N << "):" << endl;
    printArray(data);
    cout << "-----------------------------" << endl;

    // Execute the mission
    // Initial call covers the entire array range [0, N-1]
    solver.quickSort(data, 0, N - 1);

    // Report findings
    cout << "SORTED ARRAY STATE:" << endl;
    printArray(data);
    cout << "-----------------------------" << endl;
    
    cout << "Time Complexity Note: O(N log N) average case achieved." << endl;
    cout << "MISSION COMPLETE." << endl;

    // Expected Output: [ -2, 1, 1, 2, 3, 4, 4, 5, 7, 8 ]

    return 0;
}
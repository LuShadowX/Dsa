/**
 * @file is_bst_inorder.cpp
 * @author LuShadowX
 * @brief Verify if a given sequence represents the Inorder traversal of a BST.
 * @difficulty: Easy (Rank C)
 * @tags: Binary Search Tree, BST, Inorder Traversal, Array, Sorting
 * @logic: Leverages the fundamental property that an inorder traversal of a
 * valid Binary Search Tree produces a sequence of values sorted in strictly
 * ascending order. The algorithm iterates through the given array and checks
 * if every element is strictly less than its successor. Any violation confirms
 * it is not a valid BST inorder sequence.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION & FORMULAE
 * ============================================================================
 * [BST Property]
 * For any node N in a BST:
 * - All values in the Left Subtree(N) < Value(N)
 * - All values in the Right Subtree(N) > Value(N)
 *
 * [Inorder Traversal Definition]
 * Visit Left Subtree -> Visit Node -> Visit Right Subtree
 *
 * [The Theorem]
 * Combining the BST property with the Inorder definition means we always visit
 * smaller values first, then the middle value, then larger values recursively.
 * Therefore, the resulting sequence S must satisfy:
 * S[0] < S[1] < S[2] < ... < S[N-1]
 *
 * [Violation Condition]
 * The sequence is INVALID if for any adjacent pair indices i and i+1:
 * S[i] >= S[i+1]
 * ============================================================================
 */

/**
 * MISSION: BST Signature Verification Protocol
 * RANK: C (Foundational Property Check)
 * DEPARTMENT: Hierarchical Data Structures & validation
 * CHALLENGE:
 * Given an array of integers, determine if it represents a valid Inorder
 * traversal sequence of a Binary Search Tree.
 * CONSTRAINTS:
 * - Time Complexity: O(N) - A single linear pass is required.
 * - Space Complexity: O(1) - No auxiliary space needed beyond loop variables.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * Checks if the input vector is sorted in strictly ascending order.
     * @param arr The integer vector representing the traversal sequence.
     * @return true if it represents a valid BST inorder traversal, false otherwise.
     */
    bool isBSTTraversal(vector<int>& arr) {
        // An empty or single-element array is technically a valid BST traversal.
        // The loop condition (i < arr.size() - 1) correctly handles size 0 and 1
        // by not executing, returning true.
        
        // Iterate through the array up to the second-to-last element.
        for (int i = 0; i < arr.size() - 1; i++) {
            // CRITICAL CHECK: The BST property dictates strictly increasing order.
            // If current element is greater than or equal to the next, the property is violated.
            if (arr[i] >= arr[i+1]) {
                return false; // Violation found
            }
        }
        
        // If the loop completes without violations, the sequence is valid.
        return true;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper to print boolean results clearly
string boolToString(bool b) { return b ? "VALID (True)" : "INVALID (False)"; }

int main() {
    Solution solver;

    cout << "INITIATING BST SIGNATURE VERIFICATION..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: A valid BST inorder sequence (strictly increasing)
    vector<int> validSeq = {10, 20, 30, 40, 50};
    cout << "Test Case 1 (Valid): [10, 20, 30, 40, 50]" << endl;
    cout << "Result: " << boolToString(solver.isBSTTraversal(validSeq)) << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 2: An invalid sequence (unsorted)
    vector<int> invalidSeqUnsorted = {10, 30, 20, 40, 50};
    cout << "Test Case 2 (Invalid - Unsorted): [10, 30, 20, 40, 50]" << endl;
    // Violation occurs at index 1 vs 2 (30 >= 20)
    cout << "Result: " << boolToString(solver.isBSTTraversal(invalidSeqUnsorted)) << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 3: An invalid sequence (contains duplicates)
    // Standard BST definition implies distinct keys.
    vector<int> invalidSeqDuplicate = {10, 20, 20, 40, 50};
    cout << "Test Case 3 (Invalid - Duplicates): [10, 20, 20, 40, 50]" << endl;
    // Violation occurs at index 1 vs 2 (20 >= 20)
    cout << "Result: " << boolToString(solver.isBSTTraversal(invalidSeqDuplicate)) << endl;
    cout << "-----------------------------" << endl;

    cout << "MISSION COMPLETE." << endl;

    return 0;
}
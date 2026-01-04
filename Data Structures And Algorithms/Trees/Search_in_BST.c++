/**
 * @file search_in_bst.cpp
 * @author LuShadowX
 * @brief Search for a specific key value within a Binary Search Tree (BST).
 * @problem_link: https://www.geeksforgeeks.org/problems/search-a-node-in-bst/1
 * @difficulty: Easy (Rank C)
 * @tags: Binary Search Tree, BST, Search, Recursion, Divide and Conquer
 * @logic: Utilizes the fundamental BST property to perform an optimized search.
 * Unlike a generic binary tree where we might need to search O(N) nodes,
 * in a BST, comparing the key with the current root tells us exactly which
 * direction to go:
 * - If key == root->data: Found.
 * - If key < root->data: Go Left (discard right subtree).
 * - If key > root->data: Go Right (discard left subtree).
 */

/**
 * ============================================================================
 * MATHEMATICAL & ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The BST Definition]
 * For any node 'N' in a valid BST:
 * 1. All keys in the Left Subtree of N are strictly LESS than N's key.
 * 2. All keys in the Right Subtree of N are strictly GREATER than N's key.
 * (Assuming distinct keys).
 *
 * [The Search Recurrence Relation]
 * The search operation S(root, key) can be defined mathematically:
 *
 * / True                  if root is valid AND root->data == key
 * S(root, k) =| False                 if root is NULL
 * | S(root->left, k)      if k < root->data
 * \ S(root->right, k)     if k > root->data
 *
 * [Time Complexity Analysis]
 * At each step, we descend one level in the tree. The number of comparison steps
 * is at most the Height (H) of the tree.
 * - Average/Best Case (Balanced Tree): H = O(log N). The search is efficient.
 * - Worst Case (Skewed Tree, like a line): H = O(N). The search degrades to linear.
 *
 * [Space Complexity Analysis]
 * Space is dictated by the maximum depth of the recursion stack.
 * Total Space: S(N) = O(H), where H is the tree height.
 * ============================================================================
 */

/**
 * MISSION: BST Target Acquisition Protocol
 * RANK: C (Foundational BST Operation)
 * DEPARTMENT: Hierarchical Data Structures & Search Algorithms
 * CHALLENGE:
 * Given the root of a Binary Search Tree (BST) and an integer 'key',
 * return true if the node with the given key exists in the BST, and false otherwise.
 * CONSTRAINTS:
 * - Time Complexity: O(Height of Tree) - O(log N) average, O(N) worst case.
 * - Space Complexity: O(Height of Tree) for recursion stack.
 */

#include <iostream>

using namespace std;

// Standard definition for a Binary Tree Node.
struct Node {
    int data;
    Node* left;
    Node* right;
    // Constructor for easier testing
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * Searches for a key in the BST using recursion.
     * @param root The current node being inspected.
     * @param key The target value to find.
     * @return true if found, false otherwise.
     */
    bool search(Node* root, int key) {
        // BASE CASES:
        // 1. We reached a NULL pointer (key not found in this path).
        if (root == NULL) {
            return false;
        }
        // 2. We found the key at the current node.
        if (root->data == key) {
            return true;
        }

        // RECURSIVE STEP (Divide & Conquer based on BST property):
        if (key < root->data) {
            // Key is smaller than current node, it must be in the Left subtree.
            // Discard the right subtree.
            return search(root->left, key);
        } else {
            // Key is larger than (or equal to) current node.
            // It must be in the Right subtree. Discard the left subtree.
            // Note: If duplicates are allowed and stored left, the logic adjusts,
            // but for standard BST search, this is correct.
            return search(root->right, key);
        }
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to insert nodes to create a BST for testing
Node* insertBST(Node* root, int val) {
    if (root == nullptr) return new Node(val);
    if (val < root->data) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

int main() {
    Solution solver;

    /* TEST CASE SETUP: Constructing a BST
     * 4
     * / \
     * 2   7
     * / \
     * 1   3
     */
    Node* root = nullptr;
    root = insertBST(root, 4);
    insertBST(root, 2);
    insertBST(root, 7);
    insertBST(root, 1);
    insertBST(root, 3);

    cout << "INITIATING BST TARGET ACQUISITION PROTOCOL..." << endl;
    cout << "BST structure constructed." << endl;
    cout << "-----------------------------" << endl;

    // Test Case 1: Searching for an existing key
    int target1 = 2;
    cout << "Searching for Key: " << target1 << endl;
    bool found1 = solver.search(root, target1);
    cout << "Status: " << (found1 ? "FOUND (Success)" : "NOT FOUND (Failure)") << endl;
    cout << "-----------------------------" << endl;

    // Test Case 2: Searching for a non-existent key
    int target2 = 5;
    cout << "Searching for Key: " << target2 << endl;
    bool found2 = solver.search(root, target2);
    cout << "Status: " << (found2 ? "FOUND (Success)" : "NOT FOUND (Failure)") << endl;

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup omitted for brevity in competitive programming context,
    // but crucial in real-world applications.

    return 0;
}
/**
 * @file insert_in_bst.cpp
 * @author LuShadowX
 * @brief Insert a new key value into a Binary Search Tree (BST).
 * @problem_link: https://www.geeksforgeeks.org/problems/insert-a-node-in-a-bst/1
 * @difficulty: Easy (Rank C)
 * @tags: Binary Search Tree, BST, Insertion, Recursion
 * @logic: The insertion process mirrors the BST search process. We start at the
 * root and traverse down:
 * 1. If the current node is NULL, we have found the correct empty spot. Create
 * the new node and return it. This becomes the base case.
 * 2. If the new key is greater than the current node's data, we recurse to the
 * right child, linking the result back to current->right.
 * 3. If the new key is smaller (or equal, handling duplicates by placing them left),
 * we recurse to the left child, linking the result back to current->left.
 * 4. Finally, return the (potentially modified) root pointer up the stack to
 * maintain tree integrity.
 */

/**
 * ============================================================================
 * MATHEMATICAL & ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The BST Invariant Maintenance]
 * The core principle is to maintain the BST property after insertion:
 * For every node N, ∀L ∈ LeftSubtree(N), L < N AND ∀R ∈ RightSubtree(N), R > N.
 * (Note: This implementation handles duplicates by placing them in the left subtree,
 * effectively making the rule L <= N).
 *
 * [Recursive Structure]
 * The insertion operation I(root, key) is defined recursively:
 *
 * / new Node(key)          if root is NULL (Base Case: Attachment)
 * I(root, key) = | root->right = I(...)   if key > root->data (Recurse Right)
 * \ root->left = I(...)    if key <= root->data (Recurse Left)
 *
 * [Time Complexity Analysis]
 * The algorithm traces a path from the root to a leaf where the new node belongs.
 * The length of this path is at most the Height (H) of the tree.
 * - Average/Best Case (Balanced Tree): H = O(log N).
 * - Worst Case (Skewed Tree): H = O(N).
 *
 * [Space Complexity Analysis]
 * Space is dictated by the recursion stack depth.
 * Total Space: S(N) = O(H), where H is the tree height.
 * ============================================================================
 */

/**
 * MISSION: BST Expansion Protocol
 * RANK: C (Foundational BST Operation)
 * DEPARTMENT: Hierarchical Data Structures & Dynamic Modifications
 * CHALLENGE:
 * Given the root of a Binary Search Tree (BST) and an integer 'key', insert
 * the key into the BST into its correct position such that the BST property
 * holds true after insertion. Return the root of the modified tree.
 * CONSTRAINTS:
 * - Time Complexity: O(Height of Tree).
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
     * Inserts a new key into the BST using recursion.
     * @param root The root of the current subtree.
     * @param key The value to insert.
     * @return The root of the (potentially modified) subtree.
     */
    Node* insert(Node* root, int key) {
        // BASE CASE: Found the empty spot. Create and return the new node.
        if (root == NULL) {
            return new Node(key);
        }

        // RECURSIVE STEP 1: Key is larger, go right.
        if (root->data < key) {
            // Crucial: Update the right pointer with the result of the recursive call.
            // This attaches the new node when the base case returns it.
            root->right = insert(root->right, key);
        }
        // RECURSIVE STEP 2: Key is smaller (or equal), go left.
        else {
            // Crucial: Update the left pointer with the result of the recursive call.
            root->left = insert(root->left, key);
        }

        // Return the current node pointer up the recursion stack to maintain connections.
        return root;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function: Inorder Traversal to verify BST property (prints sorted)
void inorderPrint(Node* root) {
    if (root == nullptr) return;
    inorderPrint(root->left);
    cout << root->data << " ";
    inorderPrint(root->right);
}

int main() {
    Solution solver;
    Node* root = nullptr;

    cout << "INITIATING BST EXPANSION PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // Phase 1: Building the initial tree
    cout << "Inserting initial batch: 4, 2, 7, 1, 3" << endl;
    root = solver.insert(root, 4); // Insert into empty tree, root becomes 4
    solver.insert(root, 2);
    solver.insert(root, 7);
    solver.insert(root, 1);
    solver.insert(root, 3);

    cout << "Current BST State (Inorder): ";
    inorderPrint(root);
    cout << endl << "-----------------------------" << endl;

    // Phase 2: Inserting a new value
    int newKey = 5;
    cout << "Executing insertion of new key: " << newKey << endl;
    solver.insert(root, newKey);

    // Verification
    cout << "BST State After Insertion (Inorder): ";
    inorderPrint(root);
    cout << endl;
    // Expected: 1 2 3 4 5 7 (Sorted order confirms valid BST)

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup omitted for brevity in competitive programming context.

    return 0;
}
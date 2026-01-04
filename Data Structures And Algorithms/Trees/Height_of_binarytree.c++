/**
 * @file height_of_binary_tree.cpp
 * @author LuShadowX
 * @brief Calculate the Height (maximum depth) of a Binary Tree based on edge count.
 * @problem_link: https://www.geeksforgeeks.org/problems/height-of-binary-tree/1
 * @difficulty: Easy (Rank C)
 * @tags: Tree, Binary Tree, DFS, Recursion, Height
 * @logic: Uses a recursive Postorder DFS approach (Bottom-Up).
 * The height of a node is defined as 1 plus the maximum height of its left
 * or right children. Crucially, this implementation defines height as the
 * number of EDGES on the longest path from the node to a leaf.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION & FORMULAE
 * ============================================================================
 * The Height H(root) is defined recursively based on EDGE count:
 *
 * [Base Case - The "Edge" Shift]
 * If root is NULL, it represents a non-existent path beneath a leaf.
 * To ensure a leaf node calculates to height 0, the base case must return -1.
 * H(NULL) = -1
 *
 * [Recursive Step]
 * For any existing node, its height is 1 (the edge connecting it to its child)
 * plus the maximum height of its subtrees.
 * H(root) = 1 + max( H(root->left), H(root->right) )
 *
 * [Verification for Leaf Node]
 * Leaf Node L has NULL left and right children.
 * H(L) = 1 + max( H(NULL), H(NULL) )
 * H(L) = 1 + max( -1, -1 )
 * H(L) = 1 + (-1) = 0. (Correct: A leaf has 0 edges beneath it).
 * ============================================================================
 */

/**
 * MISSION: Binary Tree Altitude Protocol (Edge Metric)
 * RANK: C (Foundational Tree Metric)
 * DEPARTMENT: Hierarchical Data Structures & Recursive Algorithms
 * CHALLENGE:
 * Given the root of a Binary Tree, determine its height. The height is defined
 * as the number of edges on the longest path from the root node down to the
 * deepest leaf node. An empty tree has a height of -1. A single root node
 * has a height of 0.
 * CONSTRAINTS:
 * - Time Complexity: O(N) - Every node must be visited to ensure the longest path is found.
 * - Space Complexity: O(H) - Auxiliary stack space depends on tree height.
 */

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Standard definition for a Binary Tree Node.
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * Calculates the height of the tree (edge count definition).
     * @param root The root of the binary tree.
     * @return The height of the tree based on edges (-1 for empty tree).
     */
    int height(Node* root) {
        // CRITICAL BASE CASE (Edge Count Definition):
        // If the node is NULL, return -1. This ensures that leaf nodes
        // evaluate to height 0 (1 + max(-1, -1)).
        if (root == NULL) {
            return -1;
        }

        // 1. Recursive Hypothesis: Get height of left subtree
        int leftHeight = height(root->left);

        // 2. Recursive Hypothesis: Get height of right subtree
        int rightHeight = height(root->right);

        // 3. Induction Step: Current height is 1 (current edge) + max child height
        return 1 + max(leftHeight, rightHeight);
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    /* TEST CASE SETUP: Constructing a tree with height 2 (edges)
     * 1      (Depth 0, Height 2)
     * / \
     * 2   3    (Depth 1, Height 1)
     * /
     * 4          (Depth 2, Height 0 - Leaf)
     *
     * Longest path edges: 1->2, 2->4. Total edges = 2.
     */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);

    cout << "INITIATING TREE ALTITUDE PROTOCOL..." << endl;
    cout << "Tree structure constructed." << endl;
    cout << "-----------------------------" << endl;

    // Execute the mission
    int treeHeight = solver.height(root);

    // Report findings
    cout << "REPORT:" << endl;
    cout << "Calculated Tree Height (Edges): " << treeHeight << endl;

    // Verification
    int expectedHeight = 2;
    if (treeHeight == expectedHeight) {
        cout << "STATUS: SUCCESS - Height matches expected edge count." << endl;
    } else {
        cout << "STATUS: FAILURE - Discrepancy detected." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Cleanup memory
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}
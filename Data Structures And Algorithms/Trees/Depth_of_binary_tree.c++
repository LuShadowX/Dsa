/**
 * @file max_depth_binary_tree.cpp
 * @author LuShadowX
 * @brief Calculate the Maximum Depth of a Binary Tree based on NODE count.
 * @problem_link: https://www.geeksforgeeks.org/problems/maximum-depth-of-binary-tree/1
 * @difficulty: Easy (Rank C)
 * @tags: Tree, Binary Tree, DFS, Recursion, Depth
 * @logic: Uses a recursive DFS approach. The maximum depth is defined as the
 * number of NODES on the longest path from the root to the farthest leaf.
 * The depth of a node is 1 (itself) plus the maximum depth of its children.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION & FORMULAE
 * ============================================================================
 * The Maximum Depth D(root) is defined recursively based on NODE count:
 *
 * [Base Case - The "Node" Count]
 * If root is NULL, it signifies an empty path. It contributes ZERO nodes.
 * D(NULL) = 0
 *
 * [Recursive Step]
 * For any existing node, its depth contribution is 1 (the node itself)
 * plus the maximum depth of its subtrees.
 * D(root) = 1 + max( D(root->left), D(root->right) )
 *
 * [Verification for Leaf Node]
 * Leaf Node L has NULL left and right children.
 * D(L) = 1 + max( D(NULL), D(NULL) )
 * D(L) = 1 + max( 0, 0 )
 * D(L) = 1. (Correct: A leaf node counts as 1 node in the path).
 * ============================================================================
 */

/**
 * MISSION: Binary Tree Depth Protocol (Node Metric)
 * RANK: C (Foundational Tree Metric)
 * DEPARTMENT: Hierarchical Data Structures & Recursive Algorithms
 * CHALLENGE:
 * Given the root of a Binary Tree, determine its maximum depth. The maximum
 * depth is the number of nodes along the longest path from the root node
 * down to the farthest leaf node. An empty tree has a depth of 0.
 * CONSTRAINTS:
 * - Time Complexity: O(N) - Every node must be visited.
 * - Space Complexity: O(H) - Auxiliary stack space depends on tree height.
 */

#include <iostream>
#include <vector>
#include <algorithm> // For std::max

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
     * Calculates the maximum depth of the tree (node count definition).
     * @param root The root of the binary tree.
     * @return The number of nodes on the longest path.
     */
    int maxDepth(Node* root) {
        // CRITICAL BASE CASE (Node Count Definition):
        // If the node is NULL, it contributes 0 nodes to the path.
        if (root == NULL) {
            return 0;
        }

        // 1. Recursive Hypothesis: Get node-depth of left subtree
        int leftDepth = maxDepth(root->left);

        // 2. Recursive Hypothesis: Get node-depth of right subtree
        int rightDepth = maxDepth(root->right);

        // 3. Induction Step: Add 1 for the current node itself
        return 1 + max(leftDepth, rightDepth);
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    /* TEST CASE SETUP: Constructing the following tree:
     * 1      (Depth 1)
     * / \
     * 2   3    (Depth 2)
     * / \
     * 4   5      (Depth 3 - Leaves)
     *
     * Longest path (nodes): 1->2->4 or 1->2->5.
     * Total nodes on longest path = 3.
     */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "INITIATING TREE DEPTH PROTOCOL (NODE COUNT)..." << endl;
    cout << "Tree structure constructed." << endl;
    cout << "-----------------------------" << endl;

    // Execute the mission
    int depth = solver.maxDepth(root);

    // Report findings
    cout << "REPORT:" << endl;
    cout << "Calculated Maximum Depth (Nodes): " << depth << endl;

    // Verification
    int expectedDepth = 3;
    if (depth == expectedDepth) {
        cout << "STATUS: SUCCESS - Depth matches expected node count." << endl;
    } else {
        cout << "STATUS: FAILURE - Discrepancy detected." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Cleanup memory
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}
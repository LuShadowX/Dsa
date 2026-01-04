/**
 * @file preorder_traversal.cpp
 * @author LuShadowX
 * @brief Recursive Preorder Traversal of a Binary Tree.
 * @problem_link: https://www.geeksforgeeks.org/problems/preorder-traversal/1
 * @difficulty: Easy (Rank C)
 * @tags: Tree, Binary Tree, DFS, Recursion, Preorder
 * @logic: Follows the Depth-First Search principle using the NLR sequence:
 * 1. Visit (process) the current Node immediately.
 * 2. Recursively traverse the current node's Left subtree.
 * 3. Recursively traverse the current node's Right subtree.
 * This priority on the root node defines the "Pre" order nature.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION & FORMULAE
 * ============================================================================
 * The Traversal Sequence T(root) is defined recursively:
 *
 * [Traversal Definition (NLR)]
 * If root is NULL: T(root) = Ø (Empty sequence)
 * If root exists:  T(root) = Value(root) + T(root->left) + T(root->right)
 *
 * [Time Complexity Analysis]
 * Every node is visited exactly once to process its value.
 * Total Time: T(N) = O(N), where N is the total number of nodes.
 *
 * [Space Complexity Analysis]
 * Space is dictated by the maximum depth of the recursion stack, which equals
 * the height of the tree (H).
 * - Best/Average Case (Balanced Tree): H = O(log N)
 * - Worst Case (Skewed Tree): H = O(N)
 * Total Space: S(N) = O(H)
 * ============================================================================
 */

/**
 * MISSION: Preorder Traversal Protocol (NLR Sequence)
 * RANK: C (Foundational Tree Traversal)
 * DEPARTMENT: Hierarchical Data Structures & Recursive Algorithms
 * CHALLENGE:
 * Given the root of a Binary Tree, return a sequence of its node values
 * corresponding to a Preorder traversal. This order is crucial for tasks like
 * creating a prefix expression from an expression tree or serializing a tree.
 * CONSTRAINTS:
 * - Time Complexity: O(N) guaranteed.
 * - Space Complexity: O(H) auxiliary stack space.
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
    // Constructor for easier testing
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    /**
     * THE RECURSIVE NAVIGATOR (Helper Function)
     * Executes the NLR traversal logic recursively.
     * @param root The current node being visited.
     * @param result Reference to the vector storing the traversal sequence.
     */
    void preorder(Node* root, vector<int>& result) {
        // CRITICAL BASE CASE: If node is empty, backtrack.
        if (root == NULL) {
            return;
        }

        // 1. PROCESS NODE: Capture the current node's data FIRST.
        result.push_back(root->data);

        // 2. TRAVERSE LEFT: Explore the left subtree subsequently.
        preorder(root->left, result);

        // 3. TRAVERSE RIGHT: Explore the right subtree finally.
        preorder(root->right, result);
    }

public:
    /**
     * Initiates the Preorder traversal operation.
     * @param root The root of the binary tree.
     * @return A vector containing node values in Preorder sequence.
     */
    vector<int> preOrder(Node* root) {
        vector<int> result;
        // Start the recursive navigation protocol
        preorder(root, result);
        return result;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to neatly print the result vector
void printVector(const vector<int>& vec) {
    cout << "[ ";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    cout << " ]" << endl;
}

int main() {
    Solution solver;

    /* TEST CASE SETUP: Constructing the following binary tree:
     * 1
     * / \
     * 2   3
     * / \
     * 4   5
     *
     * Expected Preorder (NLR): Node(1) -> Left(2) -> Right(3)
     * Left(2) expands to: Node(2) -> Left(4) -> Right(5)
     * Final sequence: 1, 2, 4, 5, 3
     */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "INITIATING PREORDER TRAVERSAL PROTOCOL..." << endl;
    cout << "Tree structure constructed. Processing NLR sequence." << endl;
    cout << "-----------------------------" << endl;

    // Execute the mission
    vector<int> result = solver.preOrder(root);

    // Report findings
    cout << "TRAVERSAL SEQUENCE DETECTED:" << endl;
    printVector(result);
    
    // Verification
    vector<int> expected = {1, 2, 4, 5, 3};
    if (result == expected) {
        cout << "STATUS: SUCCESS - Sequence matches expected NLR order." << endl;
    } else {
        cout << "STATUS: FAILURE - Discrepancy detected." << endl;
    }
    
    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Cleanup memory (good practice for manual tree construction)
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}
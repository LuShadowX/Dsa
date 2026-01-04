/**
 * @file postorder_traversal.cpp
 * @author LuShadowX
 * @brief Recursive Postorder Traversal of a Binary Tree.
 * @problem_link: https://www.geeksforgeeks.org/problems/postorder-traversal/1
 * @difficulty: Easy (Rank C)
 * @tags: Tree, Binary Tree, DFS, Recursion, Postorder
 * @logic: Follows the Depth-First Search principle using the LRN sequence:
 * 1. Recursively traverse the current node's Left subtree.
 * 2. Recursively traverse the current node's Right subtree.
 * 3. Visit (process) the current Node finally.
 * This ensures children are always processed before their parent.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION & FORMULAE
 * ============================================================================
 * The Traversal Sequence T(root) is defined recursively:
 *
 * [Traversal Definition (LRN)]
 * If root is NULL: T(root) = Ø (Empty sequence)
 * If root exists:  T(root) = T(root->left) + T(root->right) + Value(root)
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
 * MISSION: Postorder Traversal Protocol (LRN Sequence)
 * RANK: C (Foundational Tree Traversal)
 * DEPARTMENT: Hierarchical Data Structures & Recursive Algorithms
 * CHALLENGE:
 * Given the root of a Binary Tree, return a sequence of its node values
 * corresponding to a Postorder traversal. This order is crucial for tasks like
 * deleting a tree from leaves up, or evaluating expression trees bottom-up.
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
     * Executes the LRN traversal logic recursively.
     * @param root The current node being visited.
     * @param result Reference to the vector storing the traversal sequence.
     */
    void postorder(Node* root, vector<int>& result) {
        // CRITICAL BASE CASE: If node is empty, backtrack.
        if (root == NULL) {
            return;
        }

        // 1. TRAVERSE LEFT: Explore the left subtree first.
        postorder(root->left, result);

        // 2. TRAVERSE RIGHT: Explore the right subtree next.
        postorder(root->right, result);

        // 3. PROCESS NODE: Capture the current node's data FINALLY.
        result.push_back(root->data);
    }

public:
    /**
     * Initiates the Postorder traversal operation.
     * @param root The root of the binary tree.
     * @return A vector containing node values in Postorder sequence.
     */
    vector<int> postOrder(Node* root) {
        vector<int> result;
        // Start the recursive navigation protocol
        postorder(root, result);
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
     * Expected Postorder (LRN): Left(2) -> Right(3) -> Node(1)
     * Left(2) expands to: Left(4) -> Right(5) -> Node(2)
     * Final sequence: 4, 5, 2, 3, 1
     */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "INITIATING POSTORDER TRAVERSAL PROTOCOL..." << endl;
    cout << "Tree structure constructed. Processing LRN sequence." << endl;
    cout << "-----------------------------" << endl;

    // Execute the mission
    vector<int> result = solver.postOrder(root);

    // Report findings
    cout << "TRAVERSAL SEQUENCE DETECTED:" << endl;
    printVector(result);
    
    // Verification
    vector<int> expected = {4, 5, 2, 3, 1};
    if (result == expected) {
        cout << "STATUS: SUCCESS - Sequence matches expected LRN order." << endl;
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
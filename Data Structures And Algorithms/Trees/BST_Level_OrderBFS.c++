/**
 * @file level_order_traversal.cpp
 * @author LuShadowX
 * @brief Perform a Level Order Traversal (BFS) on a Binary Tree.
 * @problem_link: https://www.geeksforgeeks.org/problems/level-order-traversal/1
 * @difficulty: Easy-Medium (Rank C+)
 * @tags: Tree, Binary Tree, BFS, Queue, Level Order
 * @logic: Utilizes the Breadth-First Search (BFS) strategy using a queue.
 * To group nodes by level, we take a "snapshot" of the current queue size at the
 * beginning of each main loop iteration. We then process exactly that many nodes
 * (the current level), adding their children to the back of the queue for the
 * next level.
 */

/**
 * ============================================================================
 * MATHEMATICAL & ALGORITHMIC FOUNDATION
 * ============================================================================
 * [Breadth-First Search (BFS) Principle]
 * BFS explores a tree layer by layer. Mathematically, it visits all nodes at
 * depth 'd' before visiting any node at depth 'd+1'.
 *
 * [Queue Invariant]
 * The queue operates on First-In-First-Out (FIFO). When processing depth 'd',
 * we enqueue nodes at depth 'd+1'. The FIFO nature ensures we finish depth 'd'
 * before starting depth 'd+1'.
 *
 * [Time Complexity Analysis]
 * Every node is pushed into and popped from the queue exactly once.
 * Total Time: T(N) = O(N), where N is the total number of nodes.
 *
 * [Space Complexity Analysis]
 * Space is dictated by the maximum number of nodes in the queue at any given time.
 * This occurs at the widest level of the tree. In the worst case (a complete
 * binary tree), the last level contains approximately N/2 nodes.
 * Total Space: S(N) = O(W), where W is the maximum width of the tree. Worst case O(N).
 * ============================================================================
 */

/**
 * MISSION: Level Order Traversal Protocol (Layer-by-Layer Analysis)
 * RANK: C+ (Foundational BFS Pattern)
 * DEPARTMENT: Hierarchical Data Structures & Graph Traversal
 * CHALLENGE:
 * Given the root of a Binary Tree, return a 2D vector representing its
 * level-order traversal. Each inner vector should contain the node values
 * for a distinct level, from left to right, starting from the root level (depth 0).
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(N) required auxiliary space for the queue.
 */

#include <iostream>
#include <vector>
#include <queue>

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
     * Executes the level order traversal.
     * @param root The root of the binary tree.
     * @return A 2D vector where each inner vector holds nodes of one level.
     */
    vector<vector<int>> levelOrder(Node *root) {
        vector<vector<int>> result;
        if (root == NULL) return result; // Handle empty tree base case

        queue<Node*> q;
        // 1. Initialization: Push the root node to start the BFS.
        q.push(root);

        // Continue until all levels have been processed
        while (!q.empty()) {
            // CRITICAL STEP: Snapshot the current level size.
            // This is the number of nodes present in the *current* depth level.
            // We must process exactly this many nodes in this inner loop.
            int size = q.size();
            
            vector<int> currentLevelValues; // Temporary storage for this level

            // Process all nodes belonging to the current level
            for (int i = 0; i < size; i++) {
                Node* node = q.front();
                q.pop();

                // Capture value
                currentLevelValues.push_back(node->data);

                // Enqueue left child if it exists (for next level)
                if (node->left != NULL) q.push(node->left);
                // Enqueue right child if it exists (for next level)
                if (node->right != NULL) q.push(node->right);
            }

            // Add the completed level group to the final result
            result.push_back(currentLevelValues);
        }
        return result;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to print the 2D result vector
void print2DVector(const vector<vector<int>>& vec) {
    cout << "[" << endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << "  Level " << i << ": [ ";
        for (size_t j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << (j == vec[i].size() - 1 ? "" : ", ");
        }
        cout << " ]" << endl;
    }
    cout << "]" << endl;
}

int main() {
    Solution solver;

    /* TEST CASE SETUP: Constructing the following binary tree:
     * 3      (Level 0)
     * / \
     * 9   20   (Level 1)
     * /  \
     * 15   7 (Level 2)
     *
     * Expected Output: [[3], [9, 20], [15, 7]]
     */
    Node* root = new Node(3);
    root->left = new Node(9);
    root->right = new Node(20);
    root->right->left = new Node(15);
    root->right->right = new Node(7);

    cout << "INITIATING LEVEL ORDER TRAVERSAL PROTOCOL..." << endl;
    cout << "Tree structure constructed." << endl;
    cout << "-----------------------------" << endl;

    // Execute the mission
    vector<vector<int>> result = solver.levelOrder(root);

    // Report findings
    cout << "TRAVERSAL RESULTS (Grouped by Level):" << endl;
    print2DVector(result);

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Cleanup memory (good practice)
    delete root->right->right;
    delete root->right->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}
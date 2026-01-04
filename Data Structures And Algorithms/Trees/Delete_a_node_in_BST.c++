/**
 * @file delete_node_bst_successor.cpp
 * @author LuShadowX
 * @brief Delete a specific key value from a Binary Search Tree (BST).
 * @problem_link: https://www.geeksforgeeks.org/problems/delete-a-node-from-bst/1
 * @difficulty: Medium (Rank B)
 * @tags: Binary Search Tree, BST, Deletion, Recursion, In-order Successor
 * @logic: The algorithm first searches for the node to delete. Once found, it handles
 * three cases to maintain the BST invariant:
 * 1. Node has NO children (Leaf): Simply remove it (return NULL).
 * 2. Node has ONE child: Replace the node with its single child.
 * 3. Node has TWO children (Successor Strategy): Find the inorder successor
 * (the smallest node in the right subtree). Replace the target node's *data*
 * with the successor's data. Finally, recursively delete the original
 * successor node from the right subtree.
 */

/**
 * ============================================================================
 * MATHEMATICAL & ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The BST Invariant Maintenance]
 * The deletion operation must ensure that for every node N remaining in the tree:
 * ∀L ∈ LeftSubtree(N), L < N AND ∀R ∈ RightSubtree(N), R > N.
 *
 * [Two-Child Deletion Strategy - Successor Value Replacement]
 * When deleting node D with two children:
 * 1. Let S be the inorder successor of D (the leftmost node of D->right).
 * 2. Property: S is greater than all nodes in D->left, and smaller than all
 * other nodes in D->right.
 * 3. Replacing D's value with S's value maintains the BST property at D's position.
 * 4. The problem reduces to deleting the original S from D->right. Since S is
 * the leftmost node, it has at most one right child, making its deletion trivial.
 *
 * [Time Complexity Analysis]
 * Let H be the tree height.
 * - Search: O(H)
 * - Finding Successor: O(H) in worst case.
 * - Recursive delete of successor: O(H).
 * Total Time: O(H).
 *
 * [Space Complexity Analysis]
 * Total Space: S(N) = O(H) due to recursion stack depth.
 * ============================================================================
 */

/**
 * MISSION: BST Node Removal Protocol (Successor Variant)
 * RANK: B (Complex BST Operation)
 * DEPARTMENT: Hierarchical Data Structures & Dynamic Modifications
 * CHALLENGE:
 * Given the root of a Binary Search Tree (BST) and an integer 'key', delete the
 * node with the given key from the BST. Return the root of the modified tree.
 * The tree must remain a valid BST after deletion.
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
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * Deletes a key from the BST using recursion (Successor approach).
     * @param root The root of the current subtree.
     * @param key The value to delete.
     * @return The root of the (potentially modified) subtree.
     */
    Node* delNode(Node* root, int key) {
        // BASE CASE: Key not found or tree is empty.
        if (root == NULL) {
            return NULL;
        }

        // SEARCH PHASE: Navigate to the node to be deleted.
        if (root->data < key) {
            // Key is larger, search right subtree. Update right pointer.
            root->right = delNode(root->right, key);
        } else if (root->data > key) {
            // Key is smaller, search left subtree. Update left pointer.
            root->left = delNode(root->left, key);
        } 
        // DELETION PHASE: Node found (root->data == key).
        else {
            // CASE 1 & 2: Node has 0 or 1 child (Left child is NULL).
            // Replace current node with its right child.
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root; // Free memory
                return temp; // Return the surviving child
            }
            // CASE 1 & 2: Node has 0 or 1 child (Right child is NULL).
            // Replace current node with its left child.
            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root; // Free memory
                return temp; // Return the surviving child
            }
            
            // CASE 3: Node has TWO children (Successor Strategy).
            
            // 1. Find the In-order Successor (smallest in right subtree)
            Node* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            
            // 2. Value Replacement: Copy successor's data to current node
            root->data = temp->data;
            
            // 3. Reduce to trivial case: Delete the original successor node
            // from the right subtree. It's guaranteed to have 0 or 1 child.
            root->right = delNode(root->right, root->data);
        }
        
        // Return the (potentially updated) current node pointer.
        return root;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to insert nodes into BST for testing
Node* insertBST(Node* root, int val) {
    if (root == nullptr) return new Node(val);
    if (val < root->data) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

// Helper function: Inorder Traversal to verify BST property
void inorderPrint(Node* root) {
    if (root == nullptr) return;
    inorderPrint(root->left);
    cout << root->data << " ";
    inorderPrint(root->right);
}

int main() {
    Solution solver;
    Node* root = nullptr;

    /* TEST CASE SETUP: Constructing the BST
     * 5
     * / \
     * 3   6
     * / \   \
     * 2   4   7
     */
    root = insertBST(root, 5);
    insertBST(root, 3);
    insertBST(root, 6);
    insertBST(root, 2);
    insertBST(root, 4);
    insertBST(root, 7);

    cout << "INITIATING BST NODE REMOVAL PROTOCOL (SUCCESSOR STRATEGY)..." << endl;
    cout << "Initial BST State (Inorder): ";
    inorderPrint(root);
    cout << endl << "-----------------------------" << endl;

    // Test Case: Deleting a node with two children (Node 3)
    // Successor of 3 is 4. Value 3 is replaced by 4, then original 4 is deleted.
    int keyToDelete = 3;
    cout << "Executing deletion of key: " << keyToDelete << endl;
    root = solver.delNode(root, keyToDelete);

    /* Expected structure after deleting 3 using successor value replacement:
     * 5
     * / \
     * 4   6
     * /     \
     * 2       7
     * (Node 3's value became 4, original node 4 was deleted)
     */

    // Verification
    cout << "BST State After Deletion (Inorder): ";
    inorderPrint(root);
    cout << endl;
    // Expected Output: 2 4 5 6 7 (Sorted order confirms valid BST)

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    return 0;
}
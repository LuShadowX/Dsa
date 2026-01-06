/**
 * @file flattening_linked_list.cpp
 * @author LuShadowX
 * @brief Flatten a linked list with 'next' and 'bottom' pointers into a single sorted list.
 * @problem_link: https://www.geeksforgeeks.org/problems/flattening-a-linked-list/1
 * @difficulty: Medium (Rank B)
 * @tags: Linked List, Recursion, Merge Sort, Flattening
 * @logic: The problem is to merge K sorted lists. We use a recursive approach.
 * The main `flatten` function recursively goes to the end of the main list (linked by `next`).
 * As the recursion returns, it merges the current list (`root`) with the already flattened
 * list from its right (`root->next`). This is done using a helper `mergethem` function,
 * which is a standard two-pointer merge for sorted lists, but using `bottom` pointers.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Structure]
 * The input is a main linked list where each node contains:
 * - `data`: The value.
 * - `next`: Points to the head of the next list in the horizontal chain.
 * - `bottom`: Points to the next node in its own sorted vertical list.
 *
 * [The Strategy: Recursive Bottom-Up Merge]
 * We treat this as merging the last list with the second-to-last, then merging
 * that result with the third-to-last, and so on, until we merge with the first list.
 *
 * Let L₁, L₂, ..., Lₖ be the K vertical lists.
 * 1. Recursively call flatten(L₂). This will eventually return the merged result of L₂...Lₖ.
 * 2. Merge L₁ with the result from step 1.
 *
 * [The Merge Operation (`mergethem`)]
 * This helper function takes two heads of sorted vertical lists and merges them
 * into one sorted vertical list.
 * - It uses a dummy node for easier head management.
 * - It iterates through both lists using `bottom` pointers, always picking the smaller node.
 * - CRITICAL STEP: After merging, it sets `result->next = NULL`. This disconnects
 * the horizontal `next` pointers, ensuring the final list is a single vertical line.
 *
 * [Time Complexity Analysis]
 * Let K be the number of lists in the horizontal chain.
 * Let N be the total number of nodes across all lists.
 * The nodes from the last two lists are merged once. The result is then merged
 * with the third-to-last list, and so on. In the worst case, the nodes from the
 * rightmost lists are processed multiple times in subsequent merges.
 * The time complexity is O(N * K), where N is total nodes and K is number of horizontal lists.
 * (A more efficient approach using a priority queue would be O(N log K)).
 *
 * [Space Complexity Analysis]
 * The recursion goes K levels deep, one for each list in the horizontal chain.
 * Total Auxiliary Space: S(K) = O(K) for the recursion stack.
 * ============================================================================
 */

/**
 * MISSION: Multi-Level List Flattening Protocol
 * RANK: B (Complex Recursive Merge)
 * DEPARTMENT: Linear Data Structures & Recursive Sorting
 * CHALLENGE:
 * Given a linked list where every node represents a linked list and contains two
 * pointers:
 * (i) `next`: Points to the next node in the main list.
 * (ii) `bottom`: Points to a linked list where every node is sorted in descending order.
 * Flatten the entire structure into a single linked list, sorted in ascending order, Let's assume the bottom is sorted in ascending order as per the problem statement.
 * using the `bottom` pointers.
 * CONSTRAINTS:
 * - Time Complexity: O(Total Nodes * Number of Lists).
 * - Space Complexity: O(Number of Lists) for recursion stack.
 */

#include <iostream>

using namespace std;

// Standard definition for the special Node structure.
struct Node {
    int data;
    Node* next;
    Node* bottom;

    Node(int x) {
        data = x;
        next = NULL;
        bottom = NULL;
    }
};

class Solution {
private:
    /**
     * Helper function to merge two sorted linked lists using 'bottom' pointers.
     * @param root The head of the first sorted list.
     * @param rootnext The head of the second sorted list.
     * @return The head of the merged sorted list.
     */
    Node* mergethem(Node* root, Node* rootnext) {
        // Base cases: if one list is empty, return the other.
        if (root == NULL) return rootnext;
        if (rootnext == NULL) return root;

        // Use a dummy node to simplify building the merged list.
        Node* result = new Node(-1);
        Node* store = result; // Keep track of the dummy to return its bottom later.

        // Standard two-pointer merge logic.
        while (root && rootnext) {
            if (root->data <= rootnext->data) {
                result->bottom = root;
                root = root->bottom;
            } else {
                result->bottom = rootnext;
                rootnext = rootnext->bottom;
            }
            result = result->bottom;
        }

        // Attach any remaining part of the non-empty list.
        if (root) {
            result->bottom = root;
        }
        if (rootnext) {
            result->bottom = rootnext;
        }

        // CRITICAL: Break the horizontal 'next' link for the newly merged list.
        // The flattened list should only be connected via 'bottom'.
        result->next = NULL;

        // Return the actual head of the merged list.
        return store->bottom;
    }

public:
    /**
     * Flattens the multi-level linked list into a single sorted list.
     * @param root The head of the main linked list.
     * @return The head of the flattened, sorted list.
     */
    Node* flatten(Node* root) {
        // Base case: if list is empty or has only one vertical list, it's already flattened.
        if (root == NULL || root->next == NULL) {
            return root;
        }

        // RECURSIVE STEP:
        // 1. Recursively flatten the rest of the list starting from root->next.
        root->next = flatten(root->next);

        // 2. Merge the current list (root) with the now-flattened rest of the list.
        root = mergethem(root, root->next);

        // Return the head of the newly merged, larger list.
        return root;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper to print the list using 'bottom' pointers
void printList(Node* head) {
    Node* temp = head;
    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->data << (temp->bottom != nullptr ? " -> " : "");
        temp = temp->bottom;
    }
    cout << " ]" << endl;
}

int main() {
    Solution solver;

    cout << "INITIATING MULTI-LEVEL LIST FLATTENING..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE: Creating a complex multi-level list
    // L1: 5 -> 7 -> 8 -> 30
    Node* head1 = new Node(5);
    head1->bottom = new Node(7);
    head1->bottom->bottom = new Node(8);
    head1->bottom->bottom->bottom = new Node(30);

    // L2: 10 -> 20
    Node* head2 = new Node(10);
    head2->bottom = new Node(20);

    // L3: 19 -> 22 -> 50
    Node* head3 = new Node(19);
    head3->bottom = new Node(22);
    head3->bottom->bottom = new Node(50);

    // L4: 28 -> 35 -> 40 -> 45
    Node* head4 = new Node(28);
    head4->bottom = new Node(35);
    head4->bottom->bottom = new Node(40);
    head4->bottom->bottom->bottom = new Node(45);

    // Connect the lists horizontally
    head1->next = head2;
    head2->next = head3;
    head3->next = head4;

    cout << "Structure constructed. Executing flatten()..." << endl;

    // Execute the flattening operation
    Node* flattenedHead = solver.flatten(head1);

    cout << "Flattened List: ";
    printList(flattenedHead);

    // Verification: Expected sorted sequence
    // 5, 7, 8, 10, 19, 20, 22, 28, 30, 35, 40, 45, 50
    Node* temp = flattenedHead;
    int lastVal = -1;
    bool sorted = true;
    int count = 0;
    while(temp != NULL) {
        if (temp->data < lastVal) {
            sorted = false;
            break;
        }
        lastVal = temp->data;
        temp = temp->bottom;
        count++;
    }

    if (sorted && count == 13) {
        cout << "Verification: SUCCESS - List is fully flattened and sorted." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup is complex and omitted for brevity.

    return 0;
}
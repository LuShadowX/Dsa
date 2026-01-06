/**
 * @file count_nodes_linked_list.cpp
 * @author LuShadowX
 * @brief Determine the total number of nodes present in a singly linked list.
 * @problem_link: https://www.geeksforgeeks.org/problems/count-nodes-of-linked-list/1
 * @difficulty: Easy (Rank C)
 * @tags: Linked List, Traversal, Iteration, Basic Operation
 * @logic: Performs a complete linear traversal of the list.
 * 1. Initialize a counter variable to zero.
 * 2. Use a pointer to iterate through the list starting from the head.
 * 3. While the current pointer is not NULL indicating a valid node exists:
 * a. Increment the counter.
 * b. Move the pointer to the next node.
 * 4. Return the final counter value.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [Linear Traversal Requirement]
 * A singly linked list does not store its size as metadata. To determine the
 * count, we must visit every node sequentially from the head to the tail.
 *
 * Mathematical representation of the operation:
 * Count C = Σ (1 for each node Nᵢ in the sequence N₀ → N₁ → ... → NULL)
 *
 * [Time Complexity Analysis]
 * We perform a constant time operation (increment and pointer move) for every
 * node in the list.
 * Total Time: T(N) = O(N), where N is the number of nodes.
 *
 * [Space Complexity Analysis]
 * The algorithm uses a fixed number of variables (count, pointer) regardless of
 * the list size.
 * Total Auxiliary Space: S(N) = O(1) (Constant Space).
 * ============================================================================
 */

/**
 * MISSION: Linked List Enumeration Protocol
 * RANK: C (Foundational List Operation)
 * DEPARTMENT: Linear Data Structures & Metrics
 * CHALLENGE:
 * Given the head pointer of a singly linked list, calculate and return the
 * total number of nodes contained within the list.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(1) required.
 */

#include <iostream>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct Node {
    int data;
    Node* next;
    // Constructor
    Node(int x) : data(x), next(NULL) {}
};

class Solution {
public:
    /**
     * Counts the number of nodes in the linked list.
     * @param head The head pointer of the linked list.
     * @return The integer count of nodes.
     */
    int getCount(Node* head) {
        int count = 0; // Initialize counter accumulator

        // Initialize traversal pointer.
        // Note: The provided code uses the local 'head' pointer directly for traversal.
        // Node* temp = head; (Unused in the logic loop below)

        // Iterate as long as current node exists
        while (head != NULL) {
            count++;          // Register existence of current node
            head = head->next; // Advance to the next node
        }

        // Return final accumulated count
        return count;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    cout << "INITIATING LINKED LIST ENUMERATION..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Non-empty list (10 -> 20 -> 30)
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);

    cout << "Test Case 1: List [ 10 -> 20 -> 30 ]" << endl;
    int count1 = solver.getCount(head);
    cout << "Detected Count: " << count1 << endl;

    if (count1 == 3) {
        cout << "Verification: SUCCESS." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: Empty list
    Node* emptyHead = NULL;
    cout << "Test Case 2: Empty List []" << endl;
    int count2 = solver.getCount(emptyHead);
    cout << "Detected Count: " << count2 << endl;

    if (count2 == 0) {
        cout << "Verification: SUCCESS - Handled NULL head correctly." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory Cleanup omitted for brevity in competitive context.

    return 0;
}
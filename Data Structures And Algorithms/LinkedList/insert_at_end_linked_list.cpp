/**
 * @file insert_at_end_linked_list.cpp
 * @author LuShadowX
 * @brief Insert a new node at the tail end of a Singly Linked List.
 * @problem_link: https://www.geeksforgeeks.org/problems/linked-list-insertion/1
 * @difficulty: Easy (Rank C)
 * @tags: Linked List, Insertion, Traversal
 * @logic: The operation requires finding the last node in the list to attach the new node.
 * 1. Create the new node with the given data.
 * 2. Handle Edge Case: If the list is empty (head is NULL), the new node becomes the head.
 * 3. Traversal: If the list is not empty, initialize a temporary pointer at the head.
 * 4. Iterate using a while loop until the temporary pointer reaches the last node (where temp->next is NULL).
 * 5. Link the last node's 'next' pointer to the new node.
 * 6. Return the original head pointer (unless it was updated in step 2).
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [Sequential Access Limitation]
 * Unlike arrays which allow O(1) random access to the last element (if size is known),
 * a singly linked list only holds a reference to the head. To access the tail,
 * we must sequentially traverse every node from the start.
 *
 * Current List: N₀ → N₁ → ... → Nₖ₋₁ → NULL (Tail is Nₖ₋₁)
 * New Node: N_new
 * Operation: Find Nₖ₋₁, then set Nₖ₋₁ → N_new → NULL.
 *
 * [Time Complexity Analysis]
 * To find the end of the list, we must visit every existing node exactly once.
 * - New Node Creation: O(1)
 * - Traversal to Tail: O(N), where N is the current number of nodes.
 * - Linking Step: O(1)
 * Total Time: T(N) = O(N).
 *
 * [Space Complexity Analysis]
 * The algorithm uses a single temporary pointer ('temp') for traversal, regardless
 * of the list size.
 * Total Auxiliary Space: S(N) = O(1) (Constant Space).
 * ============================================================================
 */

/**
 * MISSION: Linked List Tail Annexation Protocol
 * RANK: C (Foundational List Operation)
 * DEPARTMENT: Linear Data Structures & Dynamic Memory
 * CHALLENGE:
 * Given the head pointer of a singly linked list and an integer value 'x',
 * create a new node containing 'x' and insert it at the very end of the list.
 * Return the head pointer of the modified list.
 * CONSTRAINTS:
 * - Time Complexity: O(N) allowed due to necessary traversal.
 * - Space Complexity: O(1) auxiliary space required.
 */

#include <iostream>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct Node {
    int data;
    Node* next;
    // Constructors
    Node() : data(0), next(NULL) {}
    Node(int x) : data(x), next(NULL) {}
};

class Solution {
public:
    /**
     * Appends a new node to the end of the linked list.
     * @param head The current head pointer of the list.
     * @param x The data value for the new node.
     * @return The head pointer of the modified list.
     */
    Node *insertAtEnd(Node *head, int x) {
        // 1. Allocate memory for the new node and set its data.
        Node* newnode = new Node(x);

        // 2. CRITICAL EDGE CASE: If the list is currently empty.
        if (head == NULL) {
            // The new node becomes the head of the list.
            return newnode;
        }

        // 3. Initialize traversal pointer at the start.
        Node* temp = head;

        // 4. Traverse to find the tail node.
        // Stop when 'temp' is pointing to the node whose 'next' is NULL.
        while (temp->next != NULL) {
            temp = temp->next;
        }

        // 5. Link the current tail node to the new node.
        temp->next = newnode;

        // 6. Return the original head pointer as it hasn't changed.
        return head;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to print Linked List for verification
void printList(Node* head) {
    Node* temp = head;
    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->data << (temp->next != nullptr ? " -> " : "");
        temp = temp->next;
    }
    cout << " ]" << endl;
}

int main() {
    Solution solver;

    cout << "INITIATING LINKED LIST TAIL ANNEXATION..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Insertion into an EMPTY list
    cout << "Test Case 1: Inserting 10 into an empty list." << endl;
    Node* head = NULL; // Start empty
    head = solver.insertAtEnd(head, 10);
    cout << "Result Status: ";
    printList(head);
    // Verification: Head should now point to node 10.
    if (head != NULL && head->data == 10 && head->next == NULL) {
        cout << "Verification: SUCCESS - Handled empty list correctly." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;


    // TEST CASE 2: Insertion into an EXISTING list
    cout << "Test Case 2: Appending 20 and 30 to current list." << endl;
    head = solver.insertAtEnd(head, 20);
    head = solver.insertAtEnd(head, 30);

    cout << "Result Status: ";
    printList(head);

    // Verification: Last node should be 30.
    Node* temp = head;
    while(temp->next != NULL) temp = temp->next;
    
    if (temp->data == 30) {
        cout << "Verification: SUCCESS - New nodes appended correctly to tail." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory Cleanup omitted for brevity in competitive context.

    return 0;
}
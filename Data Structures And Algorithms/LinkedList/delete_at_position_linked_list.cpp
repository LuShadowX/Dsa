/**
 * @file delete_at_position_linked_list.cpp
 * @author LuShadowX
 * @brief Delete a node at a specific 1-based position in a Singly Linked List.
 * @problem_link: https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1
 * @difficulty: Easy-Medium (Rank C+)
 * @tags: Linked List, Deletion, Pointer Manipulation
 * @logic: The operation requires distinct handling for the head versus internal nodes.
 * 1. Case x=1 (Head Deletion): Update the head pointer to skip the first node.
 * 2. Case x>1 (Internal/Tail Deletion): Traverse the list to find the node at
 * position (x-1) (the predecessor). Reroute the predecessor's 'next' pointer
 * to skip the target node (position x) and point directly to position (x+1).
 * The strategy uses a counter initialized to 2 to stop the traversal pointer
 * at the predecessor node.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [Pointer Rerouting Principle]
 * Deleting a node $N_x$ from a sequence $N_{x-1} \rightarrow N_x \rightarrow N_{x+1}$
 * requires altering the link of the predecessor $N_{x-1}$.
 *
 * Operation: Set $N_{x-1} \rightarrow next$ to point to $N_{x+1}$.
 *
 * To perform this, we must have a pointer currently referencing $N_{x-1}$.
 *
 * [Time Complexity Analysis]
 * We iterate through the list until we reach position 'x'.
 * - Best Case (x=1): O(1)
 * - Worst Case (x=N or x > N): O(N) traversal.
 * Total Time: T(N) = O(N).
 *
 * [Space Complexity Analysis]
 * The algorithm uses a fixed number of pointer variables for traversal.
 * Total Auxiliary Space: S(N) = O(1).
 * ============================================================================
 */

/**
 * MISSION: Linked List Surgical Extraction Protocol
 * RANK: C+ (Positional Modification)
 * DEPARTMENT: Linear Data Structures & Dynamic Memory
 * CHALLENGE:
 * Given the head pointer of a singly linked list and an integer position 'x' (1-based),
 * delete the node at that specific position. Return the head pointer of the
 * modified list.
 * CONSTRAINTS:
 * - 1 <= x <= size of the list.
 * - Time Complexity: O(N) allowed.
 * - Space Complexity: O(1) required.
 */

#include <iostream>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct Node {
    int data;
    Node* next;
    // Constructor
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class Solution {
public:
    /**
     * Deletes the node at position x.
     * @param head The current head pointer of the list.
     * @param x The 1-based index of the node to remove.
     * @return The head pointer of the modified list.
     */
    Node* deleteNode(Node* head, int x) {
        Node* temp = head; // Initialize traversal pointer
        
        // Initialize counter to 2. This strategy helps stop 'temp' at position x-1.
        int count = 2; 

        // Handle empty list case implicitly (loop won't run, returns NULL head).

        // Traverse the list
        while (temp != NULL) {
            // CASE 1: Deleting the Head node (position 1)
            if (x == 1) {
                // Move head pointer to the second node.
                head = head->next;
                // Note: Memory of original head is not freed here (possible memory leak in production).
                return head;
            }
            // CASE 2: Deleting internal or tail node (position > 1)
            // This condition triggers when 'temp' is at position (x-1).
            else if (count == x) {
                // Reroute pointers: skip the next node (the target at pos x).
                // Ensure temp->next is not NULL before dereferencing.
                if (temp->next != NULL) {
                     temp->next = temp->next->next;
                }
                // Once deleted, we can stop traversal.
                break; 
            }
            
            // Advance counter and pointer
            count++;
            temp = temp->next;
        }
        
        // Return the (potentially unmodified) head pointer.
        return head;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to print Linked List
void printList(Node* head) {
    Node* temp = head;
    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->data << (temp->next != nullptr ? " -> " : "");
        temp = temp->next;
    }
    cout << " ]" << endl;
}

// Helper to create a simple list 10->20->30->40->50
Node* createTestList() {
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);
    head->next->next->next->next = new Node(50);
    return head;
}

int main() {
    Solution solver;

    cout << "INITIATING LINKED LIST SURGICAL EXTRACTION..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Delete Head (Position 1)
    Node* head1 = createTestList();
    cout << "Initial List 1: "; printList(head1);
    cout << "Action: Delete Position 1" << endl;
    head1 = solver.deleteNode(head1, 1);
    cout << "Result List 1:  "; printList(head1);
    // Verification: Should be 20->30->40->50
    if (head1->data == 20) cout << "Verification: SUCCESS" << endl; else cout << "Verification: FAILURE" << endl;
    cout << "-----------------------------" << endl;


    // TEST CASE 2: Delete Middle (Position 3)
    Node* head2 = createTestList();
    cout << "Initial List 2: "; printList(head2);
    cout << "Action: Delete Position 3 (Value 30)" << endl;
    head2 = solver.deleteNode(head2, 3);
    cout << "Result List 2:  "; printList(head2);
    // Verification: Should be 10->20->40->50
    if (head2->next->next->data == 40) cout << "Verification: SUCCESS" << endl; else cout << "Verification: FAILURE" << endl;
    cout << "-----------------------------" << endl;

    cout << "MISSION COMPLETE." << endl;

    // Memory Cleanup omitted for brevity.

    return 0;
}
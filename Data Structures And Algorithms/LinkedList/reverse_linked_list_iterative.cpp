/**
 * @file reverse_linked_list_iterative.cpp
 * @author LuShadowX
 * @brief Reverse a Singly Linked List using an iterative approach.
 * @problem_link: https://www.geeksforgeeks.org/problems/reverse-a-linked-list/1
 * @difficulty: Easy-Medium (Rank C+)
 * @tags: Linked List, In-place Reversal, Iteration, Two Pointers (actually Three)
 * @logic: Utilizes a three-pointer strategy to traverse the list once and reverse
 * links on the fly.
 * 1. 'pre' (Previous): Tracks the node behind the current one. Initially NULL.
 * 2. 'temp' (Current): Tracks the node currently being processed. Initially Head.
 * 3. 'nextt' (Next Temporary): Saves the pointer to the *rest* of the list before
 * we change the current node's 'next' pointer.
 *
 * The loop performs a 4-step dance: Save Next -> Reverse Link -> Shift 'pre' -> Shift 'temp'.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [State Transformation]
 * We transform the structural relationships between nodes from a forward sequence
 * to a backward sequence without allocating new nodes.
 *
 * Initial State: N₁ → N₂ → N₃ → ... → Nₖ → NULL
 * Final State:   NULL ← N₁ ← N₂ ← N₃ ← ... ← Nₖ (Head is now Nₖ)
 *
 * [The 4-Step Iterative Dance]
 * Inside the loop, for current node 'temp':
 * 1. SAVE future path:    nextt = temp->next;
 * 2. REVERSE current link: temp->next = pre;
 * 3. MOVE prev forward:   pre = temp;
 * 4. MOVE curr forward:   temp = nextt;
 *
 * [Time Complexity Analysis]
 * We visit every node exactly once, performing O(1) pointer assignments.
 * Total Time: T(N) = O(N).
 *
 * [Space Complexity Analysis]
 * The algorithm operates "in-place", using only three fixed pointer variables
 * regardless of the list size.
 * Total Auxiliary Space: S(N) = O(1).
 * ============================================================================
 */

/**
 * MISSION: Linked List Inversion Protocol
 * RANK: C+ (Standard Interview Problem)
 * DEPARTMENT: Linear Data Structures & Pointer Manipulation
 * CHALLENGE:
 * Given the head pointer of a singly linked list, reverse the order of the nodes
 * within the list. Return the new head pointer of the reversed list.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(1) required (in-place).
 */

#include <iostream>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct Node {
    int data;
    Node* next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    /**
     * Reverses a singly linked list iteratively.
     * @param head The current head of the list.
     * @return The new head of the reversed list.
     */
    Node* reverseList(Node* head) {
        // 'temp' acts as the current pointer, starting at head.
        Node* temp = head;
        // 'pre' acts as the previous pointer. Initially NULL (new tail's next).
        Node* pre = NULL;
        // 'nextt' acts as temporary storage to not lose the rest of the list.
        Node* nextt = NULL;

        // Iterate until current pointer reaches the end (NULL).
        while (temp != NULL) {
            // 1. SAVE the next node before we break the link to it.
            nextt = temp->next;

            // 2. REVERSE the link. Point current node back to the previous node.
            temp->next = pre;

            // 3. SHIFT 'pre' forward to the current node.
            pre = temp;

            // 4. SHIFT 'temp' forward to the next node (saved in step 1).
            temp = nextt;
        }

        // At the end of the loop, 'temp' is NULL.
        // 'pre' is pointing to the last actual node processed, which is the new HEAD.
        return pre;
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

// Helper to create a simple list 1->2->3->4->5
Node* createTestList() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    return head;
}

int main() {
    Solution solver;

    cout << "INITIATING LINKED LIST INVERSION PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE: Standard 5-node list
    Node* head = createTestList();
    cout << "Original List: "; printList(head);

    cout << "Action: Execute Inversion" << endl;
    Node* newHead = solver.reverseList(head);

    cout << "Reversed List: "; printList(newHead);

    // Verification: New Head should be 5, next should be 4.
    if (newHead != NULL && newHead->data == 5 && newHead->next->data == 4) {
        cout << "Verification: SUCCESS - List order reversed correctly." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    cout << "MISSION COMPLETE." << endl;

    // Memory Cleanup omitted for brevity.

    return 0;
}
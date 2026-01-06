/**
 * @file remove_loop_linked_list.cpp
 * @author LuShadowX
 * @brief Detect and remove a cycle (loop) in a Singly Linked List.
 * @problem_link: https://www.geeksforgeeks.org/problems/remove-loop-in-linked-list/1
 * @difficulty: Medium (Rank B)
 * @tags: Linked List, Two Pointers, Floyd's Algorithm, Cycle Removal
 * @logic: The operation is performed in three distinct phases based on Floyd's algorithm:
 * 1. Detection: Use slow (1x) and fast (2x) pointers. If they meet, a loop exists.
 * 2. Locate Start: Reset 'fast' to head. Move both 'slow' and 'fast' 1 step at a time.
 * They will meet at the start node of the cycle.
 * 3. Remove: Keep 'fast' at the start node. Use 'slow' to traverse the loop until
 * it reaches the last node (where slow->next == fast). Set slow->next = NULL
 * to break the cycle.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION (Recap for Phase 2 & 3)
 * ============================================================================
 * [Finding the Start Node]
 * As proven in the "Cycle Entry Detection" mission, if we reset one pointer to
 * the Head and keep the other at the Meeting Point, moving both one step at a
 * time guarantees they meet exactly at the Cycle Start Node.
 *
 * [Breaking the Cycle]
 * A cycle exists because the "last" node in the logical sequence points back
 * to a previous node (the "Cycle Start Node").
 * To remove the loop, we must:
 * 1. Identify the Cycle Start Node (done in Phase 2).
 * 2. Find the node immediately preceding it within the loop structure.
 * 3. Change that predecessor's 'next' pointer to NULL.
 * ============================================================================
 */

/**
 * MISSION: Linked List Cycle Neutralization Protocol
 * RANK: B (Multi-stage Pointer Manipulation)
 * DEPARTMENT: Linear Data Structures & Structural Repair
 * CHALLENGE:
 * Given the head pointer of a singly linked list, check if a loop exists.
 * If a loop exists, modify the list structure to remove the loop, restoring it
 * to a standard linear linked list terminated by NULL.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(1) required.
 * - The structure must be modified in-place.
 */

#include <iostream>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
public:
    /**
     * Removes the loop from the linked list if one exists.
     * @param head The head pointer of the linked list.
     */
    void removeLoop(Node* head) {
        // Base Case: Empty list or single node list cannot have a loop.
        if (head == NULL || head->next == NULL) return;

        Node* fast = head;
        Node* slow = head;
        bool find = false;

        // ==========================================
        // Phase 1: Detection (Tortoise and Hare)
        // ==========================================
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next; // Move 2 steps
            slow = slow->next;       // Move 1 step
            
            // Collision detected inside the loop
            if (fast == slow) {
                find = true;
                break;
            }
        }

        // If the loop finished without collision, no cycle exists. Exit.
        // (Note: The provided code checks fast/fast->next again, which works but checking 'find' is cleaner)
        if (fast == NULL || fast->next == NULL) return;

        // ==========================================
        // Phase 2: Locate the Cycle Start Node
        // ==========================================
        // Reset fast pointer to head.
        fast = head;
        // Move both pointers one step at a time until they meet again.
        // The provided loop condition is slightly unusual but functionally finds meeting point.
        while (fast != NULL && fast->next != NULL) {
            // If they meet, 'fast' is pointing to the Cycle Start Node.
            if (fast == slow) break; 
            fast = fast->next;
            slow = slow->next;
        }
        
        // At this point, 'fast' pointer is at the start node of the cycle.

        // ==========================================
        // Phase 3: Find the Last Node and Break Cycle
        // ==========================================
        // Use 'slow' to traverse the loop. Stop when 'slow->next' points to the start node ('fast').
        while (slow->next != fast) {
            slow = slow->next;
        }
        
        // 'slow' is now at the last node of the loop.
        // Sever the link to break the cycle.
        slow->next = NULL;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper to print list (safely stops at a reasonable limit if loop exists)
void printListSafe(Node* head) {
    Node* temp = head;
    int limit = 20; // Safety limit to prevent infinite printing if loop exists
    int count = 0;
    cout << "[ ";
    while (temp != nullptr && count < limit) {
        cout << temp->data << (temp->next != nullptr ? " -> " : "");
        temp = temp->next;
        count++;
    }
    if (temp != nullptr) cout << "... (Loop or long list detected)";
    cout << " ]" << endl;
}

// Helper to create a list with a specific cycle start for testing.
// Structure: 1 -> 2 -> 3 -> [4 -> 5 -> 6 -> (back to 4)]
Node* createLoopedList() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    Node* startNode = new Node(4); // Cycle starts here
    head->next->next->next = startNode;
    startNode->next = new Node(5);
    Node* endNode = new Node(6);
    startNode->next->next = endNode;
    // Create the loop: 6 points back to 4
    endNode->next = startNode;
    return head;
}

int main() {
    Solution solver;

    cout << "INITIATING CYCLE NEUTRALIZATION PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE: List with a loop
    cout << "Test Case: Looped list (1->2->3->[4->5->6->4...])" << endl;
    Node* head = createLoopedList();
    cout << "Initial State (Safe Print): ";
    printListSafe(head);

    cout << "Action: Executing removeLoop()" << endl;
    solver.removeLoop(head);

    cout << "Final State (Standard Print): ";
    // If successful, this print function will terminate naturally at NULL.
    Node* temp = head;
    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->data << (temp->next != nullptr ? " -> " : "");
        temp = temp->next;
    }
    cout << " ]" << endl;

    // Verification: Check if the last node's next is NULL
    Node* check = head;
    while(check != nullptr && check->next != nullptr) {
        check = check->next;
    }
    
    if (check != nullptr && check->next == nullptr && check->data == 6) {
         cout << "Verification: SUCCESS - Cycle neutralized, list terminated at node 6." << endl;
    } else {
         cout << "Verification: FAILURE - List not correctly terminated." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    return 0;
}
/**
 * @file find_middle_linked_list.cpp
 * @author LuShadowX
 * @brief Find the middle element of a Singly Linked List in one pass.
 * @problem_link: https://www.geeksforgeeks.org/problems/finding-middle-element-in-a-linked-list/1
 * @difficulty: Easy (Rank C)
 * @tags: Linked List, Two Pointers, Tortoise and Hare
 * @logic: Utilizes the Two-Pointer approach (Tortoise and Hare algorithm).
 * 1. Initialize two pointers, 'slow' and 'fast', both at the head.
 * 2. Iterate through the list. In each step, move 'slow' one node forward and
 * 'fast' two nodes forward.
 * 3. Ensure the loop continues only while 'fast' and 'fast->next' are valid
 * to prevent segmentation faults.
 * 4. When the 'fast' pointer reaches the end of the list, the 'slow' pointer
 * will have covered exactly half the distance, resting on the middle node.
 * (Note: For even-sized lists, it returns the second middle node).
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Relative Speed Principle]
 * Imagine a race track of length L.
 * Runner A (Fast) runs at speed 2v.
 * Runner B (Slow) runs at speed v.
 *
 * When Runner A finishes the race (distance L), Runner B will have run exactly
 * half that distance (L/2) in the same amount of time.
 *
 * Applying this to the list:
 * When the 'fast' pointer reaches the NULL terminator, the 'slow' pointer is
 * exactly halfway through the list structure.
 *
 * [Time Complexity Analysis]
 * The 'fast' pointer traverses the list once. The 'slow' pointer traverses half.
 * The dominant factor is the single pass.
 * Total Time: T(N) = O(N/2) -> O(N), where N is the number of nodes.
 *
 * [Space Complexity Analysis]
 * The algorithm uses only two fixed pointer variables regardless of list size.
 * Total Auxiliary Space: S(N) = O(1) (Constant Space).
 * ============================================================================
 */

/**
 * MISSION: Linked List Midpoint Navigation Protocol
 * RANK: C (Standard Efficient Algorithm)
 * DEPARTMENT: Linear Data Structures & Algorithmic Optimization
 * CHALLENGE:
 * Given the head pointer of a singly linked list, find and return the data value
 * of the middle node. If there are two middle nodes (even length list), return
 * the second middle node.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required (one pass).
 * - Space Complexity: O(1) required.
 */

#include <iostream>
#include <vector>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct Node {
    int data;
    Node* next;
    // Constructor
    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    /**
     * Finds the middle node's data using the two-pointer technique.
     * @param head The head pointer of the linked list.
     * @return The integer data of the middle node.
     */
    int getMiddle(Node* head) {
        // Initialize Tortoise (slow) and Hare (fast) pointers at the start.
        Node* fast = head;
        Node* slow = head;

        // Iterate while the fast pointer has not reached the end.
        // CRITICAL CHECK: We must verify both 'fast' (for even length termination)
        // and 'fast->next' (to safely take the second step).
        while (fast && fast->next) {
            slow = slow->next;       // Move slow pointer 1 step
            fast = fast->next->next; // Move fast pointer 2 steps
        }

        // At the end of the loop, 'slow' is pointing to the middle node.
        // (Implicit assumption: list is not empty, based on return type int).
        return slow->data;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper to create a list from a vector
Node* createList(const vector<int>& arr) {
    if (arr.empty()) return nullptr;
    Node* head = new Node(arr[0]);
    Node* tail = head;
    for (size_t i = 1; i < arr.size(); ++i) {
        tail->next = new Node(arr[i]);
        tail = tail->next;
    }
    return head;
}

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

int main() {
    Solution solver;

    cout << "INITIATING LINKED LIST MIDPOINT NAVIGATION..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Odd Length List (5 nodes)
    vector<int> dataOdd = {10, 20, 30, 40, 50};
    Node* headOdd = createList(dataOdd);
    cout << "Test Case 1 (Odd Length): "; printList(headOdd);
    int middleOdd = solver.getMiddle(headOdd);
    cout << "Calculated Middle: " << middleOdd << endl;
    
    // Verification: Middle of 5 nodes is the 3rd node (index 2).
    if (middleOdd == 30) cout << "Verification: SUCCESS" << endl; else cout << "Verification: FAILURE" << endl;
    cout << "-----------------------------" << endl;


    // TEST CASE 2: Even Length List (6 nodes)
    vector<int> dataEven = {1, 2, 3, 4, 5, 6};
    Node* headEven = createList(dataEven);
    cout << "Test Case 2 (Even Length): "; printList(headEven);
    // For even length, this implementation returns the second middle (4).
    int middleEven = solver.getMiddle(headEven);
    cout << "Calculated Middle: " << middleEven << endl;

    // Verification: Middle of 6 nodes are 3 and 4. Expecting 4.
    if (middleEven == 4) cout << "Verification: SUCCESS" << endl; else cout << "Verification: FAILURE" << endl;
    cout << "-----------------------------" << endl;

    cout << "MISSION COMPLETE." << endl;

    // Memory Cleanup omitted for brevity.

    return 0;
}
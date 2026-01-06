/**
 * @file add_two_numbers_linked_list.cpp
 * @author LuShadowX
 * @brief Add two numbers represented by linked lists (MSD first).
 * @problem_link: https://www.geeksforgeeks.org/problems/add-two-numbers-represented-by-linked-lists/1
 * @difficulty: Medium (Rank B)
 * @tags: Linked List, Math, Recursion, Two Pointers
 * @logic: The numbers are stored with the most significant digit at the head.
 * To perform addition from the least significant digit, we use a three-step
 * Reverse-Add-Reverse strategy:
 * 1. **Reverse** both input linked lists. Now the heads represent the units place.
 * 2. **Add** the two lists digit by digit, traversing them simultaneously.
 * Maintain a 'carry' for sums >= 10. Create a new list to store the sum digits.
 * 3. **Reverse** the resulting sum list to restore the correct order (MSD at head).
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Alignment Problem]
 * Standard addition requires aligning numbers by their place value (units, tens, etc.).
 *
 * 4 5 (List 1: 4 -> 5)
 * + 3 4 5 (List 2: 3 -> 4 -> 5)
 * -------
 *
 * The linked list representation `MSD -> ... -> LSD` makes this alignment difficult.
 * Reversing them transforms the problem:
 *
 * List 1 (rev): 5 -> 4
 * List 2 (rev): 5 -> 4 -> 3
 *
 * Now, the heads (both '5') are the units digits, and we can add them directly.
 *
 * [The Addition Loop Condition]
 * The loop `while(t1 || t2 || carry)` is critical. Consider 99 + 1:
 * Rev lists: `9->9` and `1`.
 * - Iter 1: 9+1 = 10. Node=0, Carry=1.
 * - Iter 2: 9+0 + Carry(1) = 10. Node=0, Carry=1.
 * - Lists are now empty (t1=NULL, t2=NULL).
 * - The loop MUST run one more time because `carry` is 1, to create the final
 * '1' node for the result '100'.
 *
 * [Time Complexity Analysis]
 * 1. Reverse L1: O(N)
 * 2. Reverse L2: O(M)
 * 3. Add lists: O(max(N, M))
 * 4. Reverse result: O(max(N, M))
 * Total Time: T(N, M) = O(N + M).
 *
 * [Space Complexity Analysis]
 * We create a new list for the result, whose length is at most max(N, M) + 1.
 * Total Auxiliary Space: S(N, M) = O(N + M) for the new list.
 * ============================================================================
 */

/**
 * MISSION: Linked List Arithmetic Addition Protocol
 * RANK: B (Multi-stage Transformation & Math)
 * DEPARTMENT: Linear Data Structures & Numerical Algorithms
 * CHALLENGE:
 * Given two singly linked lists representing two non-negative integers, where
 * each node contains a single digit and the most significant digit is at the head,
 * return a linked list that represents the sum of these two numbers.
 * CONSTRAINTS:
 * - Time Complexity: O(N + M) required.
 * - Space Complexity: O(N + M) allowed for the result list.
 */

#include <iostream>
#include <vector>

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
private:
    /**
     * Helper function to reverse a singly linked list.
     * @param head The head of the list to reverse.
     * @return The new head of the reversed list.
     */
    Node* reverseList(Node* head) {
        Node* prev = NULL;
        Node* curr = head;
        Node* nextt = NULL;
        while (curr != NULL) {
            nextt = curr->next; // Save next node
            curr->next = prev;  // Reverse link
            prev = curr;        // Move prev forward
            curr = nextt;       // Move curr forward
        }
        return prev; // 'prev' is the new head
    }

public:
    /**
     * Adds two numbers represented by linked lists.
     * @param head1 The head of the first number's list.
     * @param head2 The head of the second number's list.
     * @return The head of the result list representing the sum.
     */
    Node* addTwoLists(Node* head1, Node* head2) {
        // STEP 1: Reverse both input lists to align by least significant digit.
        head1 = reverseList(head1);
        head2 = reverseList(head2);

        Node* temp1 = head1;
        Node* temp2 = head2;
        int carry = 0;

        // Create a dummy node to simplify building the result list.
        Node* dummy = new Node(-1);
        Node* current = dummy; // Pointer to the tail of the result list.

        // STEP 2: Perform digit-by-digit addition.
        // Continue as long as there are digits left or a remaining carry.
        while (temp1 || temp2 || carry > 0) {
            int sum = carry; // Start with carry from previous step.
            
            if (temp1) {
                sum += temp1->data;
                temp1 = temp1->next;
            }
            if (temp2) {
                sum += temp2->data;
                temp2 = temp2->next;
            }

            // The new digit is sum % 10.
            current->next = new Node(sum % 10);
            current = current->next;
            
            // The new carry is sum / 10.
            carry = sum / 10;
        }

        // The actual result list (still reversed) starts after the dummy.
        Node* resultHead = dummy->next;
        // Note: In production, delete the dummy node here.

        // STEP 3: Reverse the result list to restore the correct order.
        resultHead = reverseList(resultHead);

        // OPTIONAL STEP: Remove leading zeros from the final result.
        // E.g., if result is 0->0->7, make it 7. But keep a single 0->NULL.
        Node* temp = resultHead;
        while (temp != NULL && temp->data == 0 && temp->next != NULL) {
            temp = temp->next;
        }
        // The new head is the first non-zero node, or the last '0' node.
        resultHead = temp;

        return resultHead;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper to create list from vector
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
    while (temp != nullptr) {
        cout << temp->data;
        temp = temp->next;
    }
    cout << endl;
}

// Helper to verify list content
bool verifyList(Node* head, const vector<int>& expected) {
    Node* temp = head;
    for (int val : expected) {
        if (temp == nullptr || temp->data != val) return false;
        temp = temp->next;
    }
    return temp == nullptr;
}

int main() {
    Solution solver;

    cout << "INITIATING LINKED LIST ARITHMETIC ADDITION..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: General addition with uneven lengths
    // 45 + 345 = 390
    Node* num1 = createList({4, 5});
    Node* num2 = createList({3, 4, 5});
    cout << "  " << 45 << endl << "+ " << 345 << endl << "-------" << endl;
    
    Node* result1 = solver.addTwoLists(num1, num2);
    cout << "Result: "; printList(result1);

    if (verifyList(result1, {3, 9, 0})) {
        cout << "Verification: SUCCESS" << endl;
    } else {
        cout << "Verification: FAILURE" << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: Carry creates a new most significant digit
    // 99 + 1 = 100
    Node* num3 = createList({9, 9});
    Node* num4 = createList({1});
    cout << "  " << 99 << endl << "+  " << 1 << endl << "-------" << endl;
    
    Node* result2 = solver.addTwoLists(num3, num4);
    cout << "Result: "; printList(result2);

    if (verifyList(result2, {1, 0, 0})) {
        cout << "Verification: SUCCESS - Carry handled correctly." << endl;
    } else {
        cout << "Verification: FAILURE" << endl;
    }
    cout << "-----------------------------" << endl;
    
    // TEST CASE 3: Adding Zero
    // 0 + 0 = 0
    Node* num5 = createList({0});
    Node* num6 = createList({0});
    cout << "  " << 0 << endl << "+ " << 0 << endl << "-------" << endl;

    Node* result3 = solver.addTwoLists(num5, num6);
    cout << "Result: "; printList(result3);

    if (verifyList(result3, {0})) {
        cout << "Verification: SUCCESS - Zero handled correctly." << endl;
    } else {
        cout << "Verification: FAILURE" << endl;
    }
    cout << "-----------------------------" << endl;


    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup omitted for brevity.

    return 0;
}
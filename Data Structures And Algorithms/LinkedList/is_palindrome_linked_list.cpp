/**
 * @file is_palindrome_linked_list.cpp
 * @author LuShadowX
 * @brief Determine if a singly linked list is a palindrome in O(N) time and O(1) space.
 * @problem_link: https://www.geeksforgeeks.org/problems/check-if-linked-list-is-palindrome/1
 * @difficulty: Medium (Rank B)
 * @tags: Linked List, Two Pointers, Reversal, Palindrome
 * @logic: The algorithm follows a three-phase strategy to avoid using extra space:
 * 1. **Find Middle:** Use slow and fast pointers to find the node just before the start of the second half.
 * 2. **Reverse Second Half:** Reverse the sub-list starting from the middle to the end.
 * 3. **Compare:** Traverse the first half and the reversed second half simultaneously. If all values match, it's a palindrome.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Space-Time Trade-off]
 * A palindrome reads the same forwards and backwards. For arrays, this is a simple
 * two-pointer check from both ends. For singly linked lists, we cannot traverse backwards.
 *
 * - Naive Approach (O(N) Space): Push all node values onto a stack. Iterate
 * through the list again, popping from the stack and comparing.
 *
 * - Optimal Approach (O(1) Space - Implemented Here): Instead of storing data
 * externally, we temporarily alter the list's structure to allow backward
 * traversal of the second half.
 *
 * [The Three Phases]
 * List: L₁ → L₂ → ... → L_mid → ... → Lₙ₋₁ → Lₙ
 *
 * Phase 1 (Split): Find split point 'S' (end of first half).
 * Phase 2 (Reverse): Reverse the part S->next ... Lₙ to get Lₙ → Lₙ₋₁ → ...
 * Phase 3 (Compare):
 * Pointer 1 starts at L₁.
 * Pointer 2 starts at Lₙ (new head of reversed half).
 * Compare P1->data vs P2->data, move both forward.
 *
 * [Time Complexity Analysis]
 * - Finding middle: O(N/2)
 * - Reversing second half: O(N/2)
 * - Comparing halves: O(N/2)
 * Total Time: T(N) = O(N).
 *
 * [Space Complexity Analysis]
 * The algorithm performs operations in-place using a fixed number of pointers.
 * Total Auxiliary Space: S(N) = O(1).
 * ============================================================================
 */

/**
 * MISSION: Linked List Palindrome Verification Protocol
 * RANK: B (Multi-stage Structural Manipulation)
 * DEPARTMENT: Linear Data Structures & Pattern Recognition
 * CHALLENGE:
 * Given the head of a singly linked list, determine if its sequence of values
 * forms a palindrome (reads the same forwards and backwards). Return true if it is,
 * false otherwise.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(1) required.
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
public:
    /**
     * Checks if the linked list is a palindrome.
     * @param head The head pointer of the linked list.
     * @return true if it's a palindrome, false otherwise.
     */
    bool isPalindrome(Node* head) {
        // Base case: Empty or single-node lists are palindromes.
        if (head == NULL || head->next == NULL) {
            return true;
        }

        // PHASE 1: FIND MIDDLE
        // Use tortoise and hare to find the end of the first half.
        Node* fast = head;
        Node* slow = head;
        // Condition ensures 'slow' stops right before the second half begins.
        while (fast->next != NULL && fast->next->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
        }

        // 'slow' is now at the split point. The second half starts at 'slow->next'.

        // PHASE 2: REVERSE SECOND HALF
        // Reuse 'fast' pointer to traverse the second half for reversal.
        fast = slow->next;
        Node* prev = NULL;
        Node* nextt = NULL;
        while (fast != NULL) {
            nextt = fast->next; // Store next node
            fast->next = prev;  // Reverse current link
            prev = fast;        // Move prev one step
            fast = nextt;       // Move current one step
        }
        // After reversal, 'prev' is the head of the reversed second half.

        // PHASE 3: COMPARE FIRST AND REVERSED SECOND HALVES
        fast = prev; // Pointer to start of reversed second half
        slow = head; // Pointer to start of first half

        // Iterate through the reversed second half (it might be shorter in odd-length lists)
        while (fast != NULL) {
            if (fast->data != slow->data) {
                return false; // Mismatch found, not a palindrome.
            }
            fast = fast->next;
            slow = slow->next;
        }

        // If loop completes without mismatches, it is a palindrome.
        // (Note: A robust solution would re-reverse the second half here to restore the list).
        return true;
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

int main() {
    Solution solver;

    cout << "INITIATING PALINDROME VERIFICATION PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Even length palindrome
    vector<int> data1 = {1, 2, 3, 3, 2, 1};
    Node* head1 = createList(data1);
    cout << "Test Case 1: [1 -> 2 -> 3 -> 3 -> 2 -> 1]" << endl;
    if (solver.isPalindrome(head1)) {
        cout << "Result: VALID PALINDROME. Verification: SUCCESS." << endl;
    } else {
        cout << "Result: INVALID. Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: Odd length non-palindrome
    vector<int> data2 = {1, 2, 3, 4, 5};
    Node* head2 = createList(data2);
    cout << "Test Case 2: [1 -> 2 -> 3 -> 4 -> 5]" << endl;
    if (!solver.isPalindrome(head2)) {
        cout << "Result: INVALID PALINDROME. Verification: SUCCESS." << endl;
    } else {
        cout << "Result: VALID. Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup omitted for brevity.

    return 0;
}
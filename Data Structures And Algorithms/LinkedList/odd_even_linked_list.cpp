/**
 * @file odd_even_linked_list.cpp
 * @author LuShadowX
 * @brief Reorder a singly linked list to group all odd-indexed nodes together followed by all even-indexed nodes.
 * @problem_link: https://leetcode.com/problems/odd-even-linked-list/
 * @difficulty: Medium (Rank B)
 * @tags: Linked List, Two Pointers, In-place Reordering
 * @logic: The problem requires grouping nodes based on their position index (1st, 2nd, 3rd...), not their values.
 * We use a two-pointer strategy to build two separate chains in-place:
 * 1. An 'odd' chain starting at the head (1st node).
 * 2. An 'even' chain starting at the second node.
 * We must save the head of the 'even' chain (`evenHead`) to connect it later.
 * We iterate through the list, re-linking nodes such that `odd->next` points to the next odd node (skipping one), and `even->next` points to the next even node.
 * Finally, we attach the head of the finished 'even' chain to the tail of the finished 'odd' chain.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Separation Strategy]
 * Initial: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
 *
 * We want to transform the links without creating new nodes:
 * Odd Chain becomes:  1 -> 3 -> 5 -> NULL
 * Even Chain becomes: 2 -> 4 -> NULL
 *
 * [The Pointer "Leapfrog"]
 * In each iteration, we make the pointers jump over their immediate neighbor:
 * - Current state: `odd` at N_i, `even` at N_{i+1}
 * - Action 1: `odd->next = even->next` (Links N_i to N_{i+2})
 * - Action 2: Advance `odd` to N_{i+2}
 * - Action 3: `even->next = odd->next` (Links N_{i+1} to N_{i+3})
 * - Action 4: Advance `even` to N_{i+3}
 *
 * [Time Complexity Analysis]
 * We traverse the list exactly once. Each node is processed a constant number of times.
 * Total Time: T(N) = O(N), where N is the number of nodes.
 *
 * [Space Complexity Analysis]
 * The reordering is done in-place by changing existing pointers. We use only a
 * few fixed auxiliary pointers (`odd`, `even`, `evenHead`).
 * Total Auxiliary Space: S(N) = O(1) (Constant Space).
 * ============================================================================
 */

/**
 * MISSION: Linked List Odd-Even Reordering Protocol
 * RANK: B (Structural Manipulation)
 * DEPARTMENT: Linear Data Structures & Pointer Arithmetic
 * CHALLENGE:
 * Given the head of a singly linked list, group all the nodes with odd indices
 * together followed by the nodes with even indices, and return the reordered list.
 * The first node is considered odd, the second even, and so on.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(1) required.
 * - The relative order inside both the even and odd groups should remain as it was in the input.
 */

#include <iostream>
#include <vector>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    /**
     * Reorders the list to place odd-indexed nodes before even-indexed nodes.
     * @param head The head of the singly linked list.
     * @return The head of the reordered list.
     */
    ListNode* oddEvenList(ListNode* head) {
        // --- STEP 1: BASE CASES ---
        // If the list is empty (NULL) or has only one node, no reordering is needed.
        if (head == NULL || head->next == NULL) return head;

        // --- STEP 2: INITIALIZE POINTERS ---
        // 'odd' starts at the 1st node.
        // 'even' starts at the 2nd node.
        ListNode* odd = head;
        ListNode* even = head->next;

        // CRITICAL: We must save the start of the even list.
        // Once we move the 'even' pointer during the loop, we will lose the 
        // reference to the start of the even chain. We need this to connect 
        // the end of the odd list to the start of the even list later.
        ListNode* evenHead = even;

        // --- STEP 3: THE REARRANGEMENT LOOP ---
        // We move in pairs. The condition 'even && even->next' ensures that
        // there is a subsequent 'odd' node to connect to.
        while (even != NULL && even->next != NULL) {
            
            // 1. Connect the current 'odd' node to the next 'odd' node.
            // (e.g., node 1 points to node 3)
            odd->next = even->next;
            
            // 2. Move the 'odd' pointer forward to the newly connected node.
            odd = odd->next;

            // 3. Connect the current 'even' node to the next 'even' node.
            // (e.g., node 2 points to node 4)
            // Note: odd->next at this point is already pointing to node 4.
            even->next = odd->next;

            // 4. Move the 'even' pointer forward to the newly connected node.
            even = even->next;
        }

        // --- STEP 4: CONNECT THE TWO LISTS ---
        // At this point, 'odd' points to the tail of the odd list, and 
        // 'even' points to the tail of the even list.
        // We link the tail of the odd list to the head of the even list.
        odd->next = evenHead;

        // We return 'head' because it is still the starting point of the 1st node (the overall head).
        return head;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper to create a list from a vector
ListNode* createList(const vector<int>& arr) {
    if (arr.empty()) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* tail = head;
    for (size_t i = 1; i < arr.size(); ++i) {
        tail->next = new ListNode(arr[i]);
        tail = tail->next;
    }
    return head;
}

// Helper function to print Linked List
void printList(ListNode* head) {
    ListNode* temp = head;
    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->val << (temp->next != nullptr ? " -> " : "");
        temp = temp->next;
    }
    cout << " ]" << endl;
}

// Helper to verify the result
bool verifyList(ListNode* head, const vector<int>& expected) {
    ListNode* temp = head;
    for (int val : expected) {
        if (temp == nullptr || temp->val != val) return false;
        temp = temp->next;
    }
    return temp == nullptr;
}

int main() {
    Solution solver;

    cout << "INITIATING LINKED LIST ODD-EVEN REORDERING..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Standard 5-node list
    vector<int> input1 = {1, 2, 3, 4, 5};
    vector<int> expected1 = {1, 3, 5, 2, 4};
    ListNode* head1 = createList(input1);

    cout << "Input List: "; printList(head1);
    
    cout << "Action: Executing oddEvenList()" << endl;
    head1 = solver.oddEvenList(head1);

    cout << "Result List: "; printList(head1);

    if (verifyList(head1, expected1)) {
        cout << "Verification: SUCCESS - List reordered correctly." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: Edge case with short list
    vector<int> input2 = {2, 1, 3};
    vector<int> expected2 = {2, 3, 1};
    ListNode* head2 = createList(input2);

    cout << "Input List 2: "; printList(head2);
    head2 = solver.oddEvenList(head2);
    cout << "Result List 2: "; printList(head2);

    if (verifyList(head2, expected2)) {
        cout << "Verification: SUCCESS." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup omitted for brevity.

    return 0;
}
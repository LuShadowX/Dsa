/**
 * @file remove_duplicates_sorted_list.cpp
 * @author LuShadowX
 * @brief Remove duplicate nodes from a sorted Singly Linked List.
 * @problem_link: https://www.geeksforgeeks.org/problems/remove-duplicate-element-from-sorted-linked-list/1
 * @difficulty: Easy (Rank C)
 * @tags: Linked List, Two Pointers, Sorting
 * @logic: Relies on the property that duplicates in a sorted list are adjacent.
 * Utilizes a two-pointer approach:
 * 1. 'slow' pointer tracks the last unique node added to the result list.
 * 2. 'fast' pointer iterates ahead.
 * 3. If 'fast' data matches 'fast->next' data, it's a duplicate sequence. Move 'fast' to skip.
 * 4. If they don't match, 'fast->next' is a new unique value. Advance 'fast' to it,
 * link 'slow->next' to this new 'fast', and advance 'slow'.
 * 5. Crucially, after the loop, terminate the list by setting 'slow->next = NULL'
 * to handle trailing duplicates.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Sorted Property Exploitation]
 * In list L = a₁ → a₂ → ... → aₙ, if L is sorted (aᵢ ≤ aᵢ₊₁), then aᵢ = aⱼ (with i<j)
 * implies aᵢ = aᵢ₊₁ = ... = aⱼ.
 * This means we only ever need to compare adjacent nodes (N vs N->next) to detect duplicates.
 *
 * [The Two-Pointer Strategy]
 * - The 'slow' pointer acts as the anchor of the "clean" list being built.
 * - The 'fast' pointer acts as a scout, identifying the next distinct value.
 *
 * [Time Complexity Analysis]
 * The 'fast' pointer traverses the list exactly once.
 * Total Time: T(N) = O(N), where N is the number of nodes.
 *
 * [Space Complexity Analysis]
 * The algorithm operates in-place, modifying existing links. It uses only two
 * fixed pointer variables regardless of input size.
 * Total Auxiliary Space: S(N) = O(1) (Constant Space).
 * ============================================================================
 */

/**
 * MISSION: Sorted List Deduplication Protocol
 * RANK: C (Foundational Optimization)
 * DEPARTMENT: Linear Data Structures & Data Cleaning
 * CHALLENGE:
 * Given the head pointer of a sorted singly linked list, delete all duplicate
 * values such that each element appears only once. Return the linked list sorted
 * as well.
 * CONSTRAINTS:
 * - The input list MUST be sorted.
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(1) required (in-place modification).
 */

#include <iostream>
#include <vector>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct Node {
    int data;
    struct Node *next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    /**
     * Removes duplicates from a sorted linked list.
     * @param head The head pointer of the sorted list.
     * @return The head pointer of the list with duplicates removed.
     */
    Node* removeDuplicates(Node* head) {
        // Base Case: Empty list or single node list has no duplicates.
        if (head == NULL || head->next == NULL) {
            return head;
        }

        Node* fast = head;
        Node* slow = head;

        // Iterate while 'fast' and its successor exist.
        while (fast && fast->next) {
            if (fast->data == fast->next->data) {
                // Duplicate detected ahead. Move 'fast' to skip current node.
                // 'slow' remains pointing at the last known unique node.
                fast = fast->next;
            } else {
                // Distinct value detected ahead.
                // 1. Move 'fast' to the new unique node.
                fast = fast->next;
                // 2. Link the 'slow' (tail of unique list) to this new unique node.
                slow->next = fast;
                // 3. Move 'slow' forward as this is now the new tail.
                slow = slow->next;
            }
        }
        
        // CRITICAL STEP: Terminate the list.
        // If the list ended with duplicates (e.g., 1->2->2->NULL), 'slow' is at the first '2',
        // and 'fast' ran off the end. We must ensure 'slow->next' is NULL to cut off the trailing '2'.
        slow->next = NULL;
        
        return head;
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
    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->data << (temp->next != nullptr ? " -> " : "");
        temp = temp->next;
    }
    cout << " ]" << endl;
}

// Helper to check list content against a vector
bool verifyList(Node* head, const vector<int>& expected) {
    Node* temp = head;
    for (int val : expected) {
        if (temp == nullptr || temp->data != val) return false;
        temp = temp->next;
    }
    return temp == nullptr; // Ensure list ends at the same time
}

int main() {
    Solution solver;

    cout << "INITIATING SORTED LIST DEDUPLICATION..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: General case with duplicates at start, middle, end
    vector<int> input1 = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    vector<int> expected1 = {1, 2, 3, 4, 5};
    Node* head1 = createList(input1);
    cout << "Input List 1: "; printList(head1);
    
    head1 = solver.removeDuplicates(head1);
    cout << "Result List 1: "; printList(head1);

    if (verifyList(head1, expected1)) {
        cout << "Verification: SUCCESS - Duplicates removed correctly." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: All duplicates
    vector<int> input2 = {2, 2, 2, 2};
    vector<int> expected2 = {2};
    Node* head2 = createList(input2);
    cout << "Input List 2: "; printList(head2);
    
    head2 = solver.removeDuplicates(head2);
    cout << "Result List 2: "; printList(head2);

    if (verifyList(head2, expected2)) {
        cout << "Verification: SUCCESS - Reduced to single node correctly." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup omitted for brevity.

    return 0;
}
/**
 * @file merge_sorted_linked_lists.cpp
 * @author LuShadowX
 * @brief Merge two sorted linked lists into a single sorted linked list.
 * @problem_link: https://www.geeksforgeeks.org/problems/merge-two-sorted-linked-lists/1
 * @difficulty: Easy-Medium (Rank C+)
 * @tags: Linked List, Merge, Two Pointers, Sorting
 * @logic: Utilizes a two-pointer approach similar to the merge step in Merge Sort.
 * 1. Create a dummy node to act as the start of the result list. Maintain a
 * pointer 'final' to the tail of this result list.
 * 2. Use pointers 'temp1' and 'temp2' to traverse the two input lists.
 * 3. Compare data at 'temp1' and 'temp2'. Append the node with the smaller value
 * to the 'final' list and advance its respective pointer.
 * 4. Repeat step 3 until one list is exhausted.
 * 5. Attach the remaining part of the non-empty list to the end of the 'final' list.
 * 6. Return the node following the dummy node as the new head.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Merge Process]
 * The core idea is to build the new sorted list node by node by always choosing
 * the smallest available element from the heads of the two unmerged parts.
 * Since both input lists are already sorted, the smallest overall element must
 * be at the head of one of them.
 *
 * [Time Complexity Analysis]
 * Let N be the length of list1 and M be the length of list2.
 * In the worst case, we iterate through both lists entirely.
 * Total Time: T(N, M) = O(N + M).
 *
 * [Space Complexity Analysis]
 * The algorithm works in-place by rearranging the existing pointers. It uses
 * a constant amount of extra space for the dummy node and a few pointers,
 * regardless of the input list sizes.
 * Total Auxiliary Space: S(N, M) = O(1) (Constant Space).
 * ============================================================================
 */

/**
 * MISSION: Sorted List Merger Protocol
 * RANK: C+ (Fundamental Combinatorial Operation)
 * DEPARTMENT: Linear Data Structures & Sorting Algorithms
 * CHALLENGE:
 * Given two singly linked lists, head1 and head2, which are sorted in non-decreasing
 * order, merge them into a single sorted linked list. The merge should be done
 * in-place by splicing together the nodes of the first two lists. Return the head
 * of the merged list.
 * CONSTRAINTS:
 * - Input lists are sorted.
 * - Time Complexity: O(N + M) required.
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
     * Merges two sorted linked lists.
     * @param head1 The head pointer of the first sorted list.
     * @param head2 The head pointer of the second sorted list.
     * @return The head pointer of the merged sorted list.
     */
    Node* sortedMerge(Node* head1, Node* head2) {
        // Pointers to traverse the input lists.
        Node* temp1 = head1;
        Node* temp2 = head2;

        // Create a dummy node to simplify the merging process.
        // 'final' will always point to the tail of the merged list being built.
        Node* final = new Node(-1);
        // 'store' keeps track of the dummy node so we can access the real head later.
        Node* store = final;

        // Iterate while both lists have nodes to compare.
        while (temp1 && temp2) {
            if (temp1->data <= temp2->data) {
                // Node from list 1 is smaller or equal. Append it.
                final->next = temp1;
                temp1 = temp1->next; // Advance list 1 pointer.
            } else {
                // Node from list 2 is smaller. Append it.
                final->next = temp2;
                temp2 = temp2->next; // Advance list 2 pointer.
            }
            // Move the tail pointer of the merged list forward.
            final = final->next;
        }

        // At this point, one list is exhausted.
        // Attach the remaining part of the other list to the end.
        if (temp1) {
            final->next = temp1;
        }
        if (temp2) {
            final->next = temp2;
        }

        // The actual head of the merged list is the node after the dummy.
        Node* mergedHead = store->next;

        // Note: The memory allocated for the dummy node 'store' is not freed here.
        // In a production environment, 'delete store;' should be called here, but
        // be careful not to delete the mergedHead if the lists were empty.
        // For competitive programming, this small leak is often acceptable.

        return mergedHead;
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
    return temp == nullptr;
}

int main() {
    Solution solver;

    cout << "INITIATING SORTED LIST MERGER PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Two standard sorted lists
    vector<int> data1 = {5, 10, 15, 40};
    vector<int> data2 = {2, 3, 20};
    vector<int> expected1 = {2, 3, 5, 10, 15, 20, 40};

    Node* head1 = createList(data1);
    Node* head2 = createList(data2);

    cout << "List 1: "; printList(head1);
    cout << "List 2: "; printList(head2);

    cout << "Action: Executing sortedMerge()" << endl;
    Node* mergedHead1 = solver.sortedMerge(head1, head2);

    cout << "Merged List: "; printList(mergedHead1);

    if (verifyList(mergedHead1, expected1)) {
        cout << "Verification: SUCCESS - Lists merged and sorted correctly." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: One empty list
    vector<int> data3 = {1, 2, 3};
    vector<int> data4 = {};
    vector<int> expected2 = {1, 2, 3};

    Node* head3 = createList(data3);
    Node* head4 = createList(data4);

    cout << "List 3: "; printList(head3);
    cout << "List 4: "; printList(head4);

    cout << "Action: Executing sortedMerge()" << endl;
    Node* mergedHead2 = solver.sortedMerge(head3, head4);

    cout << "Merged List: "; printList(mergedHead2);

    if (verifyList(mergedHead2, expected2)) {
        cout << "Verification: SUCCESS - Handled empty list correctly." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup omitted for brevity.

    return 0;
}
/**
 * @file remove_duplicates_unsorted_list.cpp
 * @author LuShadowX
 * @brief Remove duplicate nodes from an unsorted Singly Linked List using Hashing.
 * @problem_link: https://www.geeksforgeeks.org/problems/remove-duplicates-from-an-unsorted-linked-list/1
 * @difficulty: Easy (Rank C)
 * @tags: Linked List, Hashing, Unordered Set
 * @logic: Since the list is unsorted, duplicates are not adjacent. We use a Hash Set
 * to keep track of all unique values encountered so far.
 * 1. Initialize an empty `unordered_set`.
 * 2. Use two pointers: `temp` to traverse the list, and `pre` to track the previous node.
 * 3. For each node at `temp`:
 * a. Check if `temp->data` is already in the set.
 * b. If found (duplicate): Skip the current node by linking `pre->next` to `temp->next`.
 * c. If not found (unique): Insert the data into the set and move `pre` forward to `temp`.
 * 4. Always move `temp` to the next node in every iteration.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Hashing Approach]
 * Hashing allows for near-instantaneous checks for existence. By storing every
 * unique element seen in an `unordered_set`, we can determine if the current
 * node's value is a duplicate in average O(1) time.
 *
 * [Space-Time Trade-off]
 * Compared to the sorted list version which used O(1) space, here we trade space
 * for time.
 *
 * [Time Complexity Analysis]
 * We traverse the list once. For each node, set insertion and lookup operations
 * take average O(1) time.
 * Total Time: T(N) = O(N) (Average case).
 *
 * [Space Complexity Analysis]
 * In the worst case, all elements in the list are unique, and we store all N
 * values in the hash set.
 * Total Auxiliary Space: S(N) = O(N).
 * ============================================================================
 */

/**
 * MISSION: Unsorted List Deduplication Protocol
 * RANK: C (Foundational Optimization with Hashing)
 * DEPARTMENT: Linear Data Structures & Data Cleaning
 * CHALLENGE:
 * Given the head pointer of an unsorted singly linked list, remove all duplicate
 * values from the list. Return the head of the modified list.
 * CONSTRAINTS:
 * - The input list is NOT sorted.
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(N) allowed.
 */

#include <iostream>
#include <vector>
#include <unordered_set>

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
     * Removes duplicates from an unsorted linked list.
     * @param head The head pointer of the unsorted list.
     * @return The head pointer of the list with duplicates removed.
     */
    Node* removeDuplicates(Node* head) {
        // Hash set to store seen values for O(1) average lookup.
        unordered_set<int> mp;
        
        Node* pre = NULL;   // Pointer to the previous node
        Node* temp = head;  // Pointer to the current node

        // Iterate through the entire list.
        while(temp){
            // Check if current data is already in the set.
            if(mp.find(temp->data) != mp.end()){
                // Duplicate found. Skip the current node.
                // 'pre' is guaranteed to be non-NULL here as the first node is always unique.
                pre->next = temp->next;
                // Note: In production, memory for 'temp' should be freed here: delete temp;
            }
            else{
                // Unique value found. Mark as seen.
                mp.insert(temp->data);
                // Advance 'pre' pointer to the current unique node.
                pre = temp;
            }
            // Always advance 'temp' to continue traversal.
            temp = temp->next;
        }
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
    return temp == nullptr;
}

int main() {
    Solution solver;

    cout << "INITIATING UNSORTED LIST DEDUPLICATION..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: General unsorted list with duplicates
    vector<int> input1 = {5, 2, 2, 4, 5, 1, 4};
    vector<int> expected1 = {5, 2, 4, 1}; // Order of first appearance is preserved
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

    // TEST CASE 2: List with all unique elements
    vector<int> input2 = {10, 20, 30, 40};
    vector<int> expected2 = {10, 20, 30, 40};
    Node* head2 = createList(input2);
    cout << "Input List 2: "; printList(head2);
    
    head2 = solver.removeDuplicates(head2);
    cout << "Result List 2: "; printList(head2);

    if (verifyList(head2, expected2)) {
        cout << "Verification: SUCCESS - Unique list remains unchanged." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup omitted for brevity.

    return 0;
}
/**
 * @file search_in_linked_list.cpp
 * @author LuShadowX
 * @brief Search for a specific key value within a Singly Linked List.
 * @problem_link: https://www.geeksforgeeks.org/problems/search-in-linked-list-1664434326/1
 * @difficulty: Easy (Rank C)
 * @tags: Linked List, Search, Linear Search, Iteration
 * @logic: Performs a standard iterative Linear Search.
 * 1. Start a temporary pointer 'temp' at the head of the list.
 * 2. Iterate through the list using a loop that continues as long as 'temp' is not NULL.
 * 3. In each iteration, compare the current node's data ('temp->data') with the target 'key'.
 * 4. If they match, return true immediately.
 * 5. If not, advance the pointer to the next node ('temp = temp->next').
 * 6. If the loop completes without finding a match, it means the key is not present; return false.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [Linear Search Principle on Sequential Structures]
 * A linked list is a sequential data structure. Unlike an array, it does not
 * support random access (indexing in O(1) time). To find an element, we must
 * visit nodes sequentially starting from the head.
 *
 * Algorithm:
 * Let the list be L = N₀ → N₁ → ... → Nₖ → ... → NULL
 * To find key 'K':
 * - Check N₀.data. If N₀.data == K, stop, return Found.
 * - Move to N₁. Check N₁.data...
 * - Repeat until Nₖ.data == K OR we reach NULL.
 *
 * [Time Complexity Analysis]
 * - Best Case: Key is at the head. O(1).
 * - Worst Case: Key is at the tail or not present. We must visit all N nodes.
 * Total Time: T(N) = O(N), where N is the number of nodes in the list.
 *
 * [Space Complexity Analysis]
 * The algorithm only requires a single temporary pointer variable ('temp') to
 * keep track of the current position during traversal. No additional data
 * structures proportional to the input size are created.
 * Total Auxiliary Space: S(N) = O(1) (Constant Space).
 * ============================================================================
 */

/**
 * MISSION: Linked List Target Acquisition Protocol
 * RANK: C (Foundational List Operation)
 * DEPARTMENT: Linear Data Structures & Search Algorithms
 * CHALLENGE:
 * Given the head pointer of a singly linked list and an integer value 'key',
 * determine if a node containing the value 'key' exists within the list.
 * Return true if found, false otherwise.
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
    // Constructor
    Node(int x) : data(x), next(NULL) {}
};

class Solution {
public:
    /**
     * Searches for a key in the linked list.
     * @param head The head pointer of the linked list.
     * @param key The value to search for.
     * @return true if the key is present, false otherwise.
     */
    bool searchKey(Node* head, int key) {
        // Initialize a temporary pointer to traverse the list, starting at the head.
        Node* temp = head;
        
        // Iterate as long as the current node pointer is valid (not NULL).
        while (temp != NULL) {
            // CRITICAL CHECK: Compare current node's data with the target key.
            if (temp->data == key) {
                return true; // Target acquired.
            }
            // Move the pointer to the next node in the sequence.
            temp = temp->next;
        }
        
        // If the loop terminates, the end of the list was reached without finding the key.
        return false; // Target not found.
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to create a linked list from a vector (for testing setup)
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

// Helper string function for clear output
string boolToString(bool b) { return b ? "FOUND (True)" : "NOT FOUND (False)"; }

int main() {
    Solution solver;

    cout << "INITIATING LINKED LIST TARGET ACQUISITION..." << endl;
    cout << "-----------------------------" << endl;

    // Setup: Create a test list: 10 -> 20 -> 30 -> 40 -> 50
    vector<int> data = {10, 20, 30, 40, 50};
    Node* head = createList(data);
    cout << "List Structure: [ 10 -> 20 -> 30 -> 40 -> 50 ]" << endl;
    cout << "-----------------------------" << endl;

    // Test Case 1: Searching for an existing key
    int target1 = 30;
    cout << "Scanning for Target: " << target1 << endl;
    bool result1 = solver.searchKey(head, target1);
    cout << "Result: " << boolToString(result1) << endl;
    cout << "-----------------------------" << endl;

    // Test Case 2: Searching for a non-existent key
    int target2 = 99;
    cout << "Scanning for Target: " << target2 << endl;
    bool result2 = solver.searchKey(head, target2);
    cout << "Result: " << boolToString(result2) << endl;
    cout << "-----------------------------" << endl;

    cout << "MISSION COMPLETE." << endl;

    // Memory Cleanup omitted for brevity in competitive context.

    return 0;
}
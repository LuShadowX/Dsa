/**
 * @file array_to_linked_list.cpp
 * @author LuShadowX
 * @brief Convert a static array (vector) into a dynamic Singly Linked List.
 * @problem_link: https://www.geeksforgeeks.org/problems/introduction-to-linked-list/1
 * @difficulty: Easy (Rank C)
 * @tags: Linked List, Array, Data Structure Conversion
 * @logic: Utilizes a "Dummy Node" strategy to simplify list construction.
 * 1. Create a temporary dummy node. A pointer 'temp' tracks the tail of the newly building list, starting at the dummy.
 * 2. Iterate through the input array. For each element, create a new Node.
 * 3. Link the current tail ('temp->next') to this new node.
 * 4. Move the 'temp' pointer to the new node.
 * 5. After the loop, the actual head of the list is the node immediately following the dummy.
 * 6. Delete the dummy node to free memory before returning the actual head.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [Data Structure Transformation]
 * The operation transforms contiguous memory storage into non-contiguous,
 * pointer-linked storage.
 *
 * Input: Array A = [a₀, a₁, ..., aₙ₋₁]
 * (Elements stored in contiguous memory locations M, M+k, M+2k...)
 *
 * Output: Linked List L = N₀ → N₁ → ... → Nₙ₋₁ → NULL
 * Where Node Nᵢ contains data aᵢ and a pointer to Nᵢ₊₁.
 * (Nodes stored in arbitrary heap memory locations).
 *
 * [Time Complexity Analysis]
 * We iterate through the array exactly once, performing constant time O(1)
 * operations (node creation and linking) for each element.
 * Total Time: T(N) = O(N), where N is the size of the array.
 *
 * [Space Complexity Analysis]
 * We create N new nodes dynamically on the heap to store the data.
 * Total Space: S(N) = O(N).
 * ============================================================================
 */

/**
 * MISSION: Linear Structure Conversion Protocol
 * RANK: C (Foundational Data Structure Operation)
 * DEPARTMENT: memory Management & Linked Structures
 * CHALLENGE:
 * Given a vector of integers 'arr', construct a singly linked list where each
 * node corresponds to an element in the vector, preserving the original order.
 * Return the head pointer of the newly constructed list.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(N) required for the new list nodes.
 */

#include <iostream>
#include <vector>

using namespace std;

// Standard definition for a Singly Linked List Node.
class Node {
public:
    int data;
    Node* next;

    // Constructor
    Node(int d) {
        data = d;
        next = NULL;
    }
};

class Solution {
public:
    /**
     * Converts an array defined by a vector into a singly linked list.
     * @param arr The input vector of integers.
     * @return A pointer to the head of the newly created linked list.
     */
    Node* arrayToList(vector<int>& arr) {
        // 1. Create a dummy node as a temporary placeholder base.
        // Using -1 or any value is fine, it won't be part of the final list.
        Node* dummy = new Node(-1);
        
        // 'temp' will always point to the last node in the list being built.
        Node* temp = dummy;

        // 2. Iterate through array and build the list
        for (int i = 0; i < arr.size(); i++) {
            // Create new node with array data and link it to the current tail.
            temp->next = new Node(arr[i]);
            // Move tail pointer forward.
            temp = temp->next;
        }

        // 3. Identify the real head (the node after the dummy).
        Node* actualHead = dummy->next;

        // CRITICAL MEMORY MANAGEMENT: Delete the temporary dummy node.
        delete dummy;

        // 4. Return the head of the constructed list.
        return actualHead;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to print Linked List for verification
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

    cout << "INITIATING DATA STRUCTURE TRANSFORMATION..." << endl;
    cout << "-----------------------------" << endl;

    // Test Case: Standard array
    vector<int> inputData = {10, 20, 30, 40, 50};
    cout << "Input Array: [ 10, 20, 30, 40, 50 ]" << endl;

    // Execute the conversion
    Node* listHead = solver.arrayToList(inputData);

    // Report findings
    cout << "Converted Linked List: ";
    printList(listHead);

    // Verification checks
    if (listHead != nullptr && listHead->data == 10 && listHead->next->next->next->next->data == 50) {
        cout << "STATUS: SUCCESS - Structure and ordering verified." << endl;
    } else {
        cout << "STATUS: FAILURE - Conversion error detected." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory Cleanup omitted for brevity in competitive context, but essential in production.
    // (Would require iterating through the new list and deleting every node).

    return 0;
}
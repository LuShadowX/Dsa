/**
 * @file detect_loop_linked_list.cpp
 * @author LuShadowX
 * @brief Detect if a Singly Linked List contains a cycle (loop).
 * @problem_link: https://www.geeksforgeeks.org/problems/detect-loop-in-linked-list/1
 * @difficulty: Easy-Medium (Rank C+)
 * @tags: Linked List, Two Pointers, Cycle Detection, Floyd's Algorithm
 * @logic: Utilizes Floyd's Cycle-Finding Algorithm (Tortoise and Hare).
 * 1. Initialize two pointers, 'slow' and 'fast', both at the head.
 * 2. In each step, move 'slow' forward by one node and 'fast' forward by two nodes.
 * 3. If a loop exists, the 'fast' pointer will eventually enter the loop and
 * catch up to the 'slow' pointer from behind.
 * 4. If the pointers meet (point to the same node), a loop is detected.
 * 5. If the 'fast' pointer reaches the end (NULL), no loop exists.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Relative Speed Principle]
 * Consider two runners on a track. If the track is straight (no loop), the
 * faster runner will reach the end first and never meet the slower runner again.
 * If the track has a circular section, the faster runner will eventually enter
 * the circle, lap the slower runner, and meet them at some point inside the circle.
 *
 * In this algorithm:
 * - The 'slow' pointer moves 1 step/iteration.
 * - The 'fast' pointer moves 2 steps/iteration.
 * - The relative speed is 1 step/iteration.
 *
 * Once both pointers are inside the loop, the distance between them decreases
 * by 1 in each iteration. Therefore, it is mathematically guaranteed that they
 * will meet.
 *
 * [Time Complexity Analysis]
 * - No Loop: The 'fast' pointer reaches the end in O(N/2) steps.
 * - Loop Exists: The 'slow' pointer enters the loop in at most N steps. Once
 * both are in the loop, 'fast' catches 'slow' in at most K steps (where K is
 * the loop length).
 * Total Time: T(N) = O(N), where N is the total number of nodes.
 *
 * [Space Complexity Analysis]
 * The algorithm uses only two fixed pointer variables, regardless of input size.
 * Total Auxiliary Space: S(N) = O(1) (Constant Space).
 * ============================================================================
 */

/**
 * MISSION: Linked List Cycle Detection Protocol
 * RANK: C+ (Standard Efficient Algorithm)
 * DEPARTMENT: Linear Data Structures & Algorithmic Optimization
 * CHALLENGE:
 * Given the head pointer of a singly linked list, determine if the linked list
 * contains a cycle. A cycle occurs if a node's 'next' pointer points back to a
 * previous node in the list, creating a closed loop. Return true if a cycle
 * exists, false otherwise.
 * CONSTRAINTS:
 * - Time Complexity: O(N) required.
 * - Space Complexity: O(1) required.
 */

#include <iostream>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct Node {
    int data;
    Node *next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    /**
     * Detects a loop in the linked list using the two-pointer approach.
     * @param head The head pointer of the linked list.
     * @return true if a loop is present, false otherwise.
     */
    bool detectLoop(Node* head) {
        // BASE CASE: An empty list or a list with one node cannot have a loop.
        // A loop requires at least two nodes where one points back to the other.
        if (head == NULL || head->next == NULL) {
            return false;
        }

        // Initialize Tortoise (slow) and Hare (fast) pointers at the start.
        Node* slow = head;
        Node* fast = head;

        // Start the race.
        // CRITICAL CONDITION: We must ensure 'fast' can safely make a two-step jump.
        // We check if 'fast' has reached NULL or if the *next* node is NULL.
        while (fast != NULL && fast->next != NULL) {
            // Move slow pointer one step.
            slow = slow->next;
            // Move fast pointer two steps.
            fast = fast->next->next;

            // COLLISION CHECK: If pointers meet, the fast one caught the slow one.
            // This proves the existence of a cycle.
            if (fast == slow) {
                return true; // Loop detected.
            }
        }

        // If the loop terminates, the 'fast' pointer reached the end of the list.
        // Therefore, no cycle exists.
        return false;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper to create a list with a loop for testing.
// 10 -> 20 -> 30 -> 40 -> 20 (points back to node 2)
Node* createLoopedList() {
    Node* head = new Node(10);
    Node* node2 = new Node(20);
    Node* node3 = new Node(30);
    Node* node4 = new Node(40);

    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    // Create the loop: 40 points back to 20
    node4->next = node2;

    return head;
}

// Helper to create a standard linear list.
Node* createLinearList() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    return head;
}

int main() {
    Solution solver;

    cout << "INITIATING LINKED LIST CYCLE DETECTION..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: List with a loop
    cout << "Test Case 1: Analyzing list WITH a loop (10->20->30->40->20...)" << endl;
    Node* loopedHead = createLoopedList();
    bool hasLoop1 = solver.detectLoop(loopedHead);
    
    if (hasLoop1) {
        cout << "Result: CYCLE DETECTED. Verification: SUCCESS." << endl;
    } else {
        cout << "Result: NO CYCLE. Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;


    // TEST CASE 2: Linear list without a loop
    cout << "Test Case 2: Analyzing linear list WITHOUT a loop (1->2->3->NULL)" << endl;
    Node* linearHead = createLinearList();
    bool hasLoop2 = solver.detectLoop(linearHead);

    if (!hasLoop2) {
        cout << "Result: NO CYCLE. Verification: SUCCESS." << endl;
    } else {
        cout << "Result: CYCLE DETECTED. Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory Cleanup note: Cleaning up a looped list requires care to avoid infinite loops.
    // Omitted here for brevity in competitive context.

    return 0;
}
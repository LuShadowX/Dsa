/**
 * @file find_cycle_start_linked_list.cpp
 * @author LuShadowX
 * @brief Detect a cycle in a linked list and find the starting node of the cycle.
 * @problem_link: https://www.geeksforgeeks.org/problems/find-the-first-node-of-loop-in-linked-list--155602/1
 * @difficulty: Medium (Rank B)
 * @tags: Linked List, Two Pointers, Floyd's Cycle Detection, Math
 * @logic: Utilizes the extended Floyd's Cycle-Finding Algorithm.
 * Phase 1: Use slow (1x speed) and fast (2x speed) pointers to detect if a loop
 * exists. If they meet, a loop is present.
 * Phase 2: Reset the fast pointer to the head of the list. Keep the slow pointer
 * at the meeting point. Move both pointers one step at a time. The point where
 * they meet next is the start of the cycle.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION (The Proof of Phase 2)
 * ============================================================================
 * Why does resetting one pointer to the head and moving both at speed 1 work?
 *
 * Let:
 * L = Distance from Head to the Cycle Start node.
 * C = Length of the cycle (number of nodes in the loop).
 * d = Distance from Cycle Start to the 'Meeting Point' (where fast met slow initially).
 *
 * [At the Initial Meeting Point]
 * Distance traveled by Slow pointer ($D_{slow}$) = $L + d$
 * Distance traveled by Fast pointer ($D_{fast}$) = $L + d + nC$
 * (where $n$ is the integer number of full laps the fast pointer made inside the cycle).
 *
 * Since Fast moves twice as fast as Slow:
 * $D_{fast} = 2 \times D_{slow}$
 * $L + d + nC = 2(L + d)$
 * $L + d + nC = 2L + 2d$
 * $nC = L + d$
 *
 * [The Key Deduction]
 * Rearranging for L:
 * $L = nC - d$
 *
 * This equation means: The distance from the Head to the Cycle Start ($L$) is
 * exactly equal to the remaining distance the Slow pointer needs to travel
 * along the loop to complete $n$ full circles and return to the Cycle Start.
 *
 * [Conclusion]
 * If we place a pointer at Head (distance 0 from start) and another at the
 * Meeting Point (distance $d$ into the loop), and move both 1 step at a time:
 * After traveling distance $L$, the Head pointer will be at the Cycle Start.
 * The Meeting Point pointer will have covered a total loop distance of $d + L = d + (nC - d) = nC$.
 * Since $nC$ is a multiple of the cycle length, it is also back at the Cycle Start.
 * Therefore, they meet exactly at the start of the cycle.
 * ============================================================================
 */

/**
 * MISSION: Linked List Cycle Entry Detection Protocol
 * RANK: B (Mathematical Pointer Manipulation)
 * DEPARTMENT: Linear Data Structures & Algorithmic Optimization
 * CHALLENGE:
 * Given the head pointer of a singly linked list, determine if a cycle exists.
 * If it does, return the data value of the node where the cycle begins.
 * If no cycle exists, return -1.
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
     * Finds the data value of the starting node of a cycle in a linked list.
     * @param head The head pointer of the linked list.
     * @return The data of the cycle start node, or -1 if no cycle exists.
     */
    int cycleStart(Node* head) {
        Node* fast = head;
        Node* slow = head;

        // ==========================================
        // Phase 1: Detection (Tortoise and Hare)
        // ==========================================
        
        // Base Case: Empty or single-node list cannot have a loop.
        if (fast == NULL || fast->next == NULL) return -1;
        
        bool hasLoop = false;
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next; // Move 2 steps
            slow = slow->next;       // Move 1 step
            
            // Collision detected
            if (slow == fast) {
                hasLoop = true;
                break; // Exit Phase 1, 'slow' and 'fast' are at the Meeting Point.
            }
        }

        // If loop finished without collision, no cycle exists.
        if (!hasLoop) return -1;

        // ==========================================
        // Phase 2: Finding the Start Node (The Mathematical Step)
        // ==========================================
        
        // Reset one pointer to the head. Keep the other at the meeting point.
        fast = head; 
        
        // Move both pointers one step at a time until they collide again.
        // Based on the math derived above, this collision point is the cycle start.
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        // When the loop breaks, slow == fast at the start of the loop.
        return slow->data;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper to create a list with a specific cycle start for testing.
// Structure: 1 -> 2 -> [3 -> 4 -> 5 -> (back to 3)]
// Cycle start data should be 3.
Node* createTestedLoopedList() {
    Node* head = new Node(1);
    Node* node2 = new Node(2);
    Node* startNode = new Node(3); // Cycle starts here
    Node* node4 = new Node(4);
    Node* endNode = new Node(5);

    head->next = node2;
    node2->next = startNode;
    startNode->next = node4;
    node4->next = endNode;
    // Create the loop: 5 points back to 3
    endNode->next = startNode;

    return head;
}

int main() {
    Solution solver;

    cout << "INITIATING CYCLE ENTRY DETECTION PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: List with a loop
    // 1 -> 2 -> [3 -> 4 -> 5 -> 3...]
    cout << "Test Case 1: Analyzing looped list. Expected Cycle Start Data: 3" << endl;
    Node* loopedHead = createTestedLoopedList();
    int startData = solver.cycleStart(loopedHead);
    
    cout << "Result Data: " << startData << endl;
    if (startData == 3) {
        cout << "Verification: SUCCESS - Correct cycle start identified." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: Linear list without a loop
    cout << "Test Case 2: Analyzing linear list (1->2->3->NULL). Expected: -1" << endl;
    Node* linearHead = new Node(1);
    linearHead->next = new Node(2);
    linearHead->next->next = new Node(3);
    
    int linearResult = solver.cycleStart(linearHead);
    cout << "Result Data: " << linearResult << endl;

    if (linearResult == -1) {
        cout << "Verification: SUCCESS - Correctly identified no loop." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    return 0;
}
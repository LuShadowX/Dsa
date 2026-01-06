/**
 * @file intersection_point_linked_list.cpp
 * @author LuShadowX
 * @brief Find the node where two singly linked lists intersect.
 * @problem_link: https://www.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1
 * @difficulty: Medium (Rank B)
 * @tags: Linked List, Two Pointers, Math
 * @logic: Utilizes a clever two-pointer strategy to handle the difference in list lengths.
 * 1. Initialize two pointers, `temp1` at `head1` and `temp2` at `head2`.
 * 2. Traverse through both lists simultaneously.
 * 3. When `temp1` reaches the end of its list (NULL), redirect it to the head of the *other* list (`head2`).
 * 4. Similarly, when `temp2` reaches the end of its list, redirect it to `head1`.
 * 5. This switching technique ensures that if an intersection exists, both pointers will eventually reach it at the exact same iteration.
 * 6. The loop terminates when `temp1 == temp2`. This meeting point is either the intersection node or NULL (if no intersection).
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [The Distance Equalization Principle]
 * Let:
 * - A be the non-common part of list 1.
 * - B be the non-common part of list 2.
 * - C be the common intersecting part.
 *
 * Length of List 1 = A + C
 * Length of List 2 = B + C
 *
 * Path of Pointer 1: Traverses A + C, then switches and traverses B.
 * Total distance to intersection = (A + C) + B.
 *
 * Path of Pointer 2: Traverses B + C, then switches and traverses A.
 * Total distance to intersection = (B + C) + A.
 *
 * Since A + C + B = B + C + A, both pointers travel the exact same distance
 * and are guaranteed to meet at the start of C (the intersection node).
 *
 * [Time Complexity Analysis]
 * In the worst case (no intersection or intersection at the very end), each
 * pointer traverses both lists exactly once.
 * Let N be length of list 1, M be length of list 2.
 * Total Time: T(N, M) = O(N + M).
 *
 * [Space Complexity Analysis]
 * The algorithm uses only two fixed pointer variables regardless of input size.
 * Total Auxiliary Space: S(N, M) = O(1) (Constant Space).
 Note:
 The Master's Review: The "Magic" of the Switch

Why this works:

    Pointer A travels distance L1 and then starts traveling L2.

    Pointer B travels distance L2 and then starts traveling L1.

    By the time they are in their second "lap," both have traveled exactly L1+L2.

    Because they have covered the same total distance, they are guaranteed to collide at the intersection point!

Complexity:

    Time: O(N+M) — You traverse each list at most twice.

    Space: O(1) — No extra variables for length.
 * ============================================================================
 */

/**
 * MISSION: Linked List Intersection Detection Protocol
 * RANK: B (Elegant Pointer Manipulation)
 * DEPARTMENT: Linear Data Structures & Pattern Matching
 * CHALLENGE:
 * Given the heads of two singly linked lists, `head1` and `head2`, return the
 * node at which the two lists intersect. If the two linked lists have no
 * intersection at all, return NULL. The intersection is defined by reference
 * (the same node in memory), not by value.
 * CONSTRAINTS:
 * - Time Complexity: O(N + M) required.
 * - Space Complexity: O(1) required.
 * - The linked list structure must not be modified.
 */

#include <iostream>

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
     * Finds the intersection node of two linked lists.
     * @param head1 The head of the first list.
     * @param head2 The head of the second list.
     * @return The intersection node pointer, or NULL if none exists.
     */
    Node* intersectPoint(Node* head1, Node* head2) {
        // Base case: If either list is empty, there can be no intersection.
        if (head1 == NULL || head2 == NULL) {
            return NULL;
        }

        // Initialize pointers to the heads of each list.
        Node* temp1 = head1;
        Node* temp2 = head2;

        // Iterate until the pointers meet. They will meet at the intersection
        // node, or at NULL if there is no intersection.
        while (temp1 != temp2) {
            // Move temp1 forward. If it reaches the end, switch to the other list's head.
            if (temp1 == NULL) {
                temp1 = head2;
            } else {
                temp1 = temp1->next;
            }

            // Move temp2 forward. If it reaches the end, switch to the other list's head.
            if (temp2 == NULL) {
                temp2 = head1;
            } else {
                temp2 = temp2->next;
            }
        }

        // Return the meeting point (the intersection node or NULL).
        return temp1;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

// Helper function to print a list from a given node
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

    cout << "INITIATING INTERSECTION DETECTION PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // TEST CASE 1: Intersecting Lists
    // List 1: 1 -> 2 -> 3 \
    //                      -> 8 -> 9 -> 10
    // List 2:      4 -> 5 /
    // Intersection node has data '8'.

    // Create the common part
    Node* common = new Node(8);
    common->next = new Node(9);
    common->next->next = new Node(10);

    // Create List 1 head part
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    // Attach to common part
    head1->next->next->next = common;

    // Create List 2 head part
    Node* head2 = new Node(4);
    head2->next = new Node(5);
    // Attach to common part
    head2->next->next = common;

    cout << "Test Case 1 (Intersection at node with value 8):" << endl;
    cout << "List 1 structure created." << endl;
    cout << "List 2 structure created." << endl;

    Node* intersection = solver.intersectPoint(head1, head2);

    if (intersection != NULL && intersection == common) {
        cout << "Verification: SUCCESS - Intersection found at node with value: " << intersection->data << endl;
    } else {
        cout << "Verification: FAILURE - Incorrect or no intersection found." << endl;
    }
    cout << "-----------------------------" << endl;

    // TEST CASE 2: No Intersection
    // List 3: 1 -> 2
    // List 4: 3 -> 4
    Node* head3 = new Node(1);
    head3->next = new Node(2);
    Node* head4 = new Node(3);
    head4->next = new Node(4);

    cout << "Test Case 2 (No Intersection):" << endl;
    Node* noIntersection = solver.intersectPoint(head3, head4);

    if (noIntersection == NULL) {
        cout << "Verification: SUCCESS - Correctly identified no intersection." << endl;
    } else {
        cout << "Verification: FAILURE - False intersection detected." << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Memory cleanup is complex due to shared nodes and omitted for brevity.
    // In production, ensure 'common' is deleted only once.

    return 0;
}
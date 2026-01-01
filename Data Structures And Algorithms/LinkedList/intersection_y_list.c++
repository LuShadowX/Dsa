/**
 * @file intersection_y_list.cpp
 * @author LuShadowX
 * @brief Find the intersection point of two Y-shaped Linked Lists.
 * * @problem_link: https://www.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1
 * @difficulty: Medium (Rank A)
 * @tags: Linked List, Two Pointers, Memory Synchronization
 * * @logic: Synchronizing the travel distance of two pointers by switching heads.
 * Distance(A->B) == Distance(B->A).
 */
/**
 * MISSION: Intersection Point in Y-Shaped Linked Lists
 * RANK: A (High-Tier Medium)
 * DEPARTMENT: Linked Structures & Memory Synchronization
 * * CHALLENGE: 
 * Two distinct data streams (Linked Lists) converge into a single shared path.
 * Your objective is to identify the exact memory address (Node) where the 
 * synchronization begins.
 * * CONSTRAINTS: 
 * - Time Complexity: O(N + M)
 * - Space Complexity: O(1)
 * - No Division or extra data structures allowed.
 */

#include <bits/stdc++.h>

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
     * THE TWO-POINTER TIME WARP TECHNIQUE
     * We synchronize the paths by switching tracks. 
     * Distance(A + B) = Distance(B + A).
     */
    Node* intersectPoint(Node* head1, Node* head2) {
        if (!head1 || !head2) return NULL;

        Node* temp1 = head1;
        Node* temp2 = head2;

        while (temp1 != temp2) {
            // If temp1 hits the end, jump to head of list 2
            // Otherwise, step forward
            temp1 = (temp1 == NULL) ? head2 : temp1->next;

            // If temp2 hits the end, jump to head of list 1
            // Otherwise, step forward
            temp2 = (temp2 == NULL) ? head1 : temp2->next;
        }

        // They meet at the intersection point or NULL if no intersection
        return temp1;
    }
};

int main() {
    Solution solver;

    // Create Common Part: 15 -> 30
    Node* common = new Node(15);
    common->next = new Node(30);

    // Create List 1: 10 -> [Common]
    Node* head1 = new Node(10);
    head1->next = common;

    // Create List 2: 3 -> 6 -> 9 -> [Common]
    Node* head2 = new Node(3);
    head2->next = new Node(6);
    head2->next->next = new Node(9);
    head2->next->next->next = common;

    Node* result = solver.intersectPoint(head1, head2);

    if (result) {
        std::cout << "INTERSECTION DETECTED AT NODE DATA: " << result->data << std::endl;
    } else {
        std::cout << "NO INTERSECTION FOUND." << std::endl;
    }

    return 0;
}

/**
 * @file queue_using_linked_list.cpp
 * @author LuShadowX
 * @brief Implement a Queue data structure using a Singly Linked List.
 * @problem_link: https://www.geeksforgeeks.org/problems/implement-queue-using-linked-list/1
 * @difficulty: Easy (Rank C)
 * @tags: Queue, Linked List, Design, Dynamic Memory Management
 * @logic: A queue follows the FIFO (First-In, First-Out) principle.
 * To implement this efficiently with a linked list:
 * 1. **Enqueuing (insertion)** happens at one end, called the **rear** (tail).
 * 2. **Dequeuing (removal)** happens at the other end, called the **front** (head).
 *
 * We maintain two pointers:
 * - `front`: Points to the first node (the next one to be dequeued).
 * - `rear`: Points to the last node (the most recently enqueued).
 *
 * Operations:
 * - **enqueue(x):** Create a new node. If the queue is empty, both `front` and `rear`
 * point to it. Otherwise, link the current `rear->next` to the new node and
 * update `rear` to point to the new node. Time: O(1).
 * - **dequeue():** Check if empty. Store the current `front` node temporarily.
 * Move `front` to `front->next`. If `front` becomes NULL, update `rear` to NULL
 * as well. **Crucially, delete the temporary node to prevent memory leaks.** Time: O(1).
 * - **getFront():** Return `front->data`. Time: O(1).
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [Why Rear and Front Pointers?]
 * A singly linked list allows O(1) insertion at the head and O(1) deletion at the head.
 * Insertion at the tail is O(1) *only if* we maintain a tail pointer. Deletion
 * from the tail is always O(N) because we cannot easily update the second-to-last
 * node's pointer.
 *
 * For FIFO behavior:
 * - Insert at Rear (Tail): O(1) with a `rear` pointer.
 * - Remove from Front (Head): O(1) with a `front` pointer.
 * This configuration ensures all queue operations are optimal.
 *
 * [Time Complexity Analysis]
 * - enqueue(): O(1)
 * - dequeue(): O(1)
 * - getFront(): O(1)
 * - size(): O(1)
 * - isEmpty(): O(1)
 *
 * [Space Complexity Analysis]
 * The queue uses O(N) space for N nodes. Each operation uses O(1) auxiliary space.
 * ============================================================================
 */

/**
 * MISSION: Linked List Queue Implementation Protocol
 * RANK: C (Foundational Data Structure Design)
 * DEPARTMENT: Linear Data Structures & Memory Management
 * CHALLENGE:
 * Implement a Queue class using a linked list. The class should support the
 * following operations in O(1) time:
 * - enqueue(int x): Add an element to the rear of the queue.
 * - dequeue(): Remove the element from the front of the queue.
 * - getFront(): Return the front element without removing it.
 * - isEmpty(): Check if the queue is empty.
 * - size(): Return the number of elements in the queue.
 */

#include <iostream>

using namespace std;

// Standard definition for a Singly Linked List Node.
struct Node {
    int data;
    Node* next;
    Node(int new_data) {
        data = new_data;
        next = nullptr;
    }
};

class myQueue {
private:
    Node* front; // Points to the node at the front of the queue (to be removed next)
    Node* rear;  // Points to the node at the rear of the queue (most recently added)
    int count;   // Tracks the number of elements

public:
    // Constructor: Initialize an empty queue.
    myQueue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    // Destructor: CRITICAL for cleaning up dynamic memory when the queue is destroyed.
    ~myQueue() {
        Node* temp = front;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        // cout << "Destructor called: Queue memory freed." << endl; // For debug
    }

    /**
     * Checks if the queue is empty.
     * @return true if empty, false otherwise.
     */
    bool isEmpty() {
        return front == nullptr; // Or count == 0
    }

    /**
     * Adds an element to the rear of the queue.
     * @param x The value to enqueue.
     */
    void enqueue(int x) {
        Node* newnode = new Node(x);
        
        // Case 1: Queue is empty.
        if (rear == nullptr) {
            front = rear = newnode;
        } 
        // Case 2: Queue is not empty.
        else {
            rear->next = newnode; // Link the current rear to the new node
            rear = newnode;       // Update rear to point to the new end
        }
        count++;
    }

    /**
     * Removes the element from the front of the queue.
     * Does nothing if the queue is empty.
     */
    void dequeue() {
        // Underflow check
        if (isEmpty()) {
            return;
        }

        // Hold the node to be deleted.
        Node* temp = front;
        
        // Move front pointer to the next node.
        front = front->next;

        // CRITICAL: If the queue becomes empty, rear must also be NULL.
        // Otherwise, rear will point to freed memory (a dangling pointer).
        if (front == nullptr) {
            rear = nullptr;
        }

        // CRITICAL: Free the memory of the dequeued node.
        delete temp;
        count--;
    }

    /**
     * Returns the front element of the queue without removing it.
     * @return The front element, or -1 if the queue is empty.
     */
    int getFront() {
        if (isEmpty()) {
            return -1; // Indicate empty queue
        }
        return front->data;
    }

    /**
     * Returns the number of elements in the queue.
     * @return The size of the queue.
     */
    int size() {
        return count;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    cout << "INITIATING LINKED LIST QUEUE PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    myQueue q;

    // Test 1: Enqueue operations
    cout << "Action: Enqueue 10, 20, 30" << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout << "Queue Size: " << q.size() << " (Expected: 3)" << endl;
    cout << "Front Element: " << q.getFront() << " (Expected: 10)" << endl;
    cout << "-----------------------------" << endl;

    // Test 2: Dequeue operations
    cout << "Action: Dequeue once" << endl;
    q.dequeue();
    cout << "Front Element after dequeue: " << q.getFront() << " (Expected: 20)" << endl;

    cout << "Action: Dequeue remaining elements" << endl;
    q.dequeue(); // Removes 20
    q.dequeue(); // Removes 30
    cout << "Queue Size after emptying: " << q.size() << " (Expected: 0)" << endl;
    cout << "Is Empty: " << (q.isEmpty() ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "-----------------------------" << endl;

    // Test 3: Edge Cases (Underflow and re-enqueue)
    cout << "Action: Dequeue from empty queue (Underflow test)" << endl;
    q.dequeue(); // Should do nothing safely.
    cout << "Get front from empty: " << q.getFront() << " (Expected: -1)" << endl;

    cout << "Action: Enqueue 100 after emptying" << endl;
    q.enqueue(100);
    cout << "Front Element: " << q.getFront() << " (Expected: 100)" << endl;

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;
    // The destructor ~myQueue() will be called automatically here.

    return 0;
}
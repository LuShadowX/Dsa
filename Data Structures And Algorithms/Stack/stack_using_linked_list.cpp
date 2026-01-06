/**
 * @file stack_using_linked_list.cpp
 * @author LuShadowX
 * @brief Implement a Stack data structure using a Singly Linked List.
 * @problem_link: https://www.geeksforgeeks.org/problems/implement-stack-using-linked-list/1
 * @difficulty: Easy (Rank C)
 * @tags: Stack, Linked List, Design, Dynamic Memory Management
 * @logic: A stack follows the LIFO (Last-In, First-Out) principle. To implement this
 * efficiently with a linked list, all operations must be performed at one end.
 * The most efficient end for a singly linked list is the **head**.
 * 1. **Push(x):** Create a new node with value 'x'. Point its 'next' to the current
 * head (top). Update the head pointer to this new node. This is O(1).
 * 2. **Pop():** Store the current head node in a temporary pointer. Advance the
 * head pointer to the next node. **Crucially, delete the node held by the temporary pointer to prevent memory leaks.** This is O(1).
 * 3. **Peek():** Return the data of the head node. O(1).
 * A 'count' variable is maintained for O(1) size retrieval.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION
 * ============================================================================
 * [Why Insert at the Beginning?]
 * In a singly linked list, we only have pointers moving in one direction (forward).
 * - **Inserting/Deleting at Head:** We have immediate access via the head pointer.
 * Cost: O(1).
 * - **Inserting/Deleting at Tail:** We must traverse the entire list to find the
 * end (unless we maintain a tail pointer, but deleting from the tail is still
 * O(N) in a singly linked list because we need to update the second-to-last node's pointer).
 *
 * Therefore, for a stack's LIFO behavior requiring O(1) operations, the head
 * of the linked list must represent the "top" of the stack.
 *
 * [Time Complexity Analysis]
 * - push(): O(1)
 * - pop(): O(1)
 * - peek(): O(1)
 * - size(): O(1)
 * - isEmpty(): O(1)
 *
 * [Space Complexity Analysis]
 * The stack uses O(N) space, where N is the number of elements, as each element
 * requires a node. Each operation uses O(1) auxiliary space.
 * ============================================================================
 */

/**
 * MISSION: Linked List Stack Implementation Protocol
 * RANK: C (Foundational Data Structure Design)
 * DEPARTMENT: Linear Data Structures & Memory Management
 * CHALLENGE:
 * Implement a Stack class using a linked list. The class should support the
 * following operations in O(1) time:
 * - push(int x): Add an element to the top of the stack.
 * - pop(): Remove the element from the top of the stack.
 * - peek(): Return the top element without removing it.
 * - isEmpty(): Check if the stack is empty.
 * - size(): Return the number of elements in the stack.
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

class myStack {
private:
    // 'top' points to the head of the linked list, which is the top of the stack.
    // Renamed from 'dummy' for clarity, as it's not a sentinel node.
    Node* top;
    int count; // Keeps track of the number of elements.

public:
    // Constructor: Initialize an empty stack.
    myStack() {
        top = NULL;
        count = 0;
    }

    // Destructor: CRITICAL for cleaning up dynamic memory when the stack is destroyed.
    ~myStack() {
        Node* temp = top;
        while (temp != NULL) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        // cout << "Destructor called: Memory freed." << endl; // For debug purposes
    }

    /**
     * Checks if the stack is empty.
     * @return true if empty, false otherwise.
     */
    bool isEmpty() {
        // Can check either count == 0 or top == NULL.
        return top == NULL;
    }

    /**
     * Adds an element to the top of the stack.
     * @param x The value to push.
     */
    void push(int x) {
        Node* newnode = new Node(x);
        // The new node points to the current top.
        newnode->next = top;
        // The new node becomes the new top.
        top = newnode;
        count++;
    }

    /**
     * Removes the element from the top of the stack.
     * Does nothing if the stack is empty.
     */
    void pop() {
        if (isEmpty()) {
            // Stack underflow condition.
            return;
        }
        // FIXED: Memory Leak Prevention.
        Node* temp = top; // Hold the node to be deleted.
        top = top->next;  // Move the top pointer to the next node.
        delete temp;      // CRITICAL: Free the memory of the popped node.
        count--;
    }

    /**
     * Returns the top element of the stack without removing it.
     * @return The top element, or -1 if the stack is empty.
     */
    int peek() {
        if (isEmpty()) {
            return -1; // Indicate empty stack.
        }
        return top->data;
    }

    /**
     * Returns the number of elements in the stack.
     * @return The size of the stack.
     */
    int size() {
        return count;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    cout << "INITIATING LINKED LIST STACK PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    // Create a stack object. It will be destroyed at the end of main().
    myStack s;

    // Test 1: Push operations
    cout << "Action: Push 10, 20, 30" << endl;
    s.push(10);
    s.push(20);
    s.push(30);
    cout << "Stack Size: " << s.size() << " (Expected: 3)" << endl;
    cout << "Top Element: " << s.peek() << " (Expected: 30)" << endl;
    cout << "-----------------------------" << endl;

    // Test 2: Pop operations
    cout << "Action: Pop once" << endl;
    s.pop();
    cout << "Top Element after pop: " << s.peek() << " (Expected: 20)" << endl;

    cout << "Action: Pop twice more" << endl;
    s.pop();
    s.pop();
    cout << "Stack Size after popping all: " << s.size() << " (Expected: 0)" << endl;
    cout << "Is Empty: " << (s.isEmpty() ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "-----------------------------" << endl;

    // Test 3: Edge Cases (Underflow)
    cout << "Action: Pop from empty stack (Underflow test)" << endl;
    s.pop(); // Should do nothing and not crash.
    cout << "Peek from empty stack: " << s.peek() << " (Expected: -1)" << endl;

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;
    // The destructor ~myStack() will be called automatically here.

    return 0;
}
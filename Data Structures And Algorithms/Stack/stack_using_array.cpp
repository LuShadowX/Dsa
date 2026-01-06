/**
 * @file stack_dynamic_array.cpp
 * @author LuShadowX
 * @brief Implement a Stack data structure using a dynamically allocated array.
 * @difficulty: Easy (Rank C)
 * @tags: Stack, Array, Dynamic Memory Management, Pointers
 * @logic: A Stack follows the LIFO (Last-In, First-Out) principle.
 * This implementation uses a raw pointer to dynamically allocate a fixed-size
 * array on the heap.
 *
 * Key Components:
 * 1. `int* arr`: A pointer to the beginning of the dynamically allocated integer array.
 * 2. `int top`: An index tracking the top element. Initialized to -1 (empty).
 * 3. `int size`: The maximum capacity of the stack.
 *
 * Operations:
 * - **Push(x):** Increment `top`, then store `x` at `arr[top]`. (Check for overflow first).
 * - **Pop():** Decrement `top`. (Check for underflow first).
 * - **Peek():** Return the value at `arr[top]`. (Check for underflow first).
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION & C++ MEMORY CONCEPTS
 * ============================================================================
 * [Raw Pointers vs. std::vector Initial Behavior]
 * It is crucial to understand why simply declaring `std::vector<int> arr;` and
 * trying to access `arr[++top]` fails, while dynamic array allocation works.
 *
 * 1. The Vector Trap:
 * Declaring `vector<int> arr;` creates a vector with capacity 0. No memory
 * is actually allocated to hold elements. Accessing `arr[0]` immediately
 * results in undefined behavior (usually a crash due to out-of-bounds access).
 * To use a vector like a fixed array, it must be initialized with size:
 * `vector<int> arr(n);`
 *
 * 2. The Dynamic Array Solution (Used Here):
 * Declaring `int* arr;` only creates a pointer intended to hold an address.
 * It does not create storage for integers.
 * The line `arr = new int[n];` is essential. It:
 * a. Requests a contiguous block of memory on the HEAP large enough to hold 'n' integers.
 * b. Returns the starting address of that block.
 * c. Assigns that address to the pointer `arr`.
 * Once allocated, we can safely access indices from `0` to `n-1`.
 *
 * [Memory Management Responsibility]
 * Because we manually allocated memory with `new[]`, we MUST manually deallocate
 * it with `delete[]` in the class destructor to prevent memory leaks.
 *
 * [Time Complexity Analysis]
 * - push(): O(1)
 * - pop(): O(1)
 * - peek(): O(1)
 * - isEmpty(): O(1)
 * - isFull(): O(1)
 *
 * [Space Complexity Analysis]
 * The stack uses O(N) space, where N is the fixed capacity allocated in the constructor.
 * ============================================================================
 */

#include <iostream>

using namespace std;

class myStack {
private:
    int top;      // Index of the current top element
    int capacity; // Maximum size of the stack (renamed from 'size' for clarity)
    int* arr;     // Pointer to the dynamically allocated array

public:
    /**
     * @brief Constructor: Initializes stack with specific capacity.
     * Allocates dynamic memory for the array.
     * @param n The maximum number of elements the stack can hold.
     */
    myStack(int n) {
        capacity = n;
        top = -1; // Indicates empty stack
        arr = new int[n]; // CRITICAL: Dynamic memory allocation on heap
        // cout << "Stack initialized with capacity: " << n << endl;
    }

    /**
     * @brief Destructor: Cleans up dynamic memory.
     * CRITICAL: Essential to prevent memory leaks when stack object is destroyed.
     */
    ~myStack() {
        delete[] arr; // CRITICAL: Free the memory allocated by new[]
        // cout << "Stack destroyed. Memory freed." << endl;
    }

    /**
     * Checks if the stack is empty.
     * @return true if empty (top is -1), false otherwise.
     */
    bool isEmpty() {
        return top == -1;
    }

    /**
     * Checks if the stack is full.
     * @return true if full (top reaches capacity-1), false otherwise.
     */
    bool isFull() {
        return top == capacity - 1;
    }

    /**
     * Pushes an element onto the top of the stack.
     * Includes basic overflow protection.
     * @param x The value to push.
     */
    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push " << x << endl;
            return;
        }
        // Pre-increment top, then assign value.
        arr[++top] = x;
    }

    /**
     * Removes the top element from the stack.
     * Does nothing if the stack is empty (underflow protection).
     */
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Cannot pop." << endl;
            return;
        }
        // Decrement top pointer to logically remove element.
        top--;
    }

    /**
     * Returns the top element without removing it.
     * @return The top value, or -1 if empty.
     */
    int peek() {
        if (isEmpty()) {
            // Returning -1 indicates empty, assuming -1 isn't a valid data value.
            // Ideally, throw an exception or use std::optional in modern C++.
            return -1;
        }
        return arr[top];
    }

    /**
     * Helper to get current number of elements.
     */
    int currentSize() {
        return top + 1;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    cout << "INITIATING DYNAMIC ARRAY STACK PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    int capacity = 5;
    myStack s(capacity);

    // Test 1: Push operations
    cout << "Action: Push 10, 20, 30, 40, 50" << endl;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    cout << "Current Size: " << s.currentSize() << " (Expected: 5)" << endl;
    cout << "Top Element: " << s.peek() << " (Expected: 50)" << endl;
    cout << "Is Full: " << (s.isFull() ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "-----------------------------" << endl;

    // Test 2: Overflow check
    cout << "Action: Attempt push 60 (Overflow Test)" << endl;
    s.push(60); // Should print overflow message
    cout << "-----------------------------" << endl;

    // Test 3: Pop operations
    cout << "Action: Pop twice" << endl;
    s.pop(); // Pops 50
    s.pop(); // Pops 40
    cout << "Top Element after pops: " << s.peek() << " (Expected: 30)" << endl;
    cout << "-----------------------------" << endl;

    // Test 4: Emptying stack and Underflow check
    cout << "Action: Pop remaining elements until empty" << endl;
    while (!s.isEmpty()) {
        s.pop();
    }
    cout << "Is Empty: " << (s.isEmpty() ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "Action: Attempt pop empty stack (Underflow Test)" << endl;
    s.pop(); // Should print underflow message
    cout << "Peek empty stack: " << s.peek() << " (Expected: -1)" << endl;

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;
    // Destructor ~myStack() is called implicitly here, freeing memory.

    return 0;
}
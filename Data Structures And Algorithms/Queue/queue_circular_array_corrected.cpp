/**
 * @file queue_circular_array_corrected.cpp
 * @author LuShadowX
 * @brief Implement a Queue using a dynamically allocated array (Circular implementation).
 * @problem_link: https://www.geeksforgeeks.org/problems/implement-queue-using-array/1
 * @difficulty: Easy-Medium (Rank C+)
 * @tags: Queue, Circular Buffer, Array, Dynamic Memory Management
 * @logic: Utilizes a fixed-size array treated as a circular buffer to efficiently use space.
 * - `front`: Index of the actual front element.
 * - `end`: Index of the *next available slot* for insertion.
 * - `count`: Tracks the current number of elements to easily determine empty/full states.
 *
 * Crucial changes from linear version:
 * 1. Index updates use modulo arithmetic: `index = (index + 1) % size`.
 * 2. A destructor is included to free allocated memory.
 * 3. Safety checks added to enqueue/dequeue.
 */

/**
 * ============================================================================
 * ALGORITHMIC FOUNDATION: THE CIRCULAR BUFFER
 * ============================================================================
 * [Solving the Drifting Problem]
 * In a linear array queue, dequeuing items leaves unused space at the start.
 * A circular queue connects the end of the array back to the beginning.
 *
 * Array Capacity N=5. Indices 0..4.
 *
 * State: Front=3, End=0 (Wrapped around), Count=2. Array: [E2][ ][ ][E1][ ]
 *
 * Action: enqueue(E3)
 * We insert at `end` (index 0).
 * New `end` becomes `(0 + 1) % 5 = 1`.
 * State: Front=3, End=1, Count=3. Array: [E2][E3][ ][E1][ ]
 *
 * Action: dequeue()
 * We remove from `front` (index 3).
 * New `front` becomes `(3 + 1) % 5 = 4`.
 * State: Front=4, End=1, Count=2.
 *
 * This ensures that as long as `count < size`, we can always insert, utilizing
 * any free space regardless of where `front` begins.
 *
 * [Time Complexity Analysis]
 * - enqueue(), dequeue(), peek operations: O(1) due to direct indexing and math.
 *
 * [Space Complexity Analysis]
 * O(N) space allocated for the array of size N.
 * ============================================================================
 */

#include <iostream>

using namespace std;

class myQueue {
private:
    int * arr;      // Pointer for dynamic array
    int size;       // Maximum capacity
    int front;      // Index of the front element
    int end;        // Index of the next free slot
    int count;      // Current number of elements

public:
    /**
     * Constructor: Allocates memory and initializes indices.
     * @param n The maximum capacity of the queue.
     */
    myQueue(int n) {
        size = n;
        arr = new int[n];
        front = 0;
        end = 0;
        count = 0;
        // cout << "Circular Queue initialized with capacity: " << n << endl;
    }

    /**
     * Destructor: CRITICAL for freeing dynamic memory.
     */
    ~myQueue() {
        delete[] arr;
        // cout << "Queue destroyed. Memory freed." << endl;
    }

    /**
     * Checks if the queue is empty.
     * Time Complexity: O(1)
     */
    bool isEmpty() {
        return count == 0;
    }

    /**
     * Checks if the queue is full.
     * Time Complexity: O(1)
     */
    bool isFull() {
        return count == size;
    }

    /**
     * Adds an element to the rear of the queue using circular logic.
     * @param x The value to enqueue.
     * Time Complexity: O(1)
     */
    void enqueue(int x) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot enqueue " << x << endl;
            return;
        }
        arr[end] = x;
        // Circular increment: Wrap around if at the last index.
        end = (end + 1) % size;
        count++;
    }

    /**
     * Removes the element from the front using circular logic.
     * Time Complexity: O(1)
     */
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! Cannot dequeue." << endl;
            return;
        }
        // Circular increment: Wrap around if at the last index.
        front = (front + 1) % size;
        count--;
    }

    /**
     * Returns the front element.
     * Time Complexity: O(1)
     */
    int getFront() {
        if (isEmpty()) return -1;
        return arr[front];
    }

    /**
     * Returns the rear element.
     * Logic: 'end' points to the *next free slot*. The actual rear element
     * is at the index immediately preceding 'end', handling wrap-around.
     * Time Complexity: O(1)
     */
    int getRear() {
        if (isEmpty()) return -1;
        // Mathematical trick to handle wrap-around correctly:
        // If end is 0, we want index size-1.
        // (end - 1 + size) % size ensures a positive result between 0 and size-1.
        int rearIndex = (end - 1 + size) % size;
        return arr[rearIndex];
    }

    // Helper for debugging output
    int getCurrentSize() { return count; }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    cout << "INITIATING CIRCULAR ARRAY QUEUE PROTOCOL..." << endl;
    cout << "-----------------------------" << endl;

    int capacity = 3;
    myQueue q(capacity);

    // Test 1: Fill the queue
    cout << "Action: Enqueue 10, 20, 30" << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout << "Size: " << q.getCurrentSize() << ", Front: " << q.getFront() << ", Rear: " << q.getRear() << endl;
    cout << "Is Full: " << (q.isFull() ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "-----------------------------" << endl;

    // Test 2: Overflow check
    cout << "Action: Attempt to enqueue 40 (Overflow test)" << endl;
    q.enqueue(40); // Should print overflow message
    cout << "-----------------------------" << endl;

    // Test 3: Dequeue and demonstrate circular behavior
    cout << "Action: Dequeue once (removes 10)" << endl;
    q.dequeue();
    cout << "Size: " << q.getCurrentSize() << ", Front: " << q.getFront() << " (Expected: 20)" << endl;

    // Now there is space at index 0. A linear queue would fail here.
    // A circular queue should succeed.
    cout << "Action: Enqueue 40 (Testing wrap-around insertion)" << endl;
    q.enqueue(40);
    cout << "Size: " << q.getCurrentSize() << ", Front: " << q.getFront() << ", Rear: " << q.getRear() << " (Expected Rear: 40)" << endl;

    if (q.getRear() == 40 && q.isFull()) {
        cout << "Verification: SUCCESS - Circular insertion worked." << endl;
    } else {
        cout << "Verification: FAILURE." << endl;
    }
    cout << "-----------------------------" << endl;

    // Test 4: Emptying and underflow
    cout << "Action: Empty the queue" << endl;
    while(!q.isEmpty()) { q.dequeue(); }
    cout << "Is Empty: " << (q.isEmpty() ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "Action: Dequeue from empty (Underflow test)" << endl;
    q.dequeue(); // Should print underflow message

    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;
    // Destructor is called here, freeing memory.

    return 0;
}
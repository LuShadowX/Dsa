/**
 * @file tower_of_hanoi.cpp
 * @author LuShadowX
 * @brief Solve the Tower of Hanoi problem by counting minimum moves.
 * @problem_link: https://www.geeksforgeeks.org/problems/tower-of-hanoi-1587115621/1
 * @difficulty: Medium (Rank B)
 * @tags: Recursion, Math, Puzzle
 * @logic: The problem follows a recursive structure based on the observation that
 * to move N disks from Source to Destination:
 * 1. We must first move the top N-1 disks from Source to Aux.
 * 2. Then, move the largest (Nth) disk from Source to Destination (1 move).
 * 3. Finally, move the N-1 disks from Aux to Destination.
 * This implementation utilizes a reference counter to track these steps through the recursion tree.
 */

/**
 * ============================================================================
 * MATHEMATICAL FOUNDATION & FORMULAE
 * ============================================================================
 * The minimum number of moves T(N) required to transfer N disks is defined by
 * the following recurrence relation:
 *
 * [Recurrence Formula]
 * T(N) = 2 * T(N-1) + 1
 *
 * Where:
 * - 2 * T(N-1): The cost of moving the N-1 stack twice (Source->Aux, then Aux->Dest).
 * - +1: The cost of moving the single largest disk (Source->Dest).
 * - Base Case: T(1) = 1
 *
 * [Closed-Form Solution]
 * Solving this recurrence yields the direct formula for total moves:
 * Total Moves = 2^N - 1
 *
 * Example: For N=3 disks, Total Moves = 2³ - 1 = 8 - 1 = 7.
 * ============================================================================
 */

/**
 * MISSION: Tower of Hanoi Protocol
 * RANK: B (Classic Recursive Puzzle)
 * DEPARTMENT: Recursive Algorithms & Mathematical Induction
 * CHALLENGE:
 * Determine the minimum number of moves required to move N disks from a
 * source rod 'from' to a destination rod 'to' using an auxiliary rod 'aux',
 * following standard Tower of Hanoi rules (only one disk at a time, larger
 * disks cannot be placed on smaller disks).
 * CONSTRAINTS:
 * - Time Complexity: O(2^N) - The number of moves grows exponentially.
 * - Space Complexity: O(N) - Due to the maximum depth of the recursion stack.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /**
     * THE RECURSIVE MOVER (Helper Function)
     * Recursively breaks down the problem and counts moves based on the recurrence relation.
     * @param n Number of disks to move in this step.
     * @param from Index of the source rod.
     * @param to Index of the destination rod.
     * @param aux Index of the auxiliary helper rod.
     * @param count Reference to the total move counter accumulating across calls.
     */
    void solve(int n, int from, int to, int aux, int& count) {
        // BASE CASE: Only one disk to move. T(1) = 1.
        if (n == 1) {
            count++;
            return;
        }

        // RECURSIVE STEP 1: Move N-1 disks from 'from' to 'aux'.
        // Contribution: T(N-1) moves.
        solve(n - 1, from, aux, to, count);

        // CURRENT STEP: Move the Nth largest disk from 'from' to 'to'.
        // Contribution: +1 move.
        count++;

        // RECURSIVE STEP 2: Move N-1 disks from 'aux' to 'to'.
        // Contribution: T(N-1) moves.
        solve(n - 1, aux, from, to, count);
    }

public:
    /**
     * Initiates the Tower of Hanoi solution.
     * @param n Total number of disks.
     * @param from Source rod index.
     * @param to Destination rod index.
     * @param aux Auxiliary rod index.
     * @return Total minimum moves required (should equal 2^N - 1).
     */
    int towerOfHanoi(int n, int from, int to, int aux) {
        int count = 0;
        // Start the recursive counting process
        solve(n, from, to, aux, count);
        return count;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    // TEST CASE SETUP: N = 4 disks
    int N = 4;
    int rod1 = 1, rod2 = 2, rod3 = 3;

    cout << "INITIATING TOWER OF HANOI PROTOCOL (N=" << N << ")..." << endl;

    // Execute the mission
    // Note: GFG problem typically asks for (N, from, aux, to). Adjusting call to match parameters.
    int totalMoves = solver.towerOfHanoi(N, rod1, rod3, rod2);

    // Report findings
    cout << "REPORT:" << endl;
    cout << "Total minimum moves calculated via recursion: " << totalMoves << endl;
    
    // Mathematical Verification using the closed-form formula
    long long expectedMoves = pow(2, N) - 1;
    cout << "Mathematical Verification (2^N - 1): " << expectedMoves << endl;

    if (totalMoves == expectedMoves) {
        cout << "STATUS: SUCCESS - Result matches mathematical definition." << endl;
    } else {
        cout << "STATUS: FAILURE - Discrepancy detected." << endl;
    }

    cout << "MISSION COMPLETE." << endl;

    return 0;
}
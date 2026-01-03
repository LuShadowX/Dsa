/**
 * @file n_queens.cpp
 * @author LuShadowX
 * @brief Solve the N-Queens problem using Backtracking.
 * @problem_link: https://leetcode.com/problems/n-queens/
 * @difficulty: Hard (Rank S)
 * @tags: Backtracking, Recursion, Matrix
 * @logic: We attempt to place queens row by row. In each row, we iterate through
 * all columns. Before placing a queen, we use an 'isSafe' function to check if
 * she would be under attack from previously placed queens (checking vertical-up,
 * diagonal-up-left, and diagonal-up-right). If safe, we place the queen and recurse
 * to the next row. If the recursive path fails to find a solution, we backtrack
 * by removing the queen and trying the next column.
 */
/**
 * MISSION: N-Queens Alignment Protocol
 * RANK: S (Complex Strategic Deployment)
 * DEPARTMENT: Recursion & Backtracking Division
 * CHALLENGE:
 * Deploy N queens on an N×N chessboard such that no two queens can attack each
 * other. This means no two queens can share the same row, column, or diagonal.
 * Return all distinct board configurations that satisfy this condition.
 * CONSTRAINTS:
 * - Time Complexity: O(N!) - In the worst case, we explore many permutations, though pruning helps.
 * - Space Complexity: O(N^2) to store the board configurations, plus O(N) for recursion stack.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * --- PART 1: THE RADAR (Safety Check Protocol) ---
     * Determines if placing a queen at board[row][col] is safe given current deployments.
     * Since we place queens row by row from top to bottom, we only need to check
     * directions upwards from the current position.
     */
    bool isSafe(int row, int col, vector<string>& board, int n) {
        // 1. Check Vertical Vector (Upwards)
        for (int i = 0; i < row; i++)
            if (board[i][col] == 'Q') return false;

        // 2. Check Upper-Left Diagonal Vector
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 'Q') return false;

        // 3. Check Upper-Right Diagonal Vector
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
            if (board[i][j] == 'Q') return false;

        return true; // No immediate threats detected. Deployment authorized.
    }

    /**
     * --- PART 2: THE BRAIN (Recursive Backtracking Core) ---
     * Tries to place queens row by row.
     */
    void solve(int row, int n, vector<string>& board, vector<vector<string>>& ans) {
        // BASE CASE: Mission Success. All N rows have been successfully filled.
        if (row == n) {
            ans.push_back(board); // Capture current board state
            return;
        }

        // Iterate through all possible columns for the current row
        for (int col = 0; col < n; col++) {
            // If the spot is safe according to Radar...
            if (isSafe(row, col, board, n)) {
                // 1. CHOOSE: Deploy queen at current coordinates
                board[row][col] = 'Q';

                // 2. EXPLORE: Move to deploy in the next row
                solve(row + 1, n, board, ans);

                // 3. BACKTRACK: Revoke deployment. Remove queen to explore other column options for this row.
                board[row][col] = '.'; 
            }
        }
    }

    /**
     * Initiates the N-Queens solution process.
     * @param n The size of the board (N*N) and number of queens.
     * @return A vector containing all distinct valid board configurations.
     */
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        // Initialize empty board with '.'
        vector<string> board(n, string(n, '.')); 
        
        // Start the recursive process from row 0
        solve(0, n, board, ans);
        
        return ans;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    // TEST CASE SETUP: N = 4
    // A standard test case that should yield 2 distinct solutions.
    int N = 4;

    cout << "INITIATING N-QUEENS ALIGNMENT PROTOCOL (N=" << N << ")..." << endl;
    
    // Execute the mission
    vector<vector<string>> solutions = solver.solveNQueens(N);

    // Report findings
    cout << "REPORT:" << endl;
    cout << "Total distinct solutions found: " << solutions.size() << endl;
    cout << "-----------------------------" << endl;
    for (int i = 0; i < solutions.size(); ++i) {
        cout << "Solution " << i + 1 << ":" << endl;
        for (const string& row : solutions[i]) {
            cout << "  " << row << endl;
        }
        cout << "-----------------------------" << endl;
    }
    cout << "MISSION COMPLETE." << endl;

    return 0;
}
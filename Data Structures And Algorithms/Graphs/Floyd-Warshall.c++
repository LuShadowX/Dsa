/**
 * @file floyd_warshall.cpp
 * @author LuShadowX
 * @brief Floyd-Warshall Algorithm for All-Pairs Shortest Path.
 * @problem_link: https://www.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1
 * @difficulty: Medium (Rank A)
 * @tags: Graph Theory, All-Pairs Shortest Path, Dynamic Programming
 * @logic: A dynamic programming approach that iterates through all possible
 * intermediate vertices 'k'. For every pair of vertices (i, j), it checks if
 * traveling via 'k' offers a shorter path than the currently known path from 'i' to 'j'.
 * The state transition is: dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]).
 */
/**
 * MISSION: Floyd-Warshall Protocol (Global Network Optimization)
 * RANK: A (Comprehensive Pathfinding Strategy)
 * DEPARTMENT: Graph Theory & Dynamic Programming
 * CHALLENGE:
 * Determine the shortest path distances between EVERY pair of nodes in a
 * weighted graph. The graph is represented by an adjacency matrix.
 * It can handle negative edge weights, but not negative weight cycles.
 * CONSTRAINTS:
 * - Time Complexity: O(V^3) - Cubic complexity due to three nested loops.
 * Suitable for dense graphs with a smaller number of vertices (e.g., V <= 400).
 * - Space Complexity: O(V^2) - Performed in-place on the adjacency matrix.
 * NOTE:
 * Negative cycles can be detected if any diagonal element dist[i][i] becomes < 0
 * after execution.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * Executes the Floyd-Warshall algorithm in-place on the distance matrix.
     * @param dist The adjacency matrix where dist[i][j] holds the weight of edge i->j.
     * Infinity is represented by 1e8. dist[i][i] should be 0.
     */
    void floydWarshall(vector<vector<int>> &dist) {
        int size = dist.size();
        
        // k = The intermediate vertex being considered as a stepping stone.
        for(int k = 0; k < size; k++){
            // i = Source vertex
            for(int i = 0; i < size; i++){
                // j = Destination vertex
                for(int j = 0; j < size; j++){
                    
                    // Check for Infinity (1e8) to avoid integer overflow during addition.
                    // We only proceed if paths i->k and k->j actually exist.
                    if(dist[i][k] != 1e8 && dist[k][j] != 1e8){
                        // Relaxation Step:
                        // If going from i to j via k is cheaper than the direct i to j path, update it.
                        if(dist[i][k] + dist[k][j] < dist[i][j]){
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }
        
        // --- Hazard Detection: Negative Cycle Check (Optional) ---
        // If needed, check diagonal elements after the main loops.
        /*
        for(int i=0; i<size; i++){
            if(dist[i][i] < 0) {
                // Negative cycle detected reachable from node i.
                // Handle accordingly (e.g., return flag or define behavior).
            }
        }
        */
    } 
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    // TEST CASE SETUP:
    // Constructing a weighted directed graph using an adjacency matrix.
    // V = 4 vertices (0 to 3).
    const int INF = 1e8;
    vector<vector<int>> matrix = {
        {0,   5,   INF, 10},
        {INF, 0,   3,   INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };
    // Edges roughly correspond to: 0->1(5), 0->3(10), 1->2(3), 2->3(1)

    cout << "INITIATING FLOYD-WARSHALL GLOBAL OPTIMIZATION..." << endl;
    cout << "Initial State Matrix:" << endl;
    for(const auto& row : matrix) {
        for(int val : row) {
            if(val == INF) cout << "INF\t"; else cout << val << "\t";
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;

    // Execute the mission (in-place update)
    solver.floydWarshall(matrix);

    // Report findings
    cout << "OPTIMIZED ALL-PAIRS SHORTEST PATHS MATRIX:" << endl;
    for(const auto& row : matrix) {
        for(int val : row) {
            if(val == INF) {
                cout << "INF\t";
            } else {
                cout << val << "\t";
            }
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    // Expected Output:
    // 0    5    8    9
    // INF  0    3    4
    // INF  INF  0    1
    // INF  INF  INF  0

    return 0;
}
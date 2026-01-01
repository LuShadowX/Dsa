/**
 * @file bellman_ford.cpp
 * @author LuShadowX
 * @brief Bellman-Ford Algorithm for Shortest Paths with Negative Cycle Detection.
 * @problem_link: https://www.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1
 * @difficulty: Medium (Rank A)
 * @tags: Graph Theory, Shortest Path, Dynamic Programming, Negative Cycle Detection
 * @logic: Iteratively relax all edges (V-1) times. This guarantees that shortest paths
 * with at most (V-1) edges are found. A final (V-th) pass checks if any
 * distance can still be improved. If relaxation is possible in the V-th pass,
 * it indicates the presence of a negative weight cycle reachable from the source.
 */
/**
 * MISSION: Bellman-Ford Protocol (Negative Cycle Detection)
 * RANK: A (Strategic Pathfinding with Hazard Detection)
 * DEPARTMENT: Graph Theory & Optimization
 * CHALLENGE:
 * Determine shortest paths in a weighted graph that may contain negative edge weights.
 * Crucially, identify if a "negative weight cycle" exists, which means shortest
 * paths are undefined (they can become infinitely small).
 * CONSTRAINTS:
 * - Time Complexity: O(V * E) - Slower than Dijkstra, but necessary for negative weights.
 * - Space Complexity: O(V) for distance tracking.
 * - Used here for Directed Graphs.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * Executes the Bellman-Ford algorithm.
     * @param V Number of vertices.
     * @param edges Vector of edges, where each edge is {u, v, weight}.
     * @param src The source vertex.
     * @return A vector of shortest distances, or {-1} if a negative cycle is detected.
     */
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        // Initialize distances with a large value (infinity representation).
        // Using 1e8 as safe infinity for this problem's constraints.
        vector<int> distance(V, 1e8);
        
        // --- Start Protocol: Initialize Source ---
        distance[src] = 0;
        
        // --- Main Relaxation Loop (V-1 Iterations) ---
        // We relax all edges V-1 times to guarantee shortest paths in a graph with no negative cycles.
        for(int i = 0; i < V - 1; i++) {
            for(auto it : edges) {
                int u = it[0];
                int v = it[1];
                int w = it[2];
                
                // Relaxation step:
                // Ensure u is reachable (distance[u] != 1e8) before trying to relax v.
                if(distance[u] != 1e8 && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                }
            }
        }
        
        // --- Hazard Detection: Negative Cycle Check (V-th Iteration) ---
        // Perform one more relaxation pass. If any distance decreases, a negative cycle exists.
        for(auto it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];
            if(distance[u] != 1e8 && distance[u] + w < distance[v]) {
                // Negative cycle detected! Shortest paths are undefined.
                return {-1}; 
            }
        }
        
        // No negative cycles found. Return the calculated distances.
        return distance;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    // TEST CASE SETUP:
    // Constructing a directed graph with 3 vertices and negative weights.
    // Edges: 0->1 (-1), 1->2 (-2), 0->2 (4)
    // This graph has negative edges but NO negative cycle.
    int V = 3;
    int src = 0;
    vector<vector<int>> edges = {
        {0, 1, -1},
        {1, 2, -2},
        {0, 2, 4}
    };

    cout << "INITIATING BELLMAN-FORD PROTOCOL FROM SOURCE NODE " << src << "..." << endl;
    
    // Execute the mission
    vector<int> result = solver.bellmanFord(V, edges, src);

    // Report findings
    cout << "STATUS REPORT:" << endl;
    if (result.size() == 1 && result[0] == -1) {
        cout << "HAZARD WARNING: Negative Weight Cycle Detected!" << endl;
    } else {
        cout << "Shortest Path Distances:" << endl;
        cout << "-----------------------------" << endl;
        for (int i = 0; i < V; ++i) {
            cout << "Node " << i << " : ";
            if (result[i] == 1e8) {
                cout << "UNREACHABLE" << endl;
            } else {
                cout << result[i] << endl;
            }
        }
        cout << "-----------------------------" << endl;
    }
    cout << "MISSION COMPLETE." << endl;

    // Expected output for this test case: Node 0: 0, Node 1: -1, Node 2: -3

    return 0;
}
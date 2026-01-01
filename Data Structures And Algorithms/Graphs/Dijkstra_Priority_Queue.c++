/**
 * @file dijkstra.cpp
 * @author LuShadowX
 * @brief Dijkstra's Shortest Path Algorithm using a Priority Queue.
 * @problem_link: https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1
 * @difficulty: Medium (Rank A)
 * @tags: Graph Theory, Shortest Path, Greedy Algorithm, Priority Queue
 * @logic: utilizes a Min-Priority Queue to greedily select the closest vertex
 * that hasn't been processed yet. It relaxes edges, updating the shortest
 * path to neighbors if a better path is found through the current vertex.
 */
/**
 * MISSION: Dijkstra's Shortest Path Protocol
 * RANK: A (Strategic Pathfinding Algorithm)
 * DEPARTMENT: Graph Theory & Optimization
 * CHALLENGE:
 * In a weighted network, determine the shortest path costs from a single 
 * Source Command Node to all other accessible network nodes.
 * CONSTRAINTS:
 * - Time Complexity: O(E log V) using a binary heap (priority queue).
 * - Space Complexity: O(V + E) for adjacency list and distance tracking.
 * - Weights must be non-negative.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * THE PATHFINDER GENERAL (Dijkstra's Algorithm)
     * Finds the shortest distance from source to all vertices.
     * @param V Number of vertices.
     * @param edges Vector of edges where each edge is {u, v, weight}.
     * @param src The source vertex.
     * @return A vector of shortest distances from src to every node.
     */
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        // Min-heap storing {distance, node}, ordered by distance ascending.
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        // Build Adjacency list: adj[node] -> {weight, neighbor}
        vector<vector<pair<int,int>>> adj(V);
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];
            adj[u].push_back({w, v});
            // adj[v].push_back({w, u}); // Uncomment for undirected graph
        }

        // Distance array initialized with infinity (1e9 represents unreachable)
        vector<int> distance(V, 1e9);

        // --- Start Protocol: Initialize Source ---
        distance[src] = 0;
        pq.push({0, src});

        // --- Main Relaxation Loop ---
        while (!pq.empty()) {
            int node = pq.top().second;      // current node
            int weight = pq.top().first;     // distance reached so far
            pq.pop();

            // Optimization: Skip if we found a shorter path to this node already
            // This handles outdated entries in the PQ.
            if (weight > distance[node]) continue;

            // Relax all adjacent edges
            for (auto it : adj[node]) {
                int edgeWeight = it.first;
                int neighbor = it.second;

                // If a shorter path to the neighbor is found via current node
                if (weight + edgeWeight < distance[neighbor]) {
                    distance[neighbor] = weight + edgeWeight;
                    // Push new shortest distance to PQ
                    pq.push({distance[neighbor], neighbor});
                }
            }
        }

        return distance;   // Return final shortest distances
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    // TEST CASE SETUP:
    // Constructing a weighted directed graph with 6 vertices (0 to 5)
    int V = 6;
    int src = 0;

    // Edges represented as {u, v, w} (from, to, weight)
    vector<vector<int>> edges = {
        {0, 1, 4}, {0, 2, 4},
        {1, 2, 2}, {2, 3, 3}, {2, 4, 1},
        {2, 5, 6}, {3, 5, 2}, {4, 5, 3}
    };

    cout << "INITIATING DIJKSTRA'S PROTOCOL FROM SOURCE NODE " << src << "..." << endl;
    
    // Execute the mission
    vector<int> result = solver.dijkstra(V, edges, src);

    // Report findings
    cout << "SHORTEST PATH DISTANCES REPORT:" << endl;
    cout << "-----------------------------" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Node " << i << " : ";
        if (result[i] == 1e9) {
            cout << "UNREACHABLE" << endl;
        } else {
            cout << result[i] << endl;
        }
    }
    cout << "-----------------------------" << endl;
    cout << "MISSION COMPLETE." << endl;

    return 0;
}
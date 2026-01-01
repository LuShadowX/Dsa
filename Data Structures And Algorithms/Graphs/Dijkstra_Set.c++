/**
 * @file dijkstra_set.cpp
 * @author LuShadowX
 * @brief Dijkstra's Shortest Path Algorithm using a std::set.
 * @problem_link: https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1
 * @difficulty: Medium (Rank A)
 * @tags: Graph Theory, Shortest Path, Greedy Algorithm, std::set
 * @logic: Utilizes a std::set to store pairs of {distance, node}. The set
 * automatically keeps elements sorted by distance, acting as a min-priority queue.
 * A key advantage of using a set is the ability to explicitly find and remove
 * an outdated (longer) distance entry for a node before inserting a new,
 * shorter path found during relaxation. This ensures each node is in the set
 * at most once with its current shortest distance.
 */
/**
 * MISSION: Dijkstra's Shortest Path Protocol (Set Variant)
 * RANK: A (Strategic Pathfinding Algorithm)
 * DEPARTMENT: Graph Theory & Optimization
 * CHALLENGE:
 * In a weighted network, determine the shortest path costs from a single 
 * Source Command Node to all other accessible network nodes. This variant
 * leverages the properties of a balanced binary search tree (std::set) for
 * managing path candidates.
 * CONSTRAINTS:
 * - Time Complexity: O(E log V). Set operations (insert/erase) take O(log V).
 * - Space Complexity: O(V + E) for adjacency list and distance tracking.
 * - Weights must be non-negative.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * THE PATHFINDER GENERAL (Dijkstra's Algorithm - Set Version)
     * Finds the shortest distance from source to all vertices.
     * @param V Number of vertices.
     * @param edges Vector of edges where each edge is {u, v, weight}.
     * @param src The source vertex.
     * @return A vector of shortest distances from src to every node.
     */
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        // Set storing {distance, node}.
        // The set keeps elements sorted based on distance (first element of pair).
        // This allows us to efficiently retrieve the node with the minimum distance.
        set<pair<int,int>> st;

        // Adjacency list: adj[node] -> {weight, neighbor}
        vector<vector<pair<int,int>>> adj(V);

        // Distance array initialized with a large value (infinity)
        vector<int> distance(V, 1e9);

        // Build adjacency list from edges
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];

            adj[u].push_back({w, v});
            // adj[v].push_back({w, u}); // Uncomment for undirected graph
        }

        // --- Start Protocol: Initialize Source ---
        distance[src] = 0;
        st.insert({0, src});

        // --- Main Relaxation Loop ---
        while (!st.empty()) {
            // Extract node with the minimum distance.
            // st.begin() points to the smallest element in the set.
            auto it = *(st.begin());
            int weight = it.first;
            int node = it.second;

            // Remove the processed node from the set.
            st.erase(it);

            // Relax all adjacent edges
            for (auto it : adj[node]) {
                int neighbor = it.second;
                int edgeWeight = it.first;

                // If a shorter path to the neighbor is found via current node
                if (weight + edgeWeight < distance[neighbor]) {
                    
                    // Tactical Advantage of Set:
                    // If the neighbor was already reached with a longer path,
                    // we explicitly remove that outdated entry from the set.
                    if (distance[neighbor] != 1e9) {
                        st.erase({distance[neighbor], neighbor});
                    }

                    // Update distance and insert the new, shorter path entry.
                    distance[neighbor] = weight + edgeWeight;
                    st.insert({distance[neighbor], neighbor});
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

    cout << "INITIATING DIJKSTRA'S PROTOCOL (SET VARIANT) FROM SOURCE NODE " << src << "..." << endl;
    
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
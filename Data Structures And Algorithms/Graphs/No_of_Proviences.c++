/**
 * @file number_of_provinces.cpp
 * @author LuShadowX
 * @brief Count the number of connected components (provinces) in a graph.
 * @problem_link: https://www.geeksforgeeks.org/problems/number-of-provinces/1
 * @difficulty: Medium (Rank A)
 * @tags: Graph Theory, DFS, Connected Components, Adjacency Matrix
 * @logic: The problem asks for the number of connected components. We iterate through
 * each node from 0 to V-1. If a node hasn't been visited yet, it belongs to a new
 * province. We increment the province count and start a traversal (DFS in this case)
 * to mark all nodes reachable from it (i.e., the entire province) as visited.
 * Since the input is an adjacency matrix, the DFS checks connectivity by iterating
 * through the row corresponding to the current node.
 */
/**
 * MISSION: Province Enumeration Protocol
 * RANK: A (Standard Graph connectivity analysis)
 * DEPARTMENT: Graph Theory
 * CHALLENGE:
 * Given an undirected graph represented by an adjacency matrix adj[][], where
 * adj[i][j] = 1 denotes a connection between city i and city j, determine the
 * total number of disconnected provinces.
 * CONSTRAINTS:
 * - Time Complexity: O(V^2) - We iterate through every cell of the V*V matrix during DFS.
 * - Space Complexity: O(V) - For the visited array and recursion stack.
 * - 0-based indexing used for vertices.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /**
     * THE TERRITORY MAPPER (Recursive DFS Helper)
     * Explores and marks all cities within the current province.
     * Works directly on the adjacency matrix.
     * @param adj The adjacency matrix representation of the graph.
     * @param node The current city being explored.
     * @param visited Reference to the visited status vector.
     */
    void dfs(vector<vector<int>>& adj, int node, vector<int>& visited) {
        // Mark the current headquarters as visited
        visited[node] = 1;

        // Scan the adjacency matrix row for this node to find neighbors
        for (int neighbor = 0; neighbor < adj.size(); neighbor++) {
            // If a connection exists (adj[node][neighbor] == 1) AND it's unvisited
            if (adj[node][neighbor] == 1 && visited[neighbor] == 0) {
                // Recursively explore the connected city
                dfs(adj, neighbor, visited);
            }
        }
    }

public:
    /**
     * Counts the total number of provinces.
     * @param adj The adjacency matrix.
     * @param V The number of vertices (cities).
     * @return The count of connected components.
     */
    int numProvinces(vector<vector<int>> adj, int V) {
        // Track visited status of each city. Space: O(V)
        vector<int> visited(V, 0);
        int provinces = 0;

        // Iterate through every city registry entry
        for (int i = 0; i < V; i++) {
            // If the city is not yet marked as part of a province
            if (visited[i] == 0) {
                // Found a new, previously uncharted province
                provinces++;
                // Launch protocol to map the entire new territory
                dfs(adj, i, visited);
            }
        }

        return provinces;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    // TEST CASE SETUP:
    // 3 cities (0, 1, 2).
    // City 0 is connected to 2. City 1 is isolated.
    // Adjacency Matrix visual:
    //    0  1  2
    // 0 [1, 0, 1]
    // 1 [0, 1, 0]
    // 2 [1, 0, 1]
    // Expected Result: 2 provinces ({0,2} and {1})
    int V = 3;
    vector<vector<int>> adj = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };

    cout << "INITIATING PROVINCE ENUMERATION PROTOCOL..." << endl;
    cout << "Analyzing adjacency matrix dimensions: " << V << "x" << V << endl;
    
    // Execute the mission
    int result = solver.numProvinces(adj, V);

    // Report findings
    cout << "REPORT:" << endl;
    cout << "Total disconnected provinces detected: " << result << endl;
    cout << "MISSION COMPLETE." << endl;

    return 0;
}
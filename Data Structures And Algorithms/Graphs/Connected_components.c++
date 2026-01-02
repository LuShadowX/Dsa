/**
 * @file connected_components_dfs.cpp
 * @author LuShadowX
 * @brief Find all connected components in an undirected graph.
 * @problem_type: Standard Graph Problem
 * @difficulty: Medium (Rank B)
 * @tags: Graph Theory, DFS, Connected Components, Adjacency List
 * @logic: First, convert the input edge list into an adjacency list representing
 * an undirected graph. Maintain a visited array. Iterate through all vertices
 * from 0 to V-1. If a vertex is unvisited, it indicates the start of a new
 * connected component. Start a DFS from this vertex to collect all reachable
 * nodes into a temporary vector representing that component, then add it to the final result.
 */
/**
 * MISSION: Component Identification Protocol
 * RANK: B (Standard Structural Analysis)
 * DEPARTMENT: Graph Theory
 * CHALLENGE:
 * Given the number of vertices V and a list of undirected edges, identify and
 * return all disjoint connected components within the network. Each component
 * should be represented as a list of its constituent vertex IDs.
 * CONSTRAINTS:
 * - Time Complexity: O(V + E) - We visit every vertex and iterate over every edge once.
 * - Space Complexity: O(V + E) - For storing the adjacency list and recursion stack/visited array.
 * - 0-based indexing used for vertices.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /**
     * THE COMPONENT HARVESTER (Recursive DFS Helper)
     * Explores the graph to collect all nodes belonging to the current component.
     * @param adj The adjacency list.
     * @param node The current node being explored.
     * @param visit Reference to the visited status vector.
     * @param parts Reference to the vector collecting nodes for the current component.
     */
    void dfs(vector<vector<int>>& adj, int node, vector<int>& visit, vector<int>& parts) {
        // Mark the current node as visited so it's not processed again
        visit[node] = 1;
        // Add node to the current component collection
        parts.push_back(node);

        // Traverse all immediate neighbors
        for (auto neighbor : adj[node]) {
            // If neighbor is previously undiscovered, recurse
            if (visit[neighbor] == 0) {
                dfs(adj, neighbor, visit, parts);
            }
        }
    }

public:
    /**
     * Retrieves all connected components of the graph.
     * @param V Number of vertices.
     * @param edges Vector of undirected edges.
     * @return A vector of vectors, where each inner vector is a connected component.
     */
    vector<vector<int>> getComponents(int V, vector<vector<int>>& edges) {
        // 1. Infrastructure Setup
        vector<vector<int>> adj(V);      // Adjacency list
        vector<int> visit(V, 0);         // Track visited status (Space: O(V))
        vector<vector<int>> result;      // Final container for all components

        // 2. Build Adjacency List (Undirected Graph)
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u); // Add reciprocal connection
        }

        // 3. Component Identification Loop
        for (int i = 0; i < V; i++) {
            // If vertex 'i' has not been assigned to a component yet
            if (visit[i] == 0) {
                vector<int> componentParts; // Temporary container for the new component
                // Launch DFS to collect all nodes in this component
                dfs(adj, i, visit, componentParts);
                // Add the completed component to the final result
                result.push_back(componentParts);
            }
        }

        return result;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    // TEST CASE SETUP:
    // 5 vertices (0 to 4).
    // Component 1: 0-1, 1-4 (Nodes {0, 1, 4})
    // Component 2: 2-3 (Nodes {2, 3})
    int V = 5;
    vector<vector<int>> edges = {
        {0, 1},
        {1, 4},
        {2, 3}
    };

    cout << "INITIATING COMPONENT IDENTIFICATION PROTOCOL..." << endl;
    cout << "Vertices: " << V << ", Edges identified: " << edges.size() << endl;
    
    // Execute the mission
    vector<vector<int>> components = solver.getComponents(V, edges);

    // Report findings
    cout << "REPORT:" << endl;
    cout << "Total connected components detected: " << components.size() << endl;
    cout << "Component details:" << endl;
    for (int i = 0; i < components.size(); ++i) {
        cout << "  Component " << i + 1 << ": [ ";
        for (size_t j = 0; j < components[i].size(); ++j) {
            cout << components[i][j] << (j == components[i].size() - 1 ? "" : ", ");
        }
        cout << " ]" << endl;
    }
    cout << "MISSION COMPLETE." << endl;

    return 0;
}
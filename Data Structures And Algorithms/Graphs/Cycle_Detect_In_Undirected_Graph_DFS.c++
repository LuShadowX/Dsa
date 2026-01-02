/**
 * @file cycle_detection_dfs.cpp
 * @author LuShadowX
 * @brief Detect a cycle in an undirected graph using DFS.
 * @problem_type: Standard Graph Problem
 * @difficulty: Medium (Rank B)
 * @tags: Graph Theory, DFS, Cycle Detection, Undirected Graph, Recursion
 * @logic: Use recursive DFS to traverse the graph. Maintain a visited array.
 * Crucially, pass the 'parent' (the node from which the current node was reached)
 * down the recursion stack. If DFS encounters a neighbor that is already visited
 * AND is NOT the immediate parent, it confirms the existence of a cycle.
 */
/**
 * MISSION: Cycle Detection Protocol (DFS Variant)
 * RANK: B (Structural Integrity Analysis)
 * DEPARTMENT: Graph Theory & Recursive Algorithms
 * CHALLENGE:
 * Given an undirected graph, determine if it contains any cycles. A cycle exists
 * if you can start at a vertex and return to it by traversing edges without
 * using the same edge twice.
 * CONSTRAINTS:
 * - Time Complexity: O(V + E) - Standard DFS traversal.
 * - Space Complexity: O(V + E) - Adjacency list plus O(V) for recursion stack and visited array.
 * - The graph may contain multiple disconnected components.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /**
     * THE CYCLE HUNTER (Recursive DFS Helper)
     * Explores the graph recursively to find a cycle in the current component.
     * @param adj The adjacency list.
     * @param visit Reference to the visited status vector.
     * @param node The current node being explored.
     * @param src The parent node from which we arrived at current 'node'. (-1 if start of DFS).
     * @return true if a cycle is found deep in the recursion tree, false otherwise.
     */
    bool dfs(vector<vector<int>>& adj, vector<int>& visit, int node, int src) {
        // Mark current node as visited
        visit[node] = 1;
        
        // Traverse all neighbors
        for (auto it : adj[node]) {
            // Case 1: Neighbor is unvisited. Recurse deeper.
            if (visit[it] == 0) {
                // If the recursive call finds a cycle, propagate true upwards.
                // Current 'node' becomes the 'src' (parent) for the neighbor 'it'.
                if (dfs(adj, visit, it, node)) return true;
            }
            // Case 2: Neighbor is visited AND it's NOT the parent (src).
            // This is the definition of a cycle in an undirected graph.
            else if (it != src) {
                return true; // Cycle detected
            }
            // Case 3 (Implicit): Neighbor is visited AND it IS the parent. Ignore.
        }
        return false;
    }

public:
    /**
     * Detects if an undirected graph contains a cycle.
     * @param V Number of vertices.
     * @param edges Vector of undirected edges.
     * @return true if the graph has a cycle, false otherwise.
     */
    bool isCycle(int V, vector<vector<int>>& edges) {
        // 1. Build Adjacency List
        vector<vector<int>> adj(V);
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u); // Undirected graph
        }

        // 2. Initialize Visited Array (Space: O(V))
        vector<int> visit(V, 0);

        // 3. Component Iteration Loop
        // Handle disconnected graphs by checking every node.
        for (int i = 0; i < V; i++) {
            // If a node has not been visited, start DFS from it.
            if (visit[i] == 0) {
                // Pass -1 as the parent for the root of the DFS tree.
                if (dfs(adj, visit, i, -1)) return true;
            }
        }

        // If no cycle is found after checking all components.
        return false;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    cout << "INITIATING CYCLE DETECTION PROTOCOL (DFS)..." << endl;

    // Test Case 1: A graph with a cycle: 0-1, 1-2, 2-0
    int V_cycle = 3;
    vector<vector<int>> edges_cycle = {
        {0, 1}, {1, 2}, {2, 0}
    };
    cout << "\nTesting Graph 1 (with cycle):" << endl;
    bool hasCycle1 = solver.isCycle(V_cycle, edges_cycle);
    cout << "REPORT: Cycle detected? " << (hasCycle1 ? "YES (Positive)" : "NO (Negative)") << endl;

    // Test Case 2: A graph without a cycle (a tree): 0-1, 1-2, 0-3
    int V_no_cycle = 4;
    vector<vector<int>> edges_no_cycle = {
        {0, 1}, {1, 2}, {0, 3}
    };
    cout << "\nTesting Graph 2 (without cycle):" << endl;
    bool hasCycle2 = solver.isCycle(V_no_cycle, edges_no_cycle);
    cout << "REPORT: Cycle detected? " << (hasCycle2 ? "YES (Positive)" : "NO (Negative)") << endl;
    
    cout << "\nMISSION COMPLETE." << endl;

    return 0;
}
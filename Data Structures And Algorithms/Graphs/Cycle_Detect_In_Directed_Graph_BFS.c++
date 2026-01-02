/**
 * @file cycle_detection_directed_dfs.cpp
 * @author LuShadowX
 * @brief Detect a cycle in a DIRECTED graph using DFS.
 * @problem_type: Standard Graph Problem
 * @difficulty: Medium (Rank B)
 * @tags: Graph Theory, DFS, Cycle Detection, Directed Graph, Recursion
 * @logic: In a directed graph, a cycle exists if there is a back-edge to a node
 * that is currently in the active recursion stack. We use two boolean arrays:
 * 1. 'visited[]' to keep track of all visited nodes to avoid redundant processing.
 * 2. 'pathVisited[]' to keep track of nodes currently in the recursion stack.
 * During DFS, if we encounter a neighbor that is already 'pathVisited', it means
 * we found a back-edge, confirming a cycle. Crucially, 'pathVisited[node]' is reset
 * to false (backtracking) when returning from the recursive calls for that node.
 */
/**
 * MISSION: Cycle Detection Protocol (Directed DFS Variant)
 * RANK: B (Structural Integrity Analysis)
 * DEPARTMENT: Graph Theory & Recursive Algorithms
 * CHALLENGE:
 * Given a DIRECTED graph, determine if it contains any cycles. A cycle exists
 * if you can start at a vertex and return to it by traversing directed edges.
 * CONSTRAINTS:
 * - Time Complexity: O(V + E) - Standard DFS traversal.
 * - Space Complexity: O(V + E) - Adjacency list plus O(V) for recursion stack and visited arrays.
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
     * @param node The current node being explored.
     * @param visit Reference to the global visited status vector.
     * @param pathvisit Reference to the recursion stack status vector.
     * @return true if a back-edge (cycle) is found, false otherwise.
     */
    bool dfs(vector<vector<int>>& adj, int node, vector<int>& visit, vector<int>& pathvisit) {
        // Mark current node as visited globally and added to current path
        visit[node] = 1;
        pathvisit[node] = 1;
        
        // Traverse all outgoing neighbors
        for (auto neighbor : adj[node]) {
            // Case 1: Neighbor is completely unvisited. Recurse deeper.
            if (visit[neighbor] == 0) {
                // If the recursive call finds a cycle, propagate true upwards.
                if (dfs(adj, neighbor, visit, pathvisit)) return true;
            }
            // Case 2: Neighbor is already in the current recursion stack (pathVisited).
            // This indicates a back-edge, hence a cycle.
            else if (pathvisit[neighbor] == 1) {
                return true; // Cycle detected
            }
            // Case 3 (Implicit): Neighbor is visited but NOT in the current path.
            // This is a cross-edge or forward-edge to an already processed part of the graph.
            // No cycle here, ignore.
        }
        
        // BACKTRACK: Remove current node from the active recursion path stack
        // before returning to the caller.
        pathvisit[node] = 0;
        return false;
    }

public:
    /**
     * Detects if a directed graph contains a cycle.
     * @param V Number of vertices.
     * @param edges Vector of directed edges (u -> v).
     * @return true if the graph has a cycle, false otherwise.
     */
    bool isCyclic(int V, vector<vector<int>> &edges) {
        // 1. Infrastructure Setup
        vector<vector<int>> adj(V);      // Adjacency list
        vector<int> visit(V, 0);         // Global visited array (Space: O(V))
        vector<int> pathvisit(V, 0);     // Recursion stack array (Space: O(V))

        // 2. Build Adjacency List (Directed Graph)
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            adj[u].push_back(v); // Directed edge u -> v
        }

        // 3. Component Iteration Loop
        // Handle disconnected graphs by checking every unvisited node.
        for (int i = 0; i < V; i++) {
            if (visit[i] == 0) {
                // Start DFS from unvisited node. If a cycle is found, return true immediately.
                if (dfs(adj, i, visit, pathvisit)) {
                    return true;
                }
            }
        }

        // If no cycle is found after checking all components.
        return false;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    cout << "INITIATING DIRECTED CYCLE DETECTION PROTOCOL (DFS)..." << endl;

    // Test Case 1: A graph with a cycle: 0->1, 1->2, 2->0
    int V_cycle = 3;
    vector<vector<int>> edges_cycle = {
        {0, 1}, {1, 2}, {2, 0}
    };
    cout << "\nTesting Graph 1 (with cycle): 0->1->2->0" << endl;
    bool hasCycle1 = solver.isCyclic(V_cycle, edges_cycle);
    cout << "REPORT: Cycle detected? " << (hasCycle1 ? "YES (Positive)" : "NO (Negative)") << endl;

    // Test Case 2: A graph without a cycle (DAG): 0->1, 0->2, 1->3, 2->3 (Diamond shape)
    int V_no_cycle = 4;
    vector<vector<int>> edges_no_cycle = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3}
    };
    cout << "\nTesting Graph 2 (without cycle - 'Diamond'): 0->1->3, 0->2->3" << endl;
    bool hasCycle2 = solver.isCyclic(V_no_cycle, edges_no_cycle);
    cout << "REPORT: Cycle detected? " << (hasCycle2 ? "YES (Positive)" : "NO (Negative)") << endl;
    
    cout << "\nMISSION COMPLETE." << endl;

    return 0;
}
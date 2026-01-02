/**
 * @file cycle_detection_bfs.cpp
 * @author LuShadowX
 * @brief Detect a cycle in an undirected graph using BFS.
 * @problem_type: Standard Graph Problem
 * @difficulty: Medium (Rank B)
 * @tags: Graph Theory, BFS, Cycle Detection, Undirected Graph
 * @logic: Use BFS to traverse the graph. We maintain a visited array to track
 * visited nodes. The crucial part for undirected graphs is to keep track of the
 * 'parent' of the current node (the node from which we arrived). If we encounter
 * a neighbor that is already visited AND is NOT the immediate parent, it implies
 * there is another path to reach that neighbor, confirming the existence of a cycle.
 * The queue stores pairs of {current_node, parent_node}.
 */
/**
 * MISSION: Cycle Detection Protocol (BFS Variant)
 * RANK: B (Structural Integrity Analysis)
 * DEPARTMENT: Graph Theory & Traversal Algorithms
 * CHALLENGE:
 * Given an undirected graph, determine if it contains any cycles. A cycle exists
 * if you can start at a vertex and return to it by traversing edges without
 * using the same edge twice.
 * CONSTRAINTS:
 * - Time Complexity: O(V + E) - Standard BFS traversal.
 * - Space Complexity: O(V + E) - Adjacency list plus O(V) for queue and visited array.
 * - The graph may contain multiple disconnected components.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /**
     * THE CYCLE HUNTER (BFS Helper Function)
     * Performs BFS to detect a cycle within a single connected component.
     * @param adj The adjacency list.
     * @param visit Reference to the visited status vector.
     * @param node The starting node for this BFS traversal.
     * @return true if a cycle is found, false otherwise.
     */
    bool bfs(vector<vector<int>>& adj, vector<int>& visit, int node) {
        // Queue stores {current_node, parent_node}
        queue<pair<int, int>> q;
        
        // Initialize BFS from the starting node.
        // Use -1 as the parent for the root node.
        visit[node] = 1;
        q.push({node, -1});

        while (!q.empty()) {
            int currNode = q.front().first;
            int parent = q.front().second;
            q.pop();

            // Traverse all neighbors of the current node
            for (auto neighbor : adj[currNode]) {
                // Case 1: Neighbor is unvisited.
                if (visit[neighbor] == 0) {
                    visit[neighbor] = 1;
                    // Push neighbor to queue with current node as its parent
                    q.push({neighbor, currNode});
                }
                // Case 2: Neighbor is visited AND it's NOT the parent.
                // This is the definition of a cycle in an undirected graph.
                else if (visit[neighbor] == 1 && neighbor != parent) {
                    return true; // Cycle detected
                }
                // Case 3 (Implicit): Neighbor is visited AND it IS the parent.
                // This is just the path we came from, ignore it.
            }
        }
        // No cycle found in this component
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
            // If a node has not been visited, start BFS from it.
            if (visit[i] == 0) {
                // If BFS finds a cycle in this component, return true immediately.
                if (bfs(adj, visit, i)) {
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

    // TEST CASE SETUP:
    // A graph with a cycle: 0-1, 1-2, 2-0
    int V_cycle = 3;
    vector<vector<int>> edges_cycle = {
        {0, 1}, {1, 2}, {2, 0}
    };

    // A graph without a cycle (a tree): 0-1, 1-2
    int V_no_cycle = 3;
    vector<vector<int>> edges_no_cycle = {
        {0, 1}, {1, 2}
    };

    cout << "INITIATING CYCLE DETECTION PROTOCOL (BFS)..." << endl;

    // Test Case 1
    cout << "\nTesting Graph 1 (with cycle):" << endl;
    bool hasCycle1 = solver.isCycle(V_cycle, edges_cycle);
    cout << "REPORT: Cycle detected? " << (hasCycle1 ? "YES (Positive)" : "NO (Negative)") << endl;

    // Test Case 2
    cout << "\nTesting Graph 2 (without cycle):" << endl;
    bool hasCycle2 = solver.isCycle(V_no_cycle, edges_no_cycle);
    cout << "REPORT: Cycle detected? " << (hasCycle2 ? "YES (Positive)" : "NO (Negative)") << endl;
    
    cout << "\nMISSION COMPLETE." << endl;

    return 0;
}
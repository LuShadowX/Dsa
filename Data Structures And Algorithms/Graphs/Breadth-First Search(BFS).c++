/**
 * @file bfs_graph.cpp
 * @author LuShadowX
 * @brief Breadth-First Search (BFS) traversal of a graph.
 * @problem_link: https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/1
 * @difficulty: Easy (Rank B)
 * @tags: Graph Theory, BFS, Queue, Level-Order Traversal
 * @logic: Utilize a Queue data structure to explore nodes layer by layer.
 * Maintain a visited array to avoid cycles and redundant processing.
 */
/**
 * MISSION: BFS Traversal of Graph
 * RANK: B (Fundamental Search Protocol)
 * DEPARTMENT: Graph Theory & Traversal Algorithms
 * CHALLENGE:
 * Systematically explore a directed graph starting from a given source node (Node 0),
 * visiting all reachable vertices level by level, similar to ripples spreading in a pond.
 * CONSTRAINTS:
 * - Time Complexity: O(V + E) where V is vertices, E is edges.
 * - Space Complexity: O(V) for queue and visited array.
 * - The graph is 0-indexed.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * THE LEVEL-ORDER EXPLORER (BFS)
     * Executes BFS on a graph given its adjacency list.
     * @param adj The adjacency list representation of the graph.
     * @return A vector containing the nodes in BFS traversal order.
     */
    vector<int> bfs(vector<vector<int>> &adj) {
        int V = adj.size(); // Number of vertices
        vector<int> bfsOrder; // Stores the final traversal sequence
        
        // Visited array initialized to 0 (false) to handle cycles.
        // Space: O(V)
        vector<int> visited(V, 0);
        
        // Queue required for FIFO operations in BFS.
        // Space: O(V)
        queue<int> q;

        // --- Start Protocol: Begin traversal from Node 0 ---
        if (V > 0) {
            visited[0] = 1; // Mark start node as visited immediately
            q.push(0);
        }

        // --- BFS Exploration Loop ---
        while(!q.empty()){
            // 1. Dequeue current node and process it
            int node = q.front();
            q.pop();
            bfsOrder.push_back(node);

            // 2. Iterate through all adjacent neighbors
            for(auto neighbor : adj[node]){
                // If neighbor is unvisited, mark and enqueue
                if(visited[neighbor] == 0){
                    visited[neighbor] = 1; // Vital: Mark visited BEFORE pushing
                    q.push(neighbor);
                }
            }
        }
        
        return bfsOrder;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    // TEST CASE SETUP:
    // Constructing a sample directed graph with 5 vertices (0 to 4)
    // Edges: 0->1, 0->2, 0->3, 2->4
    int V = 5;
    vector<vector<int>> adj(V);

    // Building the adjacency list
    adj[0] = {1, 2, 3};
    adj[1] = {};         // Node 1 has no outgoing edges
    adj[2] = {4};        // Node 2 connects to 4
    adj[3] = {};         // Node 3 has no outgoing edges
    adj[4] = {};         // Node 4 has no outgoing edges

    cout << "INITIATING BFS PROTOCOL FROM NODE 0..." << endl;
    
    // Execute the mission
    vector<int> result = solver.bfs(adj);

    // Report findings
    cout << "TRAVERSAL SEQUENCE DETECTED: [ ";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : ", ");
    }
    cout << " ]" << endl;

    return 0;
}
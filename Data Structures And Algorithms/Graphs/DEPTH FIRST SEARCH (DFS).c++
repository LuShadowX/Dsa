/**
 * @file dfs_graph.cpp
 * @author LuShadowX
 * @brief Depth-First Search (DFS) traversal of a graph.
 * @problem_link: https://www.geeksforgeeks.org/problems/depth-first-traversal-of-a-graph/1
 * @difficulty: Easy (Rank B)
 * @tags: Graph Theory, DFS, Recursion, Backtracking
 * @logic: Explore as deep as possible along each branch before backtracking.
 * Utilize recursion (implicitly using the system stack) to manage the traversal
 * path and a visited array to prevent cycles and redundant processing.
 */
/**
 * MISSION: DFS Traversal of Graph
 * RANK: B (Fundamental Search Protocol)
 * DEPARTMENT: Graph Theory & Recursive Algorithms
 * CHALLENGE:
 * Systematically explore a directed graph starting from a given source node (Node 0),
 * diving deep into one path before backtracking to explore other possibilities.
 * CONSTRAINTS:
 * - Time Complexity: O(V + E) where V is vertices, E is edges.
 * - Space Complexity: O(V) for the visited array and the recursion stack.
 * - The graph is 0-indexed and assumed to be connected from Node 0.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /**
     * THE DEPTH DIVER (Recursive Helper Function)
     * Recursively explores the graph in a depth-first manner.
     * @param node The current node being explored.
     * @param visited Reference to the visited status vector.
     * @param result Reference to the vector storing the DFS traversal order.
     * @param adj Reference to the graph's adjacency list.
     */
    void dfs(int node, vector<int>& visited, vector<int>& result, vector<vector<int>>& adj){
        // 1. Mark current node as visited and add to result
        visited[node] = 1;
        result.push_back(node);

        // 2. Explore unvisited neighbors recursively
        for(auto neighbor : adj[node]){
            if(visited[neighbor] == 0){
                // Recursive call: dive deeper from this neighbor
                dfs(neighbor, visited, result, adj);
            }
        }
        // Implicit backtracking occurs when the loop finishes or no unvisited neighbors remain
    }

public:
    /**
     * Initiates the DFS traversal.
     * @param adj The adjacency list representation of the graph.
     * @return A vector containing the nodes in DFS traversal order.
     */
    vector<int> dfs(vector<vector<int>>& adj) {
        int V = adj.size(); // Number of vertices
        
        // Visited array initialized to 0 (false) to handle cycles.
        // Space: O(V)
        vector<int> visited(V, 0);
        
        // Vector to store the final DFS order.
        vector<int> result;
        
        // --- Start Protocol: Begin traversal from Node 0 ---
        if (V > 0) {
            // Call the recursive helper function
            dfs(0, visited, result, adj);
        }
        
        return result;
    }
};

// ================= MAIN PROTOCOL (Testing) =================

int main() {
    Solution solver;

    // TEST CASE SETUP:
    // Constructing a sample directed graph with 5 vertices (0 to 4)
    // This graph has multiple paths to demonstrate the "depth-first" nature.
    // Edges: 0->1, 0->2, 0->3, 2->4
    int V = 5;
    vector<vector<int>> adj(V);

    // Building the adjacency list
    adj[0] = {1, 2, 3};
    adj[1] = {};         // Node 1 is a leaf in this path
    adj[2] = {4};        // Node 2 connects to 4
    adj[3] = {};         // Node 3 is a leaf in this path
    adj[4] = {};         // Node 4 is a leaf in this path

    cout << "INITIATING DFS PROTOCOL FROM NODE 0..." << endl;
    
    // Execute the mission
    vector<int> result = solver.dfs(adj);

    // Report findings
    cout << "TRAVERSAL SEQUENCE DETECTED: [ ";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : ", ");
    }
    cout << " ]" << endl;
    
    // Expected Output for this graph (one possible valid DFS order):
    // TRAVERSAL SEQUENCE DETECTED: [ 0, 1, 2, 4, 3 ] 
    // (Note: Order of neighbors can vary, e.g., 0, 3, 2, 4, 1 is also valid)

    return 0;
}
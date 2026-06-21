#include<bits/stdc++.h>
using namespace std;

int lowestCommonAncestor(int u, int v, int node, vector<vector<int>>& adjList, vector<bool>& visited) {
    if((node == -1) || (node == u) || (node == v)) {
        return node;
    }
    visited[node] = true;
    int lca = -1;
    int count = 0;
    for(int adj : adjList[node]) {
        if(!visited[adj]) {
            int res = lowestCommonAncestor(u, v, adj, adjList, visited);
            if(res != -1) {
                count++;
                lca = res;
            }
        }
    }
    if(count == 2) {
        return node;
    }
    return lca;
} 

void addEdge(int u, int v, vector<vector<int>>& adjList) {
    adjList[u - 1].push_back(v - 1);
    adjList[v - 1].push_back(u - 1);
}

int main() {
    const int N = 8;
    vector<vector<int>> adjList(N);
    addEdge(1, 2, adjList);
    addEdge(1, 3, adjList);
    addEdge(2, 4, adjList);
    addEdge(2, 5, adjList);
    addEdge(2, 6, adjList);
    addEdge(3, 7, adjList);
    addEdge(3, 8, adjList);
    vector<bool> visited(N, false);
    
    // Convert 1-based inputs to 0-based for the function, then add 1 to get 1-based output
    cout << "LCA(6, 7) : " << lowestCommonAncestor(5, 6, 0, adjList, visited) << endl;
    
    // Reset visited array for the next query
    fill(visited.begin(), visited.end(), false);
    cout << "LCA(6, 4) : " << lowestCommonAncestor(5, 3, 0, adjList, visited) << endl;
    
    return 0;
}

/*
        0
      /   \
     1     2
   / | \  / \
  3  4  5 6   7

LCA(5,6) : 0
LCA(5,3) : 1
*/
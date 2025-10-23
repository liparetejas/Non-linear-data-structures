/* Shorted path in DAG by using Topological Sort
*/
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

void dfs(int currNode, vector<vector<pair<int, int>>>& adjList,
			vector<int>& visited, stack<int>& topoSortOrder) {
	visited[currNode] = 1;
	for(pair<int, int> adjNodePair : adjList[currNode]) {
		if(!visited[adjNodePair.first]) {
			dfs(adjNodePair.first, adjList, visited, topoSortOrder);
		}
	}
	topoSortOrder.push(currNode);
}

// Time: O(n + e) Space: O(n)
vector<int> shortestPathInDAG(int n, int source,
								vector<vector<pair<int, int>>>& adjList) {
	stack<int> topoSortOrder;
	vector<int> visited(n, 0);
	for(int node=0; node<n; node++) {
		if(!visited[node]) {
			dfs(node, adjList, visited, topoSortOrder);
		}
	}
	vector<int> shortestPath(7, INT_MAX);
	shortestPath[source] = 0;
	while(!topoSortOrder.empty()) {
		int currNode = topoSortOrder.top();
		int currDist = shortestPath[currNode];
		topoSortOrder.pop();
		for(pair<int, int> adjNodePair : adjList[currNode]) {
			int adjNode = adjNodePair.first;
			int adjNodeDist = adjNodePair.second;
			shortestPath[adjNode] = min(shortestPath[adjNode],
										adjNodeDist + currDist);
		}
	}
	return shortestPath;
}

int main()
{
	/* ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL); */
	int n = 0;
    int e = 0;
    cin >> n >> e;
	vector<vector<pair<int, int>>> adjList(n); 
	for(int i = 0; i<e; i++) {
	    int u, v, w; 
	    cin >> u >> v >> w;
	    adjList[u].push_back({v, w}); 
	}
	vector<int> shortestPath = shortestPathInDAG(n, 6, adjList);
	for(int node=0; node<n; node++) {
		cout << "6 -> " << node << " : " << shortestPath[node] << endl;
	}
	return 0;	
}

/*
Input:
7 8
6 4 2
6 5 3
5 4 1
4 0 3
4 2 1
2 3 3
0 1 2
1 3 1

Output:
6 -> 0 : 5
6 -> 1 : 7
6 -> 2 : 3
6 -> 3 : 6
6 -> 4 : 2
6 -> 5 : 3
6 -> 6 : 0
*/
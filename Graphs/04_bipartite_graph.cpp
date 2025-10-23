/* 
Bipartite graph:
	Let C be the minimum number of colors with which you can color
	all the nodes of the graph such that no two adjacent nodes are
	of same colors.
	If C is 2, it's called as Bipartite graph
	Some key points to remember:
	1. Linear graph with no cycles are always Bipartite graphs
	2. Any graph with even cycle length is also Bipartite graph
	Thus, any graph with odd cycle length is always non-bipartite
	We check if the length of cycle is odd to check if the graph is
	bipartite.
 */
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

// Time: O(n + e) Space: O(n)
bool isBipartiteBfs(int n, vector<vector<int>>& adjList) {
	vector<int> colors(n+1, -1);
	queue<int> q; // current
	q.push(1);
	colors[1] = 0;
	while(!q.empty()) {
		int currNode = q.front();
		q.pop();
		for(int adjNode : adjList[currNode]) {
			if(colors[adjNode] == -1) {
				colors[adjNode] = !colors[currNode];
				q.push(adjNode);
			} else if(colors[adjNode] == colors[currNode]) {
				return false;
			}
		}
	}
	return true;
}

bool dfsForBipartite(int node, vector<int>& colors, vector<vector<int>>& adjList) {
	for(int adjNode : adjList[node]) {
		if(colors[adjNode] == -1) {
			colors[adjNode] = !colors[node];
			if(dfsForBipartite(adjNode, colors, adjList) == false) {
				return false;
			}
		} else if(colors[adjNode] == colors[node]) {
			return false;
		}
	}
	return true;
}

// Time: O(n + e) Space: O(n)
bool isBipartiteDfs(int n, vector<vector<int>>& adjList) {
	vector<int> colors(n+1, -1);
	colors[1] = 0;
	if(dfsForBipartite(1, colors, adjList) == false) {
		return false;
	}
	return true;
}

int main()
{
	/* ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL); */
	int n = 0;
    int e = 0;
    cin >> n >> e;
	vector<vector<int>> adjList(n+1); 
	for(int i = 0; i<e; i++) {
	    int u, v; 
	    cin >> u >> v;
	    adjList[u].push_back(v);
	    adjList[v].push_back(u); 
	}
	if(isBipartiteBfs(n, adjList)) {
		cout << "Graph is Bipartite" << endl;
	} else {
		cout << "Graph is not Bipartite" << endl;
	}
	if(isBipartiteDfs(n, adjList)) {
		cout << "Graph is Bipartite" << endl;
	} else {
		cout << "Graph is not Bipartite" << endl;
	}
	
}

/*
Input:
8 8
1 2
2 3
2 6
3 4
4 5
5 6
4 7
7 8

Output:
Graph is not Bipartite
Graph is not Bipartite

Input:
8 8
1 2
2 3
2 6
3 4
5 6
5 7
4 7
7 8

Output:
Graph is Bipartite
Graph is Bipartite
*/
/* Strongly connected components in a DAG */
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

void getFinishingTimesDfs(int currNode, vector<int>& visited,
							stack<int>& finishingTimes,
							vector<vector<int>>& adjList) {
	visited[currNode] = 1;
	for(int adjNode : adjList[currNode]) {
		if(!visited[adjNode]) {
			getFinishingTimesDfs(adjNode, visited, finishingTimes, adjList);
		}
	}
	finishingTimes.push(currNode);					
}

void sccDfs(int currNode, vector<int>& visited,
					vector<int>& scc,
					vector<vector<int>>& adjList) {
	visited[currNode] = 1;
	scc.push_back(currNode);
	for(int adjNode : adjList[currNode]) {
		if(!visited[adjNode]) {
			sccDfs(adjNode, visited, scc, adjList);
		}
	}				
}

// Time: O(V+E) | Space: O(V)
vector<vector<int>> stronglyConnectedComponents(
								int n, vector<vector<int>>& adjList) {
	vector<vector<int>> sccs;
	// O(V+E)
	// DFS with G_R
	vector<vector<int>> reversedAdjList(n);
	for(int node=0; node<n; node++) {
		for(int adjNode : adjList[node]) {
			reversedAdjList[adjNode].push_back(node);
		}
	}
	// O(V+E)
	stack<int> finishingTimes;
	vector<int> visited(n, 0);
	for(int node=0; node<n; node++) {
		if(!visited[node]) {
			getFinishingTimesDfs(node, visited, finishingTimes,
									reversedAdjList);
		}
	}
	// O(V+E)
	// DFS with G in decreasing order of finish time found in step 1
	memset(&visited[0], 0, sizeof(int) * n);
	while(!finishingTimes.empty()) {
		int currNode = finishingTimes.top();
		finishingTimes.pop();
		if(!visited[currNode]) {
			vector<int> scc;
			sccDfs(currNode, visited, scc, adjList);
			sccs.push_back(scc);
		}
	}
	return sccs;
}

int main()
{
	int n, e;
	cin >> n >> e;
	vector<vector<int>> adjList(n);
	for(int i=0; i<e; i++) {
		int u, v;
		cin >> u >> v;
		adjList[u].push_back(v);
	}
	vector<vector<int>> sccs = stronglyConnectedComponents(n, adjList);
	cout << "SCC size: " << sccs.size() << endl;
	for(vector<int> scc : sccs) {
		for(int node : scc) {
			cout << node << " ";
		}
		cout << endl;
	}
	return 0;	
}

/*
Input:
8 10
0 1
1 2
2 0
2 3
3 4
4 7
4 5
5 6
6 4
6 7

Outut:
SCC size: 4
7 
4 5 6 
3 
0 1 2 
*/
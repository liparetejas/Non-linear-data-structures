/* Implementation of basic traversal techniques in graphs. BFS and DFS*/
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

// Time: O(n) Space: O(n)
void bfs(ll n, vector<vector<ll>> adjList) {
	vector<bool> visited(n+1, false);
	vector<ll> bfs_vect;
	ll components = 0;
	for(ll i = 1; i<=n; i++) {
		if(!visited[i]) {
			queue<ll> q;
			q.push(i);
			visited[i] = true;
			while(!q.empty()) {
				ll node = q.front();
				q.pop();
				bfs_vect.push_back(node);
				visited[node] = true;
				for(ll j : adjList[node]) {
					if(!visited[j]) {
						q.push(j);
						visited[j] = true;
					}
				}
			}
			components++;
		}
	}
	cout << "No. of components in the graph: " << components << endl;
	cout << "BFS: ";
	for(ll node : bfs_vect) {
		cout << node << " ";
	}
	cout << endl;
}


// Time: O(n) Space: O(n)
void dfs(ll n, vector<bool>& visited, vector<vector<ll>> adjList, vector<ll>& dfs_vect) {
	dfs_vect.push_back(n);
	visited[n] = true;
	for(ll node : adjList[n]) {
		if(!visited[node]) {
			dfs(node, visited, adjList, dfs_vect);
		}
	}
}

void dfs_components(ll n, vector<vector<ll>> adjList) {
	vector<bool> visited(n+1, false);
	vector<ll> dfs_vect;
	ll components = 0;
	for(ll i=1; i<=n; i++) {
		if(!visited[i]) {
			dfs(i, visited, adjList, dfs_vect);
			components++;
		}
	}
	cout << "No. of components in the graph: " << components << endl;
	cout << "DFS: ";
	for(ll node : dfs_vect) {
		cout << node << " ";
	}
	cout << endl;
}

int main()
{
	/* ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL); */
	ll n = 0;
    ll e = 0;
    cin >> n >> e;
    // declare the adjacency list 
	vector<vector<ll>> adjList(n+1); 
	
	// take edges as input 
	for(ll i = 0; i<e; i++) {
	    ll u, v; 
	    cin >> u >> v;
	    adjList[u].push_back(v); // For weighted graph, adjList[u].push_back({v, w});
	    adjList[v].push_back(u); 
	}
	/* for(vector<ll> subV : adjList) {
		for(ll node : subV) {
			cout << node << " ";
		}
		cout << endl;
	} */
	bfs(n, adjList);
	dfs_components(n, adjList);
	return 0;	
}

/*
Input:
7 6
1 2
2 3
2 7
3 5
4 6
5 7

Output:
No. of components in the graph: 2
BFS: 1 2 3 7 5 4 6
No. of components in the graph: 2
DFS: 1 2 3 5 7 4 6
*/
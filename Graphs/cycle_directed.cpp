/* Cycle detection in a directed graph using DFS & BFS algorithms */
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

// Time: O(n) Space: O(n)
bool dfs(ll curr, vector<bool>& visited, vector<bool>& path, vector<vector<ll>>& adjList) {
	visited[curr] = 1;
	path[curr] = 1;
	for(ll adj : adjList[curr]) {
		if(!visited[adj]) {
			if(dfs(adj, visited, path, adjList)) {
				return true;
			}
		}
		else if(path[adj]) {
			return true;
		}
	}
	path[curr] = 0;
	return false;
}

bool detectCycleDFS(ll n, vector<vector<ll>>& adjList) {
	vector<bool> visited(n+1, 0);
	vector<bool> path(n+1, 0);
	for(ll i = 1; i <= n; i++) {
		if(!visited[i]) {
			if(dfs(i, visited, path, adjList)) {
				return true;
			}
		}
	}
	return false;
}

bool detectCycleBFS(ll n, vector<vector<ll>>& adjList) {
	vector<int> indegree(n+1, 0);
	vector<int> topoOrder;
    for(int i = 1; i <= n; i++) {
        for(int adj : adjList[i]) {
            indegree[adj]++;
        }
    }
    queue<int> q;
    for(int i=1; i<=n; i++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);
        for(int adj : adjList[node]) {
            indegree[adj]--;
            if(indegree[adj] == 0) {
                q.push(adj);
            }
        }
    }
	return topoOrder.size() < n;
}

int main()
{
	/* ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL); */
	ll n = 0;
    ll e = 0;
    cin >> n >> e;
	vector<vector<ll>> adjList(n+1); 
	for(ll i = 0; i<e; i++) {
	    ll u, v; 
	    cin >> u >> v;
	    adjList[u].push_back(v); 
	}
    if(detectCycleDFS(n, adjList)) {
        cout << "Cycle detected using DFS." << endl;
    }
    else {
        cout << "Cycle absent." << endl;
    }
	if(detectCycleBFS(n, adjList)) {
        cout << "Cycle detected using BFS." << endl;
    }
    else {
        cout << "Cycle absent." << endl;
    }
	return 0;	
}

/*
Input:
12 14
1 2
2 3
3 4
4 5
5 7
7 8
4 6
6 7
2 9
9 10
10 11
11 12
12 9
10 6

Output:
Cycle detected using DFS.
Cycle detected using BFS.
*/
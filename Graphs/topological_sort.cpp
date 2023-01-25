/* Topological sort algorithm in a directed graph using DFS.
    Topological sort is ordering of vertices such that if there is an
    edge between u and v then u appears before v in the ordering.
    It only occurs in directed acyclic graphs.
    DFS: Use stack
    BFS: Use queue (Kahn's algorithm)
*/
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

void dfs(ll curr, vector<vector<ll>>& adjList, vector<bool>& visited, stack<ll>& topoStack) {
    visited[curr] = 1;
    for(ll adj : adjList[curr]) {
        if(!visited[adj]) {
            dfs(adj, adjList, visited, topoStack);
        }
    }
    topoStack.push(curr);
}

void topological_sort(vector<vector<ll>>& adjList, ll n) {
    vector<bool> visited(n, 0);
    stack<ll> topoStack;
    //cout << "Hello World!" << endl;
    for(ll i=0; i<n; i++) {
        if(!visited[i]) {
            //cout << " " << i << endl;
            dfs(i, adjList, visited, topoStack);
        }
    }
    //cout << topoStack.size() << endl;
    cout << "Topological order using DFS: ";
    while(!topoStack.empty()) {
        cout << topoStack.top() << " ";
        topoStack.pop();
    }
}

void kahns_algo(vector<vector<ll>>& adjList, ll n) {
    cout << "Topological order using Kahn's algorithm: ";
    vector<int> indegree(n, 0);
    for(int i = 0; i < n; i++) {
        for(int adj : adjList[i]) {
            indegree[adj]++;
        }
    }
    queue<int> q;
    for(int i=0; i<n; i++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for(int adj : adjList[node]) {
            indegree[adj]--;
            if(indegree[adj] == 0) {
                q.push(adj);
            }
        }
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
	vector<vector<ll>> adjList(n); 
	for(ll i = 0; i<e; i++) {
	    ll u, v; 
	    cin >> u >> v;
	    adjList[u].push_back(v); 
	}
    //topological_sort(adjList, n);
    kahns_algo(adjList, n);
	return 0;	
}

/*
Input:
6 6
2 3
3 4
4 0
4 1
5 0
5 2

Output:
Topological order using DFS: 5 2 3 4 1 0
Topological order using Kahn's algorithm: 5 2 3 4 0 1
*/
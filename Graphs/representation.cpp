/* Creation of graph in C++ 
   This is representation of undirected graph.
   For directed graph, we need to remove the edge from v to u.
   For weighted graph, we can insert pair in adjacency list where pair.first
   represents node and pair.second represents weight of the edge.*/
/* n: Number of nodes
   e: Number of edges*/

#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

void printGraph(vector<vector<ll>> g) {
    for(vector<ll> subV : g) {
        for(ll n : subV) {
            cout << n << " ";
        }
        cout << endl;
    }
}

void adjMat(ll n, ll e) {	
	// declare the adjacency matrix 
	vector<vector<ll>> adjMat(n+1, vector<ll>(n+1, 0)); 
	
	// take edges as input 
	for(int i = 0; i<e; i++) {
	    int u, v; 
	    cin >> u >> v;
	    adjMat[u][v] = 1; 
	    adjMat[v][u] = 1; 
	}

    printGraph(adjMat);
}

void adjList(ll n, ll e) {	
	// declare the adjacency list 
	vector<vector<ll>> adjList(n+1); 
	
	// take edges as input 
	for(ll i = 0; i<e; i++) {
	    ll u, v; 
	    cin >> u >> v;
	    adjList[u].push_back(v); // For weighted graph, adjList[u].push_back({v, w});
	    adjList[v].push_back(u); 
	}

    printGraph(adjList);
}

int main()
{
	/* ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL); */
	ll n = 0;
    ll e = 0;
    cin >> n >> e;
    // Call one function at a time
    // adjMat(n, e);
    adjList(n, e);
	return 0;	
}

/*
Input: 
5 7
1 2
1 3
1 5
2 3
2 4
3 4 
3 5

AdjMat:
0 0 0 0 0 0 
0 0 1 1 0 1
0 1 0 1 1 0
0 1 1 0 1 1
0 0 1 1 0 0
0 1 0 1 0 0

AdjList:

2 3 5
1 3 4
1 2 4 5
2 3
1 3
*/

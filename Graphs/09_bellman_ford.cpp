/* Dijkstra fails on negative cycle. Bellman ford algorithm helps in detecting negative cycles. 
   It only works on a directed graph. Finds the shortest path. */
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

/* Relaxation rule:
    dist[u] + wt < dist[v] then:
        dist[v] = dist[u] + wt*/

// Time: V.E
void bellmanFord(ll src, vector<vector<ll>>& edges, ll n) {
    vector<ll> dist(n, LLONG_MAX);
    dist[src] = 0;
    for(ll i=0; i<n-1; i++) {
        for(auto edge : edges) {
            ll u = edge[0];
            ll v = edge[1];
            ll w = edge[2];
            if(dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    for(auto edge : edges) {
        ll u = edge[0];
        ll v = edge[1];
        ll w = edge[2];
        if(dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
            cout << "Found negative cycle." << endl;
            return;
        }
    }
    for(ll d : dist) {
        cout << d << " ";
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
    ll src = 0;
    cin >> n >> e >> src;
	vector<vector<ll>> edges; 
	for(ll i = 0; i<e; i++) {
	    vector<ll> edge(3);
        cin >> edge[0] >> edge[1] >> edge[2];
        edges.push_back(edge);
	}	
    bellmanFord(src, edges, n);
    return 0;
}

/*
Input:
3 4 2
0 1 5
1 0 3
1 2 -1
2 0 1

Output:
1 6 0
*/
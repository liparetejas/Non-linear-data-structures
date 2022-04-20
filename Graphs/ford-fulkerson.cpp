/* Ford Fulkerson Algorithm for finding the maximum flow in a network.*/
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

ll bfs(ll source, ll sink, vector<ll>& parent, vector<vector<ll>>& residualGraph) {
    fill(parent.begin(), parent.end(), -1);
    ll V = residualGraph.size();
    parent[source] = -2;
    queue<pair<ll, ll>> q;
    q.push({source, INT_MAX});

    while (!q.empty()) {
        ll u = q.front().first;
        ll capacity = q.front().second;
        q.pop();
        for (ll av=0; av < V; av++) {
            if (u != av && parent[av] == -1 && residualGraph[u][av] != 0) {
                parent[av] = u;
                ll min_cap = min(capacity, residualGraph[u][av]);
                if (av == sink)
                    return min_cap;
                q.push({av, min_cap});
            }
        }
    }
    return 0;
}

ll ford_fulkerson(vector<vector<ll>>& graph, ll source, ll sink) {
    vector<ll> parent(graph.size(), -1);
    vector<vector<ll>> residualGraph = graph;
    ll min_cap = 0, max_flow = 0;
    while (min_cap = bfs(source, sink, parent, residualGraph)) {
        max_flow += min_cap;
        ll u = sink;
        while (u != source) {
            ll v = parent[u];
            residualGraph[u][v] += min_cap;
            residualGraph[v][u] -= min_cap;
            u = v;
        }
    }
    return max_flow;
}

int main()
{
	/* ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL); */
	ll n = 0;
    ll e = 0;
    cin >> n >> e; 
	vector<vector<ll>> graph(n, vector<ll> (n, 0));

	for(ll i = 0; i<e; i++) {
	    ll u, v, w; 
	    cin >> u >> v >> w;
	    graph[u][v] = w;
	}
	cout << "Maximum Flow: " << ford_fulkerson(graph, 0, 5) << endl;
    return 0;	
}

/*
Input:
7 7
0 1 4
0 3 3
1 2 4
2 3 3
2 5 2
3 4 6
4 5 6

Output:
Maximum Flow: 7
*/
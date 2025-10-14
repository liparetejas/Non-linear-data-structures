/* Dijkstra's shortest path algorithm implemented using three methods. */
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

// Time: E.log(N)
void dijkstraOne(ll src, vector<vector<pair<ll, ll>>>& adjList, ll n) {
    vector<ll> dist(n, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    q.push({0, src});
    while(!q.empty()) {
        ll curr = q.top().second;
        ll d = q.top().first;
        q.pop();
        for(auto adjNodePair : adjList[curr]) {
            ll adjNode = adjNodePair.first;
            ll w = adjNodePair.second;
            if(d+w < dist[adjNode]) {
                dist[adjNode] = d+w;
                q.push({dist[adjNode], adjNode});
            }
        }
    }
    for(ll d : dist) {
        cout << d << " ";
    }
    cout << endl;
}

// Time: E.log(N)
void dijkstraTwo(ll src, vector<vector<pair<ll, ll>>>& adjList, ll n) {
    vector<ll> dist(n, INT_MAX);
    dist[src] = 0;
    set<pair<ll, ll>> st;
    st.insert({0, src});
    while(!st.empty()) {
        pair<ll, ll> currPair = *(st.begin());
        ll curr = currPair.second;
        ll d = currPair.first;
        st.erase(currPair);
        for(auto adjNodePair : adjList[curr]) {
            ll adjNode = adjNodePair.first;
            ll w = adjNodePair.second;
            if(d+w < dist[adjNode]) {
                // If distance is not infinite, then it has already been visited by one of the other nodes.
                // Since we have a better distance, erase earlier pair from the set.
                if(dist[adjNode] != INT_MAX) {
                    st.erase({dist[adjNode], adjNode});
                }
                dist[adjNode] = d+w;
                st.insert({dist[adjNode], adjNode});
            }
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
    cin >> n >> e;
	vector<vector<pair<ll, ll>>> adjList(n); 
	for(ll i = 0; i<e; i++) {
	    ll u, v, w; 
	    cin >> u >> v >> w;
	    adjList[u].push_back({v, w});
	    adjList[v].push_back({u, w}); 
	}	
    dijkstraOne(0, adjList, n);
    dijkstraTwo(0, adjList, n);
    return 0;
}

/*
Input:
3 3
0 2 6
0 1 1
1 2 3

Output:
0 1 4
*/
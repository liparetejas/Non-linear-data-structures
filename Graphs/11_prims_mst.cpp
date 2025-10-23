/* Prim's algorithm to find MST */
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

// Time: E.log(E); Space: E
ll primsMST(ll n, vector<vector<pair<ll, ll>>>& adjList) {
    ll mst = 0;
    vector<bool> visited(n, 0);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    q.push({0, 0}); // {distance, node}
    while(!q.empty()) {
        ll dist = q.top().first;
        ll node = q.top().second;
        q.pop();
        if(!visited[node]) {
            mst += dist;
        }
        else {
            continue;
        }
        visited[node] = 1;
        for(auto adjPair : adjList[node]) {
            ll adjNode = adjPair.first;
            ll adjDist = adjPair.second;
            if(!visited[adjNode]) {
                q.push({adjDist, adjNode});
            }
        }
    }
    return mst;
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
    cout << primsMST(n, adjList) << endl;
    return 0;
}

/*
Input:
3 3
0 1 5
1 2 3
0 2 1

Output:
4
*/
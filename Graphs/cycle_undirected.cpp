/* Cycle detection in an undirected graph using BFS and DFS algorithms */
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

// Time: O(n) Space: O(n)
bool detectCycleBFS(ll n, vector<vector<ll>> adjList) {
	vector<bool> visited(n+1, false);
	for(ll i = 1; i<=n; i++) {
		if(!visited[i]) {
			queue<pair<ll, ll>> q;
			q.push({i, -1});
			visited[i] = true;
			while(!q.empty()) {
				ll curr = q.front().first;
                ll prev = q.front().second;
				q.pop();
				visited[curr] = true;
				for(ll j : adjList[curr]) {
					if(!visited[j]) {
						q.push({j, curr});
						visited[j] = true;
					}
                    else if(prev != j) {
                        return true;
                    }
				}
			}
		}
	}
    return false;
}

// Time: O(n) Space: O(n)
bool dfs(ll curr, ll prev, vector<bool>& visited, vector<vector<ll>> adjList) {
	visited[curr] = true;
	for(ll node : adjList[curr]) {
		if(!visited[node]) {
			if(dfs(node, curr, visited, adjList)) {
                return true;
            }
		}
        else if(prev != node) {
            return true;
        }
	}
    return false;
}

bool detectCycleDFS(ll n, vector<vector<ll>> adjList) {
	vector<bool> visited(n+1, false);
	for(ll i=1; i<=n; i++) {
		if(!visited[i]) {
			if(dfs(i, -1, visited, adjList)) {
                return true;
            }
		}
	}
	return false;
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
	    adjList[v].push_back(u); 
	}
	if(detectCycleBFS(n, adjList)) {
        cout << "Cycle detected using BFS." << endl;
    }
    else {
        cout << "Cycle absent." << endl;
    }
    if(detectCycleDFS(n, adjList)) {
        cout << "Cycle detected using DFS." << endl;
    }
    else {
        cout << "Cycle absent." << endl;
    }
	return 0;	
}

/*
Input:
11 10
1 2
2 4
3 5
5 6
5 10
6 7
7 8
8 9
8 11
9 10

Output:
Cycle detected using BFS.
Cycle detected using DFS.

Input:
11 10
1 2
2 4
4 8
3 5
5 6
5 10
6 7
8 9
8 11
9 10

Output:
Cycle absent.
Cycle absent.
*/
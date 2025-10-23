/* Bridges in a Graph (Tarjan's algorithm') */
/*
Keep track of two arrays
1. timeInsert[i]: Time of insertion of node i according to DFS
2. low[i]: lowest time to reach node i
*/
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

// Time: O(V + E) | Space: O(V + E)
void dfs(int currNode, int parent, int currTime, vector<int>& visited,
			vector<int>& timeInsert, vector<int>& low,
			vector<vector<int>>& bridges, vector<vector<int>>& adjList) {
        currTime++;
        visited[currNode] = 1;
        timeInsert[currNode] = currTime;
        low[currNode] = currTime;
        for(int adjNode : adjList[currNode]) {
            if(adjNode == parent) {
                continue;
            }
            if(!visited[adjNode]) {
                dfs(adjNode, currNode, currTime, visited, timeInsert, low, bridges, adjList);
                low[currNode] = min(low[currNode], low[adjNode]);
                if(low[adjNode] > timeInsert[currNode]) {
                    bridges.push_back({currNode, adjNode});
                }

            } else {
                low[currNode] = min(low[currNode], low[adjNode]);
            }
        }
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
		adjList[v].push_back(u);
	}
	vector<int> visited(n, 0);
    vector<int> timeInsert(n, 0);
    vector<int> low(n, 0);
    int time = 0;
    vector<vector<int>> bridges;
    dfs(0, -1, time, visited, timeInsert, low, bridges, adjList);
	for(vector<int> bridge : bridges) {
		cout << bridge[0] << " - " << bridge[1] << endl;
	}
	return 0;	
}

/*
Input:
12 14
0 1
1 2
2 3
0 3
3 4
4 5
5 6
5 8
6 7
7 8
7 9
9 10
9 11
10 11

Outut:
7 - 9
4 - 5
3 - 4
*/
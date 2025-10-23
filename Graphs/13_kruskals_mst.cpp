/* Kruskal's algorithm to find MST */
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

class DisjointSet{
	private:
		vector<int> par, size;
		
	public:
		DisjointSet(int n) {
			this->par.resize(n+1, 0);
			iota(this->par.begin(), this->par.end(), 0);
			this->size.resize(n+1, 1); 
		}

		int findParent(int u) {
			if(u == this->par[u]) {
				return u;
			}
			return this->par[u] = findParent(this->par[u]);
		}
		
		void unionUnV(int u, int v) {
			int parU = findParent(u);
			int parV = findParent(v);
			if(parU == parV) {
				return;
			}
			if(size[parU] < size[parV]) {
				this->par[parU] = parV;
				size[parV] += size[parU];
			} else {
				this->par[parV] = parU;
				size[parU] += size[parV];
			}
		}
};

// Time: O(V + E) + O(Elog(E)) + O(8E.Alpha) | Space: O(E)
int kruskalsMST(int n, vector<vector<pair<int, int>>>& adjList) {
    vector<vector<int>> edges;
	// O(V + E)
    for(int node=0; node<n; node++) {
    	for(pair<int, int> adjNodePair : adjList[node]) {
    		int adjNode = adjNodePair.first;
    		int weight = adjNodePair.second;
    		edges.push_back({weight, node, adjNode});
    	}
    }
	// O(Elog(E))
    sort(edges.begin(), edges.end());
    DisjointSet ds(n);
	int mst = 0;
	// O(8E.Alpha)
	for(vector<int> edge : edges) {
		int currNode = edge[1];
		int adjNode = edge[2];
		int weight = edge[0];
		if(ds.findParent(currNode) != ds.findParent(adjNode)) {
			mst += weight;
			ds.unionUnV(currNode, adjNode);
		}
	}
	return mst;
}

int main()
{
	/* ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL); */
	int n = 0;
    int e = 0;
    cin >> n >> e;
	vector<vector<pair<int, int>>> adjList(n); 
	for(int i = 0; i<e; i++) {
	    int u, v, w; 
	    cin >> u >> v >> w;
	    adjList[u].push_back({v, w});
	    adjList[v].push_back({u, w}); 
	}	
    cout << kruskalsMST(n, adjList) << endl;
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

Input:
6 9
0 3 1
0 1 2
1 2 3
1 3 3
0 4 4
2 3 5
1 5 7
2 5 8
3 4 9

Output:
17
*/
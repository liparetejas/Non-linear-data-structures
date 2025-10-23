/* Disjoint Set Data Structure */
#include<bits/stdc++.h>
#define M 1000000007
#define endl '\n'
using namespace std;

/*
  FindPar(u):
    Find ultimate parent of u and return par(u).
    Use path compression to make the process efficient.
*/

/* 
  Union(u, v):
    1. Find ultimate parent of u & v i.e. par(u) & par(v) resp.
    2. Find rank of par(u) & par(v).
    3. Connect smaller rank to larger rank.
*/

// Time: O(4.Alpha) ~ O(1)
class DistjointSet {
    vector<int> rank, parent, size;
public:
    DistjointSet(int n) {
        rank.resize(n+1, 0);
        size.resize(n+1, 1);
        parent.resize(n+1, 0);
        iota(parent.begin(), parent.begin()+n, 0);
    }

    int findPar(int u) {
        if(u == parent[u]) {
            return u;
        }
        return parent[u] = findPar(parent[u]); // Path compression line
    }

    void unionByRank(int u, int v) {
        int pu = findPar(u);
        int pv = findPar(v);
        if(pu == pv) {
            return;
        }
        if(rank[pu] < rank[pv]) {
            parent[pu] = pv;
        }
        else if(rank[pu] > rank[pv]) {
            parent[pv] = pu;
        }
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }

    void unionBySize(int u, int v) {
        int pu = findPar(u);
        int pv = findPar(v);
        if(pu == pv) {
            return;
        }
        if(size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        }
        else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

int main()
{
	/* ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL); */
    DistjointSet du(8);
    du.unionByRank(1, 2);
    du.unionByRank(2, 3);
    du.unionByRank(4, 5);
    du.unionByRank(6, 7);
    du.unionByRank(5, 6);
    if(du.findPar(3) == du.findPar(7)) {
        cout << "Same component!" << endl;
    }
    else {
        cout << "Not same component!" << endl;
    }
    du.unionByRank(3, 7);
    if(du.findPar(3) == du.findPar(7)) {
        cout << "Same component!" << endl;
    }
    else {
        cout << "Not same component!" << endl;
    }
    DistjointSet du1(8);
    du1.unionBySize(1, 2);
    du1.unionBySize(2, 3);
    du1.unionBySize(4, 5);
    du1.unionBySize(6, 7);
    du1.unionBySize(5, 6);
    if(du1.findPar(3) == du1.findPar(7)) {
        cout << "Same component!" << endl;
    }
    else {
        cout << "Not same component!" << endl;
    }
    du1.unionBySize(3, 7);
    if(du1.findPar(3) == du1.findPar(7)) {
        cout << "Same component!" << endl;
    }
    else {
        cout << "Not same component!" << endl;
    }
    return 0;
}

/*
Output:
Not same component!
Same component!
Not same component!
Same component!
*/
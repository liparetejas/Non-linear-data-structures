/* Five nodes work as a source for the algorithm. 
   Multisource shortest path algorithm. 
   Helps in the detection of negative cycle as well.
   Uses adjacency matrix and works on directed graphs only. */
#include<bits/stdc++.h>
#define M 1000000007
#define ll long long int
#define endl '\n'
using namespace std;

// Time: O(N^3) Space: (N^2)
void floydWarshall(ll n, vector<vector<ll>>& adjMat) {
    for(ll i=0; i<n; i++) {
        for(ll j=0; j<n; j++) {
            if(adjMat[i][j] == -1) {
                adjMat[i][j] = 1e5;
            }
        }
    }
    for(ll viaNode=0; viaNode<n; viaNode++) {
        for(ll i=0; i<n; i++) {
            for(ll j=0; j<n; j++) {
                adjMat[i][j] = min(adjMat[i][j], adjMat[i][viaNode] + adjMat[viaNode][j]);
            }
        }
    }
    for(ll i=0; i<n; i++) {
        if(adjMat[i][i] < 0) {
            cout << "Found a neagtive cycle" << endl;
        }
    }
    for(ll i=0; i<n; i++) {
        for(ll j=0; j<n; j++) {
            if(adjMat[i][j] == 1e5) {
                adjMat[i][j] = -1;
            }
        }
    }
    for(ll i=0; i<n; i++) {
        for(ll j=0; j<n; j++) {
            cout << adjMat[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
	/* ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL); */
	ll n = 0;
    cin >> n;
	vector<vector<ll>> adjMat(n, vector<ll>(n, 0)); 
	for(ll i=0; i<n; i++) {
        for(ll j=0; j<n; j++) {
            cin >> adjMat[i][j];
        }
    }	
    floydWarshall(n, adjMat);
    return 0;
}

/*
Input:
3
0 1 43
1 0 6
-1 -1 0

Output:
0 1 7 
1 0 6
-1 -1 0
*/
/*
    0-1 BFS

    0-1 BFS is used to find the shortest path in a graph where every edge weight
    is either 0 or 1.

    It is similar to Dijkstra's algorithm, but instead of using a priority_queue,
    we use a deque.

    Why deque?
    -----------
    If edge weight is 0:
        The distance does not increase, so we push the new node to the FRONT.

    If edge weight is 1:
        The distance increases by 1, so we push the new node to the BACK.

    This keeps smaller-distance nodes near the front of the deque.

    Important condition:
    --------------------
    0-1 BFS only works when edge weights are 0 or 1.
    If edge weights are anything else, use Dijkstra's algorithm.

    Time Complexity:  O(V + E)
    Space Complexity: O(V)
*/

#include <bits/stdc++.h>
#define ll long long int
#define endl '\n'
using namespace std;

/*
    General 0-1 BFS function for a graph.

    n   = number of nodes
    src = source node
    adj[u] contains pairs {v, w}
        v = neighbor node
        w = edge weight, either 0 or 1
*/
vector<int> zeroOneBFS(int n, int src, vector<vector<pair<int, int>>>& adj) {
    deque<int> dq;
    vector<int> dist(n, 1e9);

    dist[src] = 0;
    dq.push_front(src);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;

                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }

    return dist;
}

/*
    LeetCode-style problem:
    Find if there is a safe walk through the grid.

    grid[i][j] = 0 means safe cell, cost 0 health
    grid[i][j] = 1 means unsafe cell, cost 1 health

    We need to reach bottom-right with total damage strictly less than health.

    Since every cell cost is either 0 or 1, this is a perfect use case for 0-1 BFS.

    Meaning of dis[i][j]:
    ---------------------
    Minimum health lost to reach cell (i, j).
*/
class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dis(m, vector<int>(n, 1e9));

        // Starting cell also costs health if grid[0][0] == 1.
        dis[0][0] = grid[0][0];

        // Each element is {currentCost, row, col}.
        deque<vector<int>> dq;
        dq.push_front({dis[0][0], 0, 0});

        vector<pair<int, int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        while (!dq.empty()) {
            auto t = dq.front();
            dq.pop_front();

            int currCost = t[0];
            int i = t[1];
            int j = t[2];

            // Skip old entries if we already found a better way later.
            if (currCost > dis[i][j]) continue;

            for (auto d : dir) {
                int ni = i + d.first;
                int nj = j + d.second;

                if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                    int w = grid[ni][nj];

                    if (currCost + w < dis[ni][nj]) {
                        dis[ni][nj] = currCost + w;

                        if (w == 0) {
                            dq.push_front({dis[ni][nj], ni, nj});
                        } else {
                            dq.push_back({dis[ni][nj], ni, nj});
                        }
                    }
                }
            }
        }

        // We need health to stay positive after reaching the destination.
        return dis[m - 1][n - 1] < health;
    }
};

int main() {
    /*
        Example for general 0-1 BFS:

        Graph:
        0 --0--> 1
        0 --1--> 2
        1 --1--> 3
        2 --0--> 3

        Shortest cost from 0:
        dist[0] = 0
        dist[1] = 0
        dist[2] = 1
        dist[3] = 1
    */

    int n = 4;
    vector<vector<pair<int, int>>> adj(n);

    adj[0].push_back({1, 0});
    adj[0].push_back({2, 1});
    adj[1].push_back({3, 1});
    adj[2].push_back({3, 0});

    vector<int> dist = zeroOneBFS(n, 0, adj);

    cout << "Shortest distances from node 0:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": " << dist[i] << endl;
    }

    /*
        Example for grid problem:

        grid:
        0 1 0
        0 1 0
        0 0 0

        There is a path with total cost 0:
        (0,0) -> (1,0) -> (2,0) -> (2,1) -> (2,2)

        If health = 1, answer is true because damage 0 < health 1.
    */

    vector<vector<int>> grid = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    int health = 1;
    Solution sol;

    cout << endl;
    cout << "Can safely reach destination? ";
    cout << (sol.findSafeWalk(grid, health) ? "true" : "false") << endl;

    return 0;
}

/*
Output:
Shortest distances from node 0:
Node 0: 0
Node 1: 0
Node 2: 1
Node 3: 1

Can safely reach destination? true
*/

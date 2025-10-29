#include<bits/stdc++.h>
using namespace std;

class SegTree {
	public:
		int n;
		vector<int> v;
		vector<int> tree;
		
		SegTree(int n, vector<int> v) {
			this->n = n;
			this->v = v;
			this->tree = vector<int>(4*n, 0);
		}
		
		// O(N)
		void build(int node, int start, int end) {
			if(start == end) {
				tree[node] = v[start];
			}
			else {
				int mid = start + (end-start)/2;
				build(2*node, start, mid);
				build(2*node+1, mid+1, end);
				tree[node] = tree[2*node] + tree[2*node+1];
			}
		}
		
		// O(logN)
		void update(int node, int start, int end, int index, int val) {
			if(start == end) {
				v[index] += val;
				tree[node] += val;
			}
			else {
				int mid = start + (end-start)/2;
				if(start <= index && index <= mid) {
					update(2*node, start, mid, index, val);
				}
				else {
					update(2*node+1, mid+1, end, index, val);
				}
				tree[node] = tree[2*node] + tree[2*node+1];
			}
		}
		
		// O(logN)
		int query(int node, int start, int end, int l, int r) {
			if(r < start || end < l) {
				return 0;
			}
			else if(l <= start && end <= r) {
				return tree[node];
			}
			int mid = start + (end-start)/2;
			int p1 = query(2*node, start, mid, l, r);
			int p2 = query(2*node+1, mid+1, end, l, r);
			return p1+p2;
		}
	
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	SegTree* st = new SegTree(n, v);
	st->build(1, 0, n-1);
	// for(int node : st->tree) {
		// cout << node << " ";
	// }
	// cout << endl;
	while(m--) {
		int q, x, y;
		cin >> q >> x >> y;
		if(q == 1) {
			st->update(1, 0, n-1, x, y);
		}
		else if(q == 2) {
			cout << st->query(1, 0, n-1, x, y) << endl;
		}
	}
	return 0;
}
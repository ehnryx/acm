#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

struct DSU {
	vector<int> root;
	vector<int> weight;
	DSU(int n) {
		root.resize(n);
		memset(&root[0], -1, n*sizeof(root[0]));
		weight.resize(n);
		memset(&weight[0], 0, n*sizeof(weight[0]));
	}
	int find(int i) {
		if (root[i] == -1) return i;
		return root[i] = find(root[i]);
	}
	bool link(int i, int j) {
		int a = find(i);
		int b = find(j);
		if (a == b) return false;
		if (weight[a] < weight[b]) swap(a,b);
		root[b] = a;
		weight[a] += weight[b]+1;
		return true;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 

	int n, m, q;
	cin >> n >> m >> q;

	DSU dsu(n*m);
	vector<bool> black(n*m);
	int a, b, x, y;
	vector<int> com;
	for (int c = 0; c < q; c++) {
		cin >> a >> b >> x >> y;
		com.push_back(-1);
		for (int i = a-1; i < b; i++) {
			for (int j = x-1; j < y; j++) {
				if (!black[i*m+j]) {
					black[i*m+j] = true;
					com.push_back(i*m+j);
				}
			}
		}
	}

	int regions = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int links = 0;
			if (i > 0 && !black[(i-1)*m+j])
				links += dsu.link(i*m+j, (i-1)*m+j);
			if (j > 0 && !black[i*m+(j-1)])
				links += dsu.link(i*m+j, i*m+(j-1));
			regions -= links-1;
		}
	}

	vector<int> ans;
	ans.push_back(regions);
	for (int i = com.size()-1; i >= 0; i--) {
		if (com[i] == -1) {
			ans.push_back(regions);
		} else {
			a = i/m;
			b = i%m;
			black[i] = false;
			int links = 0;
			if (a > 0 && !black[(a-1)*m+b])
				links += dsu.link(a*m+b, (a-1)*m+b);
			if (b > 0 && !black[a*m+(b-1)])
				links += dsu.link(a*m+b, a*m+(b-1));
			if (a < n-1 && !black[(a+1)*m+b])
				links += dsu.link(a*m+b, (a+1)*m+b);
			if (b < m-1 && !black[a*m+(b+1)])
				links += dsu.link(a*m+b, a*m+(b+1));
			regions -= links-1;
		}
	}

	for (int i = ans.size()-1; i >= 0; i--) {
		cout << ans[i] << nl;
	}
	cout << "whats going on " << endl;

	return 0;
}

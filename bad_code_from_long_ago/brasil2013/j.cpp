#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct DSU {
	vector<int> weight;
	vector<int> root;
	DSU(int n) {
		weight.resize(n);
		memset(&weight[0], 0, n*sizeof(weight[0]));
		root.resize(n);
		memset(&root[0], -1, n*sizeof(root[0]));
	}

	int find(int i) {
		if (root[i] == -1) return i;
		else return root[i] = find(root[i]);
	}
	bool link(int i, int j) {
		int a = find(i);
		int b = find(j);
		if (a == b) return true;
		else {
			if (weight[a] < weight[b]) {
				root[a] = b;
				weight[b] += weight[a]+1;
			}
			else {
				root[b] = a;
				weight[a] += weight[b]+1;
			}
			return false;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	

	return 0;
}

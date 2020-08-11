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

	bool bad = false;
	int row, col;
	cin >> row >> col;
	int grid[row][col];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) { 
			cin >> grid[i][j];
			if (i > 0 && (grid[i][j] - grid[i-1][j])%col != 0) bad = true;
			if (j > 0 && (grid[i][j]-1)/col != (grid[i][j-1]-1)/col) bad = true;
		}
	}
	if (bad) {
		cout << "*" << endl;
		return 0;
	}
	DSU rowdsu(col);
	DSU coldsu(row);
	for (int j = 0; j < col; j++)
		rowdsu.link(j, (grid[0][j]-1)%col);
	for (int i = 0; i < row; i++)
		coldsu.link(i, (grid[i][0]-1)/col);
	
	int ans = 0;
	for (int j = 0; j < col; j++)
		if (rowdsu.root[j] == -1) ans += rowdsu.weight[j];
	for (int i = 0; i < row; i++)
		if (coldsu.root[i] == -1) ans += coldsu.weight[i];
	cout << ans << endl;

	return 0;
}

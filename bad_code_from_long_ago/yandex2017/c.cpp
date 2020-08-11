#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<vector<int>> graph;
	set<int> alive;
	int n, m;
	cin >> n >> m;
	graph.resize(n);
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a-1].push_back(b-1);
		graph[b-1].push_back(a-1);
		alive.insert(i);
	}

	return 0;
}

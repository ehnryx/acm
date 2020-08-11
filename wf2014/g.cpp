#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

struct Edge {
	int a, b, c;
};

int main() {
	ios::sync_with_stdio(0):
	cin.tie(0);

	int n;
	cin >> n;

	vector<Edge> edges;
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			int c;
			cin >> c;
			edges.push_back({i,j,c});
		}
	}

	return 0;
}

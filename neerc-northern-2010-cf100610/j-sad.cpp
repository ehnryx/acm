#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';

#define FILE "journey"

struct Edge {
	int a, b, c;
};

const int N = 2e3+1;
int dist[N];
vector<int> adj[N];

const int M = 2e5+1;
Edge edges[M], graph[M];

int get(int g, int a) {
	return 2*a + g;
}

int main() {
	if (fopen(FILE ".in", "r")) {
		freopen(FILE ".in", "r", stdin);
		freopen(FILE ".out", "w", stdout);
	}

	int n, s, t;
	cin >> n >> s >> t;

	int eid = 0;
	for(int g=0; g<2; g++) {
		int m;
		cin >> m;
		for(int i=0; i<m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			edges[i] = {a,b,c};
		}
		fill(dist, dist+N, 2*INF);
		dist[t] = 0;
		for(int i=1; i<n; i++) {
			for(int j=0; j<m; j++) {
				auto [a,b,c] = edges[j];
				dist[a] = min(dist[a]-c, dist[b]) + c;
				dist[b] = min(dist[b]-c, dist[a]) + c;
			}
		}
		for(int j=0; j<m; j++) {
			auto [a,b,c] = edges[j];
			if(dist[b] > dist[a]) swap(a,b);
			if(dist[a] > dist[b]) {
				a = get(g, a);
				b = get(g^1, b);
				adj[a].push_back(b);
				graph[eid++] = {a,b,-c};
				assert(c>0);
			}
		}
	}

	fill(dist, dist+N, 2*INF);
	dist[get(0, s)] = 0;
	for(int i=1; i<2*n; i++) {
		for(int j=0; j<eid; j++) {
			auto [a,b,c] = graph[j];
			dist[b] = min(dist[b], dist[a]+c);
		}
	}
	for(int j=0; j<eid; j++) {
		auto [a,b,c] = graph[j];
		if(dist[a]+c < dist[b]) {
			if(min(dist[a], dist[b]) <= 0) {
				cout << -1 << nl;
				return 0;
			}
		}
	}
	cout << -min(dist[get(0, t)], dist[get(1, t)]) << nl;

	return 0;
}

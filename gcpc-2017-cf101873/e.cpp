#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
	int a, b;
	ld c;
	Edge(){}
	Edge(int a, int b, ld c): a(a), b(b), c(c) {}
};

const int N = 800+1;
ld dist[N];

void init() {
	fill(dist, dist+N, INF);
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	init();

	int n, m;
	cin >> n >> m;

	int a, b;
	ld c;
	vector<Edge> edges;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		edges.push_back(Edge(a,b,-log(c)));
	}

	for (int i = 1; i < n; i++) {
		for (const Edge& e : edges) {
			dist[e.b] = min(dist[e.b], dist[e.a] + e.c);
		}
	}

	for (const Edge& e : edges) {
		if (dist[e.b] > dist[e.a] + e.c + EPS) {
			cout << "inadmissible" << nl;
			return 0;
		}
	}

	cout << "admissible" << nl;

	return 0;
}

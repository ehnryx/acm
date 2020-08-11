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

const int N = 2e5+7;
vector<int> adj[N];
int indeg[N];
int ans[N/2][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, a, b, x, y;
	cin >> n >> a >> b;

	for (int i=0; i<a; i++) {
		cin >> x >> y;
		adj[2*x+1].push_back(2*y);
		indeg[2*y] += 1;
	}

	for (int i=0; i<b; i++) {
		cin >> x >> y;
		adj[2*x].push_back(2*y+1);
		adj[2*y].push_back(2*x+1);
		indeg[2*y+1] += 1;
		indeg[2*x+1] += 1;
	}

	for (int i=1; i<=n; i++) {
		adj[2*i].push_back(2*i+1);
		indeg[2*i+1] += 1;
	}

	queue<int> topo;
	for (int i=1; i<=n; i++) {
		for (int j=0; j<2; j++) {
			if (indeg[2*i+j] == 0) topo.push(2*i+j);
		}
	}

	int vis = 0;
	int pos = 0;
	while (!topo.empty()) {
		int cur = topo.front(); topo.pop();
		ans[cur/2][cur%2] = pos++;
		vis += 1;

		for (int nxt : adj[cur]) {
			indeg[nxt] -= 1;
			if (indeg[nxt] == 0) topo.push(nxt);
		}
	}

	if (vis != 2*n) {
		cout << "NO" << nl;
	} else {
		cout << "YES" << nl;
		for (int i=1; i<=n; i++) {
			cout << ans[i][0] << " " << ans[i][1] << nl;
		}
	}

	return 0;
}

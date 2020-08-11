//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3 + 1;
int adj[N][4];
int oth[N][4];
bool vis[N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		for(int j=0; j<4; j++) {
			cin >> adj[i][j];
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=0; j<4; j++) {
			cin >> oth[i][j];
		}
	}

	queue<pair<int,int>> bfs;
	vis[1][1] = true;
	bfs.push(make_pair(1, 1));
	while(!bfs.empty()) {
		auto [a, b] = bfs.front();
		bfs.pop();
		for(int i=0; i<4; i++) {
			if(adj[a][i] == 0) continue;
			int u = adj[a][i];
			int v = oth[b][i];
			if(vis[u][v]) continue;
			vis[u][v] = true;
			bfs.push(make_pair(u, v));
		}
	}

	bool ok = false;
	bool no = false;
	for(int i=0; i<=n; i++) {
		if(vis[n][i]) {
			ok = true;
			if(i != n) no = true;
		}
	}
	if(!ok) {
		cout << "Impossible" << nl;
	} else if(no) {
		cout << "No" << nl;
	} else {
		cout << "Yes" << nl;
	}

	return 0;
}

//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e4;
const int M = 1e3;
int dist[N][M];

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	vector<int> a(m);
	for(int i=0; i<m; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	int g, r;
	cin >> g >> r;

	memset(dist, INF, sizeof dist);
	deque<tuple<int,int,int>> bfs;
	bfs.emplace_back(0, 0, 0);
	dist[0][0] = 0;
	while(!bfs.empty()) {
		auto [i, t, d] = bfs.front();
		bfs.pop_front();
		if(dist[i][t] != d) continue;
		if(i+1 < m) {
			int nt = (t + a[i+1] - a[i] == g ? 0 : t + a[i+1] - a[i]);
			if(nt < g && d + !nt < dist[i+1][nt]) {
				dist[i+1][nt] = d + !nt;
				if(!nt) {
					bfs.emplace_back(i+1, nt, dist[i+1][nt]);
				} else {
					bfs.emplace_front(i+1, nt, dist[i+1][nt]);
				}
			}
		}
		if(i > 0) {
			int nt = (t + a[i] - a[i-1] == g ? 0 : t + a[i] - a[i-1]);
			if(nt < g && d + !nt < dist[i-1][nt]) {
				dist[i-1][nt] = d + !nt;
				if(!nt) {
					bfs.emplace_back(i-1, nt, dist[i-1][nt]);
				} else {
					bfs.emplace_front(i-1, nt, dist[i-1][nt]);
				}
			}
		}
	}

	ll ans = INFLL;
	for(int i=0; i<g; i++) {
		if(dist[m-1][i] == INF) continue;
		ll cur = (ll) dist[m-1][i] * (r+g) + i;
		if(i == 0) cur -= r;
		ans = min(ans, cur);
	}
	if(ans == INFLL) {
		cout << -1 << nl;
	} else {
		cout << ans << nl;
	}

	return 0;
}

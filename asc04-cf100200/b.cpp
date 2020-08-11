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

namespace BCC {
	const int N = 1e4 + 2;
	const int M = 1e5 + 7;
	int vcompNum, ecompNum, I, m;
	int first[N], low[N], vis[N], ecomp[N];
	int nxt[2*M], ep[2*M], vcomp[2*M];
	stack<int> edges, verts;
	void init() { m = 0; memset(first, -1, sizeof first); }
	void add_edge(int a, int b) {
		nxt[m] = first[ep[m] = a]; first[ep[m]] = m; ++m;
		nxt[m] = first[ep[m] = b]; first[ep[m]] = m; ++m;
	}
	void biconnected(int u, int par) { int v, E; low[u] = vis[u] = ++I;
		verts.push(u); for(int e=first[u]; e!=-1; e=nxt[e]) { v = ep[e^1];
			if(!vis[v]) { edges.push(e); biconnected(v, e);
				low[u] = min(low[u], low[v]);
				if(vis[u] <= low[v]) {
					do { E = edges.top(); edges.pop(); vcomp[E] = vcomp[E^1] = vcompNum; }
					while(e != E && e != (E^1)); ++vcompNum;
				}
			} else if(vis[v] < vis[u] && e != (par^1)) {
				low[u] = min(low[u], vis[v]); edges.push(e);
			} else if(v == u) {
				vcomp[e] = vcomp[e^1] = vcompNum++;
			}
		}
		if(vis[u] <= low[u]) {
			do { v = verts.top(); verts.pop(); ecomp[v] = ecompNum; } while(v!=u);
			++ecompNum;
		}
	}
	void get_bcc(int n) {
		memset(vis,0,sizeof vis); vcompNum = ecompNum = I = 0;
		for(int i=1; i<=n; i++) if(!vis[i]) biconnected(i, -1);
	}
	bool isCutEdge(int e) { return ecomp[ep[e]] != ecomp[ep[e^1]]; }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

#ifdef ONLINE_JUDGE
	freopen("bridges.in", "r", stdin);
	freopen("bridges.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;
	BCC::init();
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		BCC::add_edge(a, b);
	}
	BCC::get_bcc(n);

	vector<int> ans;
	for(int i=0; i<m; i++) {
		if(BCC::isCutEdge(2*i)) {
			ans.push_back(i+1);
		}
	}
	cout << ans.size() << nl;
	for(int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}

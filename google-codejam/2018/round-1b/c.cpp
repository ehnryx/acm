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
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) { os << it << " "; }
	return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
	return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////



int main(int argc, char** argv) {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		cout << "Case #" << cc << ": ";
		casesolve();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////



void casesolve() {

	int n;
	cin >> n;
	int a[n+1], b[n+1];
	for(int i=1; i<=n; i++) {
		cin >> a[i] >> b[i];
	}
	ll init[n+1], g[n+1];
	for(int i=1; i<=n; i++) {
		cin >> init[i];
	}

	ll l = 0;
	ll r = 100 * 1e9;
	while(l < r) {
		ll m = (l+r+1) / 2;
		for(int i=1; i<=n; i++) {
			g[i] = init[i];
		}
		g[1] -= m;
		bool ok = true;
		if(g[1] < 0) {
			queue<int> bfs;
			vector<int> vis(n+1);
			bfs.push(1);
			vis[1]++;
			while(!bfs.empty()) {
				int u = bfs.front();
				bfs.pop();
				if(g[u] < 0) {
					g[a[u]] += g[u];
					g[b[u]] += g[u];
					g[u] = 0;
					if(g[a[u]] < 0) {
						if(g[a[u]] < -INFLL || ++vis[a[u]] > 2*n*n) {
							ok = false;
							break;
						}
						bfs.push(a[u]);
					}
					if(g[b[u]] < 0) {
						if(g[b[u]] < -INFLL || ++vis[b[u]] > 2*n*n) {
							ok = false;
							break;
						}
						bfs.push(b[u]);
					}
				}
			}
		}

		if(ok) {
			l = m;
		} else {
			r = m-1;
		}
	}

	cout << r << nl;

	return;
}


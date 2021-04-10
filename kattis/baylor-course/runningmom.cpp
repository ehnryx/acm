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

const int N = 1e4+1;
vector<int> adj[N];
int vis[N];

bool cycle(int u) {
	if (vis[u] == 1) return true;
	if (vis[u] == 2) return false;
	vis[u]++;
	for (int x : adj[u]) {
		if (cycle(x)) return true;
	}
	vis[u]++;
	return false;
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

	int n;
	cin >> n;

	int id = 0;
	unordered_map<string,int> idx;
	for (int i=0; i<n; i++) {
		string s, t;
		cin >> s >> t;
		if (!idx.count(s)) idx[s] = id++;
		if (!idx.count(t)) idx[t] = id++;
		adj[idx[s]].push_back(idx[t]);
	}

	for (string s; cin >> s; ) {
		memset(vis, 0, sizeof vis);
		if (cycle(idx[s])) {
			cout << s << " safe" << nl;
		} else {
			cout << s << " trapped" << nl;
		}
	}

	return 0;
}

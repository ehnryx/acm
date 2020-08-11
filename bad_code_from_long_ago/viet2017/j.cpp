#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(chrono::high_resolution_clock::now().time_since_epoch().count()); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Tree {
	set<int> centroids;
	vector<vector<adj>> adj;
	vector<ll> sum;
	vector<ll> depth;
	vector<ll> depth2;

	Tree(int n) {
		adj.resize(n);
		sum.resize(n);
		depth.resize(n);
		depth2.resize(n);
	}

	void add_edge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	void get_centroid() {
		;
	}

	void dfs(int cur, int par) {
		depth[cur] = sum[cur] = sum2[cur] = 0;
		for (int x : adj[cur]) {
			if (x != par) {
				dfs(x, cur);
				depth[cur] = max(depth[cur], 1 + depth[x]);
				sum[cur] += sum[x];
				sum2[cur] += sum2[x];
			}
		}
		sum[cur] += depth[cur];
		sum2[cur] += sqr(depth[cur]);
	}
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	srand();

	int a, b;

	int n;
	cin >> n;
	Tree eyqs(n+1);
	for (int i = 1; i < n; i++) {
		cin >> a >> b;
		eyqs.add_edge(a,b);
	}

	int m;
	cin >> m;
	Tree eyqs(m+1);
	for (int i = 1; i < m; i++) {
		cin >> a >> b;
		cactus.add_edge(a,b);
	}

	return 0;
}

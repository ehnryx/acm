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

const int N = 2e5 + 10;
int low[N], vis[N], scomp[N], scompNum, I;
vector<int> adj[N]; stack<int> verts;
void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
	for (int v : adj[u]) {
		if (!vis[v]) scc(v);
		if (scomp[v] == -1) low[u] = min(low[u], low[v]);
	}
	if (vis[u] <= low[u]) { int v;
		do { v = verts.top(); verts.pop(); scomp[v] = scompNum; } while (v != u);
		++ scompNum;
	}
}
void get_scc(int n) { memset(vis, 0, sizeof vis); memset(scomp, -1, sizeof scomp); 
	scompNum = I = 0; for (int i = 1; i <= n; ++i) if (!vis[i]) scc(i); 
}

double label[N], ans[N];
double curmin[N];
set<int> dag[N];

double get_rand() {
	return (double) (rand() << 15 | rand()) / (RAND_MAX << 15 | RAND_MAX);
}

void solve(int n) {
	for (int i = 0; i < scompNum; i++) {
		curmin[i] = label[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		label[scomp[i]] = min(label[scomp[i]], get_rand());
	}

	for (int i = 0; i < scompNum; i++) {
		curmin[i] = min(curmin[i], label[i]);
		for (int j : dag[i]) {
			curmin[j] = min(curmin[j], curmin[i]);
		}
	}

	for (int i = 1; i <= n; i++) {
		ans[i] += curmin[scomp[i]];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(0);
	srand();

	int n, m;
	cin >> n >> m;

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
	}
	get_scc(n);

	for (int i = 1; i <= n; i++) {
		ans[i] = 0;
		for (int j : adj[i]) {
			dag[scomp[j]].insert(scomp[i]);
		}
	}

	int cnt;
	for (cnt = 0; clock() < 5*CLOCKS_PER_SEC; cnt++) {
		solve(n);
	}

	for (int i = 1; i <= n; i++) {
		cout << max((int)round(cnt/ans[i]) - 1, 0) << nl;
	}

	return 0;
}

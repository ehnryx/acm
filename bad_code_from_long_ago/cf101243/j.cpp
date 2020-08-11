#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

namespace Dinic {
	const int N = 200 + 10;
	const int M = 100*100 + 500;
	int par[N], first[N], nxt[2*M], ep[2*M], m;
	ll flo[2*M], cap[2*M], cost[2*M];
	void init() { m = 0; memset(first, -1, sizeof first); memset(flo, 0, sizeof flo); }
	void add_edge(int a, int b, ll c=1) {
		nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, ++m;
		nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, ++m;
	}

	int L[N], cur[N];
	bool bfs(int s, int t) {
		memset(L, INF, sizeof L);
		queue<int> q; q.push(s); L[s] = 0;
		while (!q.empty()) { int u = q.front(); q.pop();
			for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
				if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
					q.push(v), L[v] = L[u]+1;
		} return L[t] < INF;
	}
	ll dfs(int u, int t, ll f) {
		if (u == t) return f;
		ll cf, df = 0;
		for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
			if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
				cf = dfs(v, t, min(cap[e] - flo[e], f - df));
				flo[e] += cf; flo[e^1] -= cf; df += cf;
			}
		return df;
	}

	vector<pii> print(int src) {
		vector<pii> res;
		for (int e = first[src]; e != -1; e = nxt[e]) {
			if (flo[e] > 0) {
				int u = ep[e^1];
				for (int ee = first[u]; ee != -1; ee = nxt[ee]) {
					if (flo[ee] > 0) {
						res.push_back(pii(u, ep[ee^1]));
					}
				}
			}
		}
		return res;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, m;
	cin >> n >> m;

	vector<string> bus, trolley;
	vector<pii> left, right;

	int source = m+n;
	int sink = source+1;
	Dinic::init();

	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		bus.push_back(s);
		left.push_back(pii(s[0]+s[1]+s[2], s[3]+s[4]+s[5]));
		Dinic::add_edge(source, i);
	}
	for (int i = 0; i < m; i++) {
		cin >> s;
		trolley.push_back(s);
		right.push_back(pii(s[0]+s[1]+s[2], s[3]+s[4]+s[5]));
		Dinic::add_edge(n+i, sink);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (left[i].first == right[j].second || left[i].second == right[j].first) {
				Dinic::add_edge(i, n+j);
			}
		}
	}

	ll flow = 0;
	while (Dinic::bfs(source, sink)) {
		flow += Dinic::dfs(source, sink, INF);
	}

	cout << flow << nl;
	vector<pii> res = Dinic::print(source);
	for (const pii& ans : res) {
		if (left[ans.first].first == right[ans.second - n].second) {
			cout << "AT " << bus[ans.first] << " " << trolley[ans.second - n] << nl;
		} else {
			cout << "TA " << trolley[ans.second - n] << " " << bus[ans.first] << nl;
		}
	}

	return 0;
}

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
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
	const int N = 1202;
  // data structures and helper functions common to all flow routines
  struct Edge { int v, r; ll f, c, p; };
  vector<Edge> adj[N]; int sz[N]; ll mc;
  void init(int n=N) { mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, ll c=1, ll p=0) { mc = max(mc,c);
    adj[a].push_back({b, sz[b]++, 0, c, p});
    adj[b].push_back({a, sz[a]++, 0, 0, -p}); }  // change 0 to c for undirected
  // Improved shortest augmenting path algorithm
  // Time Complexity: O(V^2*E), significantly faster in practice
  // Usage: call preflow(T) then flow(S, T)
  int h[N], vh[N], his[N], pre[N], cur[N];
  void preflow(int t) { memset(vh, 0, sizeof vh); memset(h, INF, sizeof h);
    h[t] = 0; vh[0] = 1; queue<int> q({t});
    while (!q.empty()) { int u = q.front(); q.pop();
      for(int i = cur[u] = 0; i < sz[u]; i++) { const Edge& e = adj[u][i];
        if (h[e.v] == INF) { q.push(e.v); vh[h[e.v] = h[u]+1]++; } } } }
  ll flow(int s, int t) { int u = s; ll flow = 0, aug = INF;
    while (h[s] < N) { bool push = false; his[u] = aug;
      for(int i = cur[u]; i < sz[u]; i++) { const Edge& e = adj[u][i];
        if (e.f < e.c && h[u] == h[e.v]+1) {
          push = true; aug = min(aug, e.c-e.f); cur[u] = i; pre[u=e.v] = e.r;
          if (u == t) { for (flow += aug; u != s; u = adj[u][pre[u]].v) {
            Edge& r = adj[u][pre[u]]; r.f -= aug; adj[r.v][r.r].f += aug; }
          aug = INF; } break; } }
      if (push) continue; else if (!--vh[h[u]]) break; else h[u]=N;
      for(int i=0; i<sz[u]; i++) { const Edge& e = adj[u][i];
        if (e.f < e.c && h[e.v] < h[u]) { h[u] = h[e.v]; cur[u]=i; } }
      vh[++h[u]]++; if (u != s) { u = adj[u][pre[u]].v; aug = his[u]; } }
    return flow; }
}

const int N = 404;

int n,m;
int s[N],t[N];

vector<int> at[N];
int get_max() {
	for (int i=0; i<n; ++i) {
		at[s[i]].push_back(t[i]);
	}
	int ans = 0;
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i=0; i<N; ++i) {
		for (auto& x : at[i]) {
			pq.push(x);
		}
		while (!pq.empty() && pq.top() < i) {
			pq.pop();
		}
		if (!pq.empty()) {
			pq.pop();
			++ans;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	cin>>n>>m;
	for(int i=0;i<n;i++) {
		cin>>s[i]>>t[i];
	}

	const int S = n;
	const int T = n+801;
	for(int i=0;i<m;i++) {
		Flow::add_edge(S,i);
		for(int j=s[i];j<=t[i];j++) {
			Flow::add_edge(i,n+j);
		}
	}
	for(int i=m;i<n;i++) {
		Flow::add_edge(i,T);
		for(int j=s[i];j<=t[i];j++) {
			Flow::add_edge(n+400+j,i);
		}
	}
	for(int i=1;i<=400;i++) {
		Flow::add_edge(n+i,n+400+i);
	}

	Flow::preflow(T);
	int ans = Flow::flow(S,T);
	cout<<get_max()<<" "<<ans<<nl;

	return 0;
}

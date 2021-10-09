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
  const int M = N*N;
  int par[N], first[N], nxt[2*M], ep[2*M], m;
  ll flo[2*M], cap[2*M], cost[2*M];
  void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
  void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
    nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
    nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
  int L[N], cur[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L);
    queue<int> q; q.push(s); L[s] = 0;
    while (!q.empty()) { int u = q.front(); q.pop();
      for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
        if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
          q.push(v), L[v] = L[u]+1;
    } return L[t] < INF; }
  ll dfs(int u, int t, ll f) {
    if (u == t) return f;
    ll cf, df = 0;
    for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
      if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
        cf = dfs(v, t, min(cap[e]-flo[e], f-df));
        flo[e] += cf; flo[e^1] -= cf; df += cf;
      } return df; }
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
  Flow::init();
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

  int ans = 0;
  while(Flow::bfs(S,T)) {
    ans += Flow::dfs(S,T,INF);
  }

  cout<<get_max()<<" "<<ans<<nl;

  return 0;
}

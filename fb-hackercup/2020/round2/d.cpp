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

void read(int r[], int n, int k) {
  for(int i=1; i<=k; i++) {
    cin >> r[i];
  }
  ll a, b, c, d;
  cin >> a >> b >> c >> d;
  for(int i=k+1; i<=n; i++) {
    r[i] = (a*r[i-2] + b*r[i-1] + c) % d + 1;
  }
}

void read1(int r[], int n, int k) {
  for(int i=1; i<=k; i++) {
    cin >> r[i];
  }
  ll a, b, c;
  cin >> a >> b >> c;
  for(int i=k+1; i<=n; i++) {
    r[i] = (a*r[i-2] + b*r[i-1] + c) % (i-1) + 1;
  }
}

void read2(int r[], int n, int k, int m) {
  for(int i=1; i<=k; i++) {
    cin >> r[i];
  }
  ll a, b, c;
  cin >> a >> b >> c;
  for(int i=k+1; i<=n; i++) {
    r[i] = (a*r[i-2] + b*r[i-1] + c) % m + 1;
  }
}

struct Line {
  mutable ll m, b, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
    else x->p = div(y->b - x->b, x->m - y->m);
    return x->p >= y->p;
  }
  void add(ll m, ll b) {
    auto z = insert({m, b, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.m * x + l.b;
  }
};

const int N = 1<<20;
LineContainer st[2*N];

void clear(int n) {
  for(int i=0; i<=n; i++) {
    for(int j=i+N; j>0; j/=2) {
      st[j].clear();
    }
  }
}

void insert(int i, ll m, ll b) {
  st[i+=N].add(-m, -b);
  for(i/=2; i>0; i/=2) {
    st[i].add(-m, -b);
  }
}

ll query(int l, int r, ll x) {
  ll ans = INFLL;
  for(l+=N, r+=N; l<r; l/=2, r/=2) {
    if(l&1) ans = min(ans, -st[l++].query(x));
    if(r&1) ans = min(ans, -st[--r].query(x));
  }
  return ans;
}

int par[N], len[N], hire[N], x[N], y[N];
vector<int> adj[N];
ll depth[N];
int start[N], sub[N];

void build(int u, int& sid) {
  sub[u] = 1;
  depth[u] = depth[par[u]] + len[u];
  start[u] = sid++;
  for(int v : adj[u]) {
    build(v, sid);
    sub[u] += sub[v];
  }
  if(adj[u].empty()) {
    insert(start[u], depth[u], 0);
  } else {
    ll cur = -depth[u] * hire[u] + query(start[u]+1, start[u]+sub[u], hire[u]);
    insert(start[u], depth[u], cur);
  }
}

void casesolve() {

  int n, m, k;
  cin >> n >> m >> k;

  read1(par, n, k);
  read(len, n, k);
  read(hire, n, k);
  read2(x, m, k, n);
  read(y, m, k);

  clear(n);
  adj[1].clear();
  for(int i=2; i<=n; i++) {
    adj[i].clear();
    adj[par[i]].push_back(i);
    assert(par[i] < i);
  }
  int sid = 0;
  build(1, sid);

  ll ans = 1;
  for(int i=1; i<=m; i++) {
    ll cur = -depth[x[i]] * y[i] + query(start[x[i]], start[x[i]]+sub[x[i]], y[i]);
    assert(cur >= 0);
    assert(cur < INFLL);
    ans = ans * ((cur + 1) % MOD) % MOD;
  }
  cout << ans << nl;

  return;
}


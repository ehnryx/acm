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

vector<int> read(int n, int k) {
  vector<int> v(n+1);
  for(int i=2; i<=k+1; i++) {
    cin >> v[i];
  }
  ll a, b, c;
  cin >> a >> b >> c;
  for(int i=k+2; i<=n; i++) {
    v[i] = (a*v[i-2] + b*v[i-1] + c) % (i-1) + 1;
  }
  return v;
}

const int N = 1e6 + 1;
char s[N];
vector<int> adj[N];
int par[N], sz[N];

// sum, max, cnt, cur
tuple<ll,int,int,int> dp[N], up[N];
vector<tuple<ll,int,int,int>> pre[N], suf[N];

void update(int& m, int& c, int other, int cnt) {
  if(other > m) {
    m = other;
    c = 0;
  }
  if(other == m) {
    c += cnt;
  }
}

void combine(ll& sum, int& mx, int& cnt, int& cur, const tuple<ll,int,int,int>& o, bool merge) {
  auto [vsum, vmx, vcnt, vcur] = o;
  sum += vsum;
  update(mx, cnt, vmx, vcnt);
  if(merge && vcur > 0) {
    sum += (ll) cur * vcur;
    cur += vcur;
    update(mx, cnt, cur, cur);
  }
}

void solve_down(int u) {
  ll sum = 0;
  int mx = (s[u] == '*');
  int cnt = 1;
  int cur = (s[u] == '*');
  sz[u] = 1;

  pre[u].resize(adj[u].size());
  for(int i=0; i<adj[u].size(); i++) {
    int v = adj[u][i];
    solve_down(v);
    sz[u] += sz[v];
    combine(sum, mx, cnt, cur, dp[v], s[u] == '*');
    if(i == 0) {
      pre[u][i] = dp[v];
    } else {
      auto [_s, _m, _t, _c] = pre[u][i-1];
      combine(_s, _m, _t, _c, dp[v], s[u] == '*');
      pre[u][i] = make_tuple(_s, _m, _t, _c);
    }
  }

  suf[u].resize(adj[u].size());
  for(int i=(int)adj[u].size()-1; i>=0; i--) {
    int v = adj[u][i];
    if(i+1 == adj[u].size()) {
      suf[u][i] = dp[v];
    } else {
      auto [_s, _m, _t, _c] = suf[u][i+1];
      combine(_s, _m, _t, _c, dp[v], s[u] == '*');
      suf[u][i] = make_tuple(_s, _m, _t, _c);
    }
  }

  dp[u] = make_tuple(sum, mx, cnt, cur);
}

void solve_up(int u, int i) {
  int p = par[u];
  ll sum = 0;
  int mx = (s[p] == '*');
  int cnt = 1;
  int cur = (s[p] == '*');

  if(p > 1) combine(sum, mx, cnt, cur, up[p], s[p] == '*');
  if(i > 0) combine(sum, mx, cnt, cur, pre[p][i-1], s[p] == '*');
  if(i+1 < adj[p].size()) combine(sum, mx, cnt, cur, suf[p][i+1], s[p] == '*');
  up[u] = make_tuple(sum, mx, cnt, cur);

  for(int j=0; j<adj[u].size(); j++) {
    solve_up(adj[u][j], j);
  }
}

void casesolve() {

	int n, k;
  cin >> n >> k;

  for(int i=1; i<=n; i++) {
    cin >> s[i];
    adj[i].clear();
  }

  vector<int> e = read(n, k);
  for(int i=2; i<=n; i++) {
    //cerr<<"edge "<<i<<" "<<e[i]<<nl;
    adj[e[i]].push_back(i);
    par[i] = e[i];
  }
  solve_down(1);
  for(int i=0; i<adj[1].size(); i++) {
    solve_up(adj[1][i], i);
  }

  ll ans = -1;
  ll cnt = 0;
  for(int i=2; i<=n; i++) {
    // sum, max, cnt, cur
    ll cur = get<0>(dp[i]) + get<0>(up[i]) + (ll) get<1>(dp[i]) * get<1>(up[i]);
    if(cur > ans) {
      ans = cur;
      cnt = 0;
    }
    if(cur == ans) {
      if(get<1>(dp[i]) == 0 || get<1>(up[i]) == 0) {
        cnt += (ll)sz[i] * (n-sz[i]);
      } else {
        cnt += (ll) get<2>(dp[i]) * get<2>(up[i]);
      }
    }
  }

  cout << ans << " " << cnt << nl;

	return;
}


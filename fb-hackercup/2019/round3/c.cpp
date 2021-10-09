#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

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
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; 
  return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
  return os << '}';
}

////////////////////////////////////////////////////////////////////////

const int N = 6e3+1;
const int L = 15;
ll fact[N], invf[N];

ll power(ll b, ll e) {
  ll r = 1;
  for ( ; e>0; e/=2) {
    if (e&1) r = r*b % MOD;
    b = b*b % MOD;
  }
  return r;
}

ll inverse(ll n) {
  return power(n, MOD-2);
}

ll ncr(ll n, ll r) {
  if (r<0 || r>n) return 0;
  return fact[n] * invf[r] % MOD * invf[n-r] % MOD;
}

void solve();

void init() {
  fact[0] = invf[0] = 1;
  FOR(i,1,N-1) {
    fact[i] = i * fact[i-1] % MOD;
    invf[i] = inverse(fact[i]);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    solve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

ll p[N], d[N];
ll anc[N][L];
vector<int> adj[N];

void precomp(int u) {
  d[u] = d[p[u]]+1;
  anc[u][0] = p[u];
  FOR(j,1,L-1) {
    anc[u][j] = anc[anc[u][j-1]][j-1];
  }
  for (int v : adj[u]) {
    precomp(v);
  }
}

int lca(int a, int b) {
  if (d[a] < d[b]) {
    swap(a,b);
  }
  Down(j,L) {
    if (d[anc[a][j]] >= d[b]) {
      a = anc[a][j];
    }
  }
  if (a == b) return a;
  assert(d[a] == d[b]);
  Down(j,L) {
    if (anc[a][j] != anc[b][j]) {
      a = anc[a][j];
      b = anc[b][j];
    }
  }
  return anc[a][0];
}

void caseinit() {
  memset(anc, 0, sizeof anc);
  For(i,N) {
    adj[i].clear();
  }
}

void solve() {
  caseinit();

  int n, k, a, b;
  cin >> n >> k >> a >> b;
  ll invn = inverse(n-1);

  // keep, collapse
  function<ll(ll)> prob0 = [=] (ll x) {
    assert(x <= n-1);
    ll pgood = (n-1-x) * invn % MOD;
    return power(pgood, k);
  };
  function<ll(ll)> prob1 = [=] (ll x) {
    assert(x+1 <= n-1);
    ll r = (n-1-x-1) * inverse(n-1-x) % MOD;
    ll s = power(n-1-x, k-1) * power(invn, k) % MOD;
    ll res = s * (1-power(r,k)) % MOD * inverse(1-r) % MOD;
    return (res + MOD) % MOD;
  };
  function<ll(ll)> prob2 = [=] (ll x) {
    ll notone = 2 * prob1(x+1) % MOD;
    ll nottwo = prob0(x+2);
    ll total = prob0(x);
    return (total + MOD-notone + MOD-nottwo) % MOD;
  };

  FOR(i,2,n) {
    cin >> p[i];
    adj[p[i]].push_back(i);
  }
  precomp(1);
  int c = lca(a,b);

  // probability of not collapsing to lca
  ll plca = prob0(d[a]-d[c] + d[b]-d[c]);
  ll ans = plca * (d[a]-d[c] + d[b]-d[c]) % MOD;

  for (int u=a, i=0; u; u=p[u], i++) {
    for (int v=b, j=0; v; v=p[v], j++) {
      if (d[u]<=d[c] && d[v]<=d[c]) continue;
      if (u==1) {
        assert(v!=1);
        ans += prob1(i+j) * (i+j+1) % MOD;
      } else if (v==1) {
        ans += prob1(i+j) * (i+j+1) % MOD;
      } else {
        ans += prob2(i+j) * (i+j+2) % MOD;
      }
    }
  }
  cout << ans % MOD << nl;

  return;
}


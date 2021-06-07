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
random_device _rd; mt19937 rng(_rd());

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1e9+7;
constexpr ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ", " << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[ "; for (const T& it : v) { os << it << " , "; }
  return os << ']';
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " , "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " , "; }
  return os << '}';
}

template <class T, class U>
istream& operator >> (istream& is, pair<T,U>& v) {
  return is >> v.first >> v.second;
}
template <int i, class... Ts>
istream& read_tuple_impl(istream& is, tuple<Ts...>& v) {
  if constexpr (i == 0) return is;
  else return read_tuple_impl<i-1>(is, v) >> get<i-1>(v);
}
template <class... Ts>
istream& operator >> (istream& is, tuple<Ts...>& v) {
  return read_tuple_impl<sizeof...(Ts)>(is, v);
}

template <class T = int>
vector<T> read_array(int n, int s=0) {
  vector<T> a(n + 2*s);
  for(int i=0; i<n; i++) {
    cin >> a[s+i];
  }
  return a;
}

template <class T = int>
vector<vector<T>> read_grid(int n, int m, int s=0, int t=0) {
  vector a(n + 2*s, vector<T>(m + 2*t));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[s+i][t+j];
    }
  }
  return a;
}

void solve_case();
void initialize();

////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  initialize();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    auto start = chrono::steady_clock::now();
    cout << "Case #" << cc << ": ";
    solve_case();
    if(argc > 1 && argv[1][0] == 't') {
      cerr << "Time: " << (chrono::steady_clock::now() - start) / 1.0s << "s" << nl << nl;
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

ll ncr(int, int);
ll interleave(int a, int b) {
  return ncr(a + b, b);
}

void solve_case() {

  int n;
  cin >> n;
  bool ok = true;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    ok &= (1 <= a[i] && a[i] <= n);
    ok &= (a[i] - a[i-1] <= 1);
  }
  if(!ok) {
    cout << 0 << nl;
    return;
  }

  vector<int> par(n+1), stk;
  stk.push_back(0);
  for(int i=1; i<=n; i++) {
    if(a[i] > a[i-1]) {
      par[i] = stk.back();
      stk.push_back(i);
    } else {
      for(int j=0; j<a[i-1]-a[i]; j++) {
        stk.pop_back();
      }
      par[stk.back()] = i;
      stk.pop_back();
      par[i] = stk.back();
      stk.push_back(i);
    }
  }

  vector<int> deg(n+1), cnt(n+1);
  vector<ll> val(n+1, 1);
  for(int i=1; i<=n; i++) {
    deg[par[i]]++;
  }

  queue<int> bfs;
  for(int i=1; i<=n; i++) {
    if(deg[i] == 0) {
      bfs.push(i);
    }
  }
  while(!empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    if(u == 0) break;
    cnt[u]++;
    ll add = val[u] * interleave(cnt[u], cnt[par[u]]) % MOD;
    val[par[u]] = val[par[u]] * add % MOD;
    cnt[par[u]] += cnt[u];
    if(--deg[par[u]] == 0) {
      bfs.push(par[u]);
    }
  }

  cout << val[0] << nl;

  return;
}

const int N = 2e5 + 7;
ll fact[N], invf[N];

ll modpow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  } return r;
}

ll ncr(int n, int r) {
  if(r<0 || n<r) return 0;
  return fact[n] * invf[r] % MOD * invf[n-r] % MOD;
}

void initialize() {
  fact[0] = invf[0] = 1;
  for(int i=1; i<N; i++) {
    fact[i] = fact[i-1] * i % MOD;
    invf[i] = modpow(fact[i], MOD - 2, MOD);
  }
}


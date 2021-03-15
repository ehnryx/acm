//#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9 + 7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  int n, m, k, p, x;
  cin >> n >> m >> k >> p >> x;
  int h = k/2;
  vector<int> tens(k+1, 1);
  for(int i=1; i<=k; i++) {
    tens[i] = tens[i-1] * 10;
  }

  vector<tuple<int,int,int>> edges;
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges.emplace_back(a, b, c);
  }

  vector forward(n+1, vector<ll>(tens[k-h]));
  vector backward(n+1, vector<ll>(tens[h]));
  for(int i=1; i<=n; i++) {
    forward[i][0] = backward[i][0] = 1;
  }

  for(int t=0; t<k-h; t++) {
    vector nf(n+1, vector<ll>(tens[k-h]));
    for(auto [a, b, c] : edges) {
      for(int v=0; v<tens[k-h]; v++) {
        if(forward[a][v]) {
          int key = v*10 + c;
          nf[b][key] = (nf[b][key] + forward[a][v]) % MOD;
        }
      }
    }
    forward = move(nf);
  }

  for(int t=0; t<h; t++) {
    vector nb(n+1, vector<ll>(tens[h]));
    for(auto [a, b, c] : edges) {
      for(int v=0; v<tens[h]; v++) {
        if(backward[b][v]) {
          int key = tens[t]*c + v;
          nb[a][key] = (nb[a][key] + backward[b][v]) % MOD;
        }
      }
    }
    backward = move(nb);
  }

  for(int i=1; i<=n; i++) {
    for(int v=0; v<tens[h]; v++) {
      if(v >= p) {
        backward[i][v%p] += backward[i][v];
      }
    }
  }

  ll ans = 0;
  for(int i=1; i<=n; i++) {
    for(int v=0; v<tens[k-h]; v++) {
      int key = (x + p - (v * tens[h] % p)) % p;
      if(key < tens[h]) {
        ans += forward[i][v] * backward[i][key] % MOD;
      }
    }
  }
  cout << ans % MOD << nl;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ": ";
    solve();
  }

  return 0;
}

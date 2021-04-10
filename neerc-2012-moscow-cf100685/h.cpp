//#pragma GCC optimize("O3")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 4e3 + 1;
ld fact[N], D[N], C[N];

ld choose(int n, int r) {
  assert(0 <= r && r <= n);
  return fact[n] - fact[r] - fact[n-r];
}

ld cyc(int n) {
  assert(n > 1);
  return C[n];
}

ld der(int n) {
  assert(n != 1);
  return D[n];
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

  for(int i=1; i<N; i++) {
    fact[i] = fact[i-1] + log((ld)i);
    if(i>1) C[i] = fact[i-1] - fact[i];
    D[i] = log(exp(D[i-1]) + (i%2 ? -1 : 1) * exp(-fact[i]));
  }

  int T;
  cin >> T;
  while(T--) {
    int n, cost;
    cin >> n >> cost;

    vector<int> dsu(n, -1);
    vector<int> sz(n, 1);
    vector<int> edges(n, 0);
    function<int(int)> find = [&](int i) {
      if(dsu[i] == -1) return i;
      return dsu[i] = find(dsu[i]);
    };
    function<void(int,int)> link = [&](int i, int j) {
      i = find(i); j = find(j);
      if(i == j) {
        edges[j]++;
      } else {
        dsu[i] = j;
        sz[j] += sz[i];
        edges[j] += edges[i] + 1;
      }
    };

    for(int i=0; i<n; i++) {
      int a;
      cin >> a;
      if(a--) {
        link(i, a);
      }
    }

    int m = 0;
    int f = 0;
    int done = 0;
    for(int i=0; i<n; i++) {
      if(i == find(i)) {
        m++;
        if(sz[i] > 1) {
          if(edges[i] < sz[i]) {
            f++;
          } else {
            done++;
            m--;
          }
        }
      }
    }
    swap(n, m);

    ld bot = 0;
    for(int k=0; k<=f; k++) {
      if(n-k != 1) bot += exp(choose(f, k) + der(n-k) + fact[n-k] - fact[n]);
    }

    ld top = 0;
    for(int j=0; j<=n; j++) {
      if(j != 1 && n-j > 1) top += exp(der(j) + cyc(n-j));
    }
    for(int k=1; k<=f; k++) {
      for(int j=0; j<=n-k; j++) {
        if(j != 1 && n-k-j > 1) top += exp(choose(f, k) + der(j) + cyc(n-k-j) + fact[n-k] - fact[n]);
        if(j+k == n && j != 1) {
          top += exp(choose(f, k) + der(j) + fact[n-k] - fact[n]) * k;
        }
      }
    }

    cout << (top/bot + done) * cost << nl;
  }

  return 0;
}

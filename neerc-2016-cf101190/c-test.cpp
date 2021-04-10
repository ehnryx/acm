//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME sadcactus

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

const int N = 1e5 + 1;
int dsu[N], col[N];
int find(int i) {
  if(dsu[i] == 0) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  i = find(i); j = find(j);
  if(i != j) dsu[i] = j;
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

  for(int i=1; i<=100; i++) {
    col[i] = 1;
  }

  vector<pair<int,int>> edges;

  int n;
  cin >> n;
  while(n--) {
    char t;
    cin >> t;
    if(t == 'j') {
      int a, b;
      cin >> a >> b;
      link(a, b);
    } else if(t == 'r') {
      int a, b, c;
      cin >> a >> b >> c;
      for(int i=1; i<=100; i++) {
        if(find(i) == find(a) && col[i] == b) {
          col[i] = c;
        }
      }
    } else {
      assert(t == 'c');
      int a, b, c;
      cin >> a >> b >> c;
      assert(b != c);
      for(int i=1; i<=100; i++) {
        for(int j=1; j<=100; j++) {
          if(find(i) == find(a) && find(j) == find(a) && col[i] == b && col[j] == c) {
            edges.emplace_back(i, j);
          }
        }
      }
    }
  }

  cout << edges.size() << " edges" << nl;
  for(auto [a, b] : edges) {
    cout << a << " " << b << nl;
  }

  return 0;
}

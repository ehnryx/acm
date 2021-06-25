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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int M = 160;
vector<bitset<M>> read(int n, int k) {
  vector<bitset<M>> a;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    bitset<M> cur;
    for(int j=0; j<4*k; j++) {
      cur[j] = stoi(s.substr(j/4, 1), 0, 16) >> (j%4) & 1;
    }
    a.push_back(cur);
  }
  return a;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m, k;
  cin >> n >> m >> k;
  auto b = read(n, k);
  auto a = read(m, k);
  k *= 4;

  vector<pair<int,int>> order;
  for(int i=0; i<n; i++) {
    bool nonzero = false;
    for(int j=0; j<k; j++) {
      if(b[i][j]) {
        order.emplace_back(i, j);
        nonzero = true;
        break;
      }
    }
    if(nonzero) {
      for(int j=i+1; j<n; j++) {
        if(b[j][order.back().second]) {
          b[j] = b[j] ^ b[i];
        }
      }
    }
  }

  for(int i=0; i<m; i++) {
    int last = -1;
    for(auto [j, t] : order) {
      if(a[i][t]) {
        a[i] = a[i] ^ b[j];
        last = j + 1;
      }
    }
    if(a[i].count()) {
      last = -1;
    }
    cout << last << nl;
  }

  return 0;
}

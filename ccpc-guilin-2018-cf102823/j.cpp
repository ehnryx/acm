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

  int T;
  cin >> T;
  for(int testnum=1; testnum<=T; testnum++) {
    cout << "Case " << testnum << ": ";
    int n;
    cin >> n;
    vector<int> a(n+2);
    for(int i=1; i<=n; i++) {
      cin >> a[i];
    }
    a[0] = a[n+1] = INF;

    vector<int> res(n+2, -1);
    priority_queue<pair<int,int>> nxt;
    for(int i=1; i<=n; i++) {
      if(a[i] < a[i+1] && a[i] < a[i-1]) {
        nxt.emplace(0, i);
      }
    }
    while(!nxt.empty()) {
      auto [v, i] = nxt.top();
      nxt.pop();
      if(v <= res[i]) continue;
      res[i] = v;
      if(i > 1 && a[i-1] > a[i]) {
        nxt.emplace(v+1, i-1);
      }
      if(i < n && a[i+1] > a[i]) {
        nxt.emplace(v+1, i+1);
      }
    }

    int diff = 0;
    for(int i=1; i<=n; i++) {
      assert(a[i] >= res[i]);
      diff += (a[i] - res[i]) % 2;
    }
    if(diff % 2 == 0) {
      cout << "Bob" << nl;
    } else {
      cout << "Alice" << nl;
    }
  }

  return 0;
}

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

  int n;
  cin >> n;
  int m;
  cin >> m;
  vector adj(m, vector<tuple<int,int,int>>(2));
  for(int i=0; i<2*m; i++) {
    int s, in, t, out, d;
    cin >> s >> in >> t >> out >> d;
    adj[s][in] = tuple(t, out, d);
  }

  function<int(int)> run = [=](int bm) {
    int s = 0;
    int i = 0;
    for(int j=0; j<n && s!=-1; j++) {
      int in = bm >> i & 1;
      auto [t, out, d] = adj[s][in];
      s = t;
      bm ^= in << i ^ out << i;
      i += (d ? 1 : -1);
      if(i < 0) i = 0;
    }
    return s;
  };

  for(int bm=0; bm<1<<n; bm++) {
    if(run(bm) != -1) {
      cout << 0 << nl;
      return 0;
    }
  }
  cout << 1 << nl;

  return 0;
}

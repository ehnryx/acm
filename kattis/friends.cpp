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

const int N = 128;
bitset<N> adj[N];
unordered_set<bitset<N>> maxs[N];

void add_to_set(unordered_set<bitset<N>>& s, const bitset<N>& bm) {
  bool ok = true;
  for(auto om = s.begin(); om != s.end(); ) {
    bitset<N> it = *om & bm;
    if(it == *om) {
      om = s.erase(om);
    } else if(it == bm) {
      ok = false;
      break;
    } else {
      om++;
    }
  }
  if(ok) {
    s.insert(bm);
  }
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

  for(int n, m; cin >> n >> m; ) {
    vector<int> remap(n);
    iota(remap.begin(), remap.end(), 0);
    shuffle(remap.begin(), remap.end(), rng);

    for(int i=0; i<n; i++) {
      adj[i].reset();
      adj[i].set(i);
      maxs[i].clear();
    }

    for(int i=0; i<m; i++) {
      int a, b;
      cin >> a >> b;
      a = remap[a-1];
      b = remap[b-1];
      adj[a].set(b);
      adj[b].set(a);
    }

    maxs[0].insert(bitset<N>(1));
    for(int i=1; i<n; i++) {
      for(bitset<N> bm : maxs[i-1]) {
        bitset<N> nbs = bm & adj[i];
        if(nbs == bm) {
          bm.set(i);
          add_to_set(maxs[i], bm);
        } else {
          nbs.set(i);
          add_to_set(maxs[i], nbs);
          add_to_set(maxs[i], bm);
        }
      }
      if(maxs[i].size() > 1000) break;
    }

    if(maxs[n-1].empty() || maxs[n-1].size() > 1000) {
      cout << "Too many maximal sets of friends." << nl;
    } else {
      cout << maxs[n-1].size() << nl;
    }
  }

  return 0;
}

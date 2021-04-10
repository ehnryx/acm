#pragma GCC optimize("O3")
#pragma GCC target("avx,sse4")

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
random_device _rd; mt19937 rng(_rd());

const int N = 10;
int country[N], league[N], team[N], cnt[N], deg[N], a[N*N], b[N*N];

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

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    cin >> a[i] >> b[i];
    deg[a[i]]++;
    deg[b[i]]++;
  }

  unordered_map<string, int> remap;
  for(int i=0, rid=0; i<N; i++) {
    string s;
    cin >> s;
    cin >> s; if(!remap.count(s)) remap[s] = rid++;
    country[i] = remap[s];
    cin >> s; if(!remap.count(s)) remap[s] = rid++;
    league[i] = remap[s];
    cin >> s; if(!remap.count(s)) remap[s] = rid++;
    team[i] = remap[s];
  }

  vector<int> o(N);
  iota(begin(o), end(o), 0);
  do {
    memset(cnt, 0, sizeof cnt);
    for(int i=0; i<m; i++) {
      for(int r=0; r<2; r++) {
        cnt[a[i]] += (country[o[a[i]]] == country[o[b[i]]]);
        cnt[a[i]] += (league[o[a[i]]] == league[o[b[i]]]);
        cnt[a[i]] += (team[o[a[i]]] == team[o[b[i]]]);
        swap(a[i], b[i]);
      }
    }
    bool ok = true;
    for(int i=0; i<N; i++) {
      ok &= (cnt[i] >= deg[i]);
    }
    if(ok) {
      cout << "yes" << nl;
      return 0;
    }
  } while(next_permutation(begin(o), end(o)));

  cout << "no" << nl;

  return 0;
}

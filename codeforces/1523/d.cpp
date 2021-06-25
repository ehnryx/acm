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
  vector<ll> a(n);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    a[i] = stoll(s, 0, 2);
  }

  int ans = 0;
  int out = 0;
  int iterations = 0;
  while(clock()<2.91*CLOCKS_PER_SEC) {
    static const int magic = 3;
    int cover = (1<<m) - 1;
    for(int i=0; i<magic; i++) {
      cover &= a[rng()%n];
    }
    int bits = __builtin_popcountll(cover);
    if(bits <= ans) continue;
    ll bm = 0;
    while(__builtin_popcountll(bm) <= ans) {
      bm = 0;
      for(int i=0; i<m; i++) {
        if(!(cover >> i & 1)) continue;
        if(rng() % bits <= ans) {
          bm |= 1LL << i;
        }
      }
    }
    //if(__builtin_popcountll(bm) <= ans) continue;
    int cnt = 0;
    for(int i=0; i<n && cnt<(n+1)/2; i++) {
      cnt += ((bm & a[i]) == bm);
    }
    if(cnt >= (n+1)/2) {
      ans = __builtin_popcountll(bm);
      out = bm;
    }
    iterations++;
  }

  for(int i=m-1; i>=0; i--) {
    cout << (out >> i & 1);
  }
  cout << nl;

  //cerr << "iterations: " << iterations << nl;

  return 0;
}

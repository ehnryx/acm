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

  int n;
  cin >> n;
  vector<int> a(2*n), b(2*n);
  for(int i=0; i<2*n; i++) {
    cin >> a[i];
  }
  for(int i=0; i<2*n; i++) {
    cin >> b[i];
  }

  int score = 0;
  vector<bool> done(2*n), seen(2*n);
  vector<int> matched;
  for(int ai=0, bi=0, dir=1; ai<2*n && bi<2*n; ) {
    if(!matched.empty()) {
      score += dir * size(matched);
      for(int v : matched) {
        done[v] = true;
      }
      matched.clear();
      continue;
    }

    int first = a[ai++] / 2;
    while(ai < 2*n && done[first]) {
      first = a[ai++] / 2;
    }
    if(ai == 2*n && done[first]) {
      break;
    }

    if(seen[first]) {
      score += dir;
      done[first] = true;
      continue;
    }

    int second = a[ai++] / 2;
    while(ai < 2*n && done[second]) {
      second = a[ai++] / 2;
    }
    if(ai == 2*n && done[second]) {
      assert(false);
    }

    if(second == first) {
      score += dir;
      done[second] = true;
      continue;
    }

    if(seen[second]) {
      matched.push_back(second);
    }
    seen[first] = seen[second] = true;
    swap(a, b);
    swap(ai, bi);
    dir *= -1;
  }

  if(score > 0) {
    cout << 0 << nl;
  } else if(score < 0) {
    cout << 1 << nl;
  } else {
    cout << -1 << nl;
  }

  return 0;
}

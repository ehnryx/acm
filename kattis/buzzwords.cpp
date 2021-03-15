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

  for(string line; getline(cin, line) && !line.empty(); ) {
    string arr;
    for(char c : line) {
      if(!isspace(c)) {
        arr.push_back(c);
      }
    }

    int n = arr.size();
    vector<map<pair<int,int>,int>> cnt(n);
    for(int i=0; i<n; i++) {
      static const int p1 = 37, p2 = 101;
      static const int m1 = 1e9 + 7, m2 = 1e9 + 9;
      ll h1 = 0, h2 = 0;
      for(int j=i; j<n; j++) {
        h1 = (h1 * p1 + arr[j]) % m1;
        h2 = (h2 * p2 + arr[j]) % m2;
        cnt[j - i][pair(h1, h2)] += 1;
      }
    }

    for(int i=0; i<n; i++) {
      int best = 0;
      for(auto [_, c] : cnt[i]) {
        best = max(best, c);
      }
      if(best == 1) break;
      cout << best << nl;
    }
    cout << nl;
  }

  return 0;
}

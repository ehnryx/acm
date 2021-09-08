#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

void output(const vector<string>& g) {
  int done = 0;
  for(const string& s : g) {
    int cur = count(begin(s), end(s), '*');
    for(int i=0; i<s.size(); i++) {
      if(i < (int)s.size()-done-cur || (int)s.size()-done <= i) {
        cout << '.';
      } else {
        cout << '*';
      }
    }
    cout << nl;
    done += cur;
  }
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

  vector<string> all;
  for(string s; getline(cin, s); ) {
    if(!empty(s)) {
      all.push_back(s);
      continue;
    }
    output(all);
    cout << nl;
    all.clear();
  }

  if(!empty(all)) {
    output(all);
  }

  return 0;
}

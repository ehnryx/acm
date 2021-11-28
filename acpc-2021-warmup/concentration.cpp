#include <bits/stdc++.h>
using namespace std;

#include "../../lca/misc/fast_input.h"
#include "../../lca/data_structure/splay_tree.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int n;
  cin >> n;
  splay_tree<splay_node<void, int>> a(2*n), b(2*n);
  for(int i=0; i<2*n; i++) {
    cin >> a[i];
  }
  for(int i=0; i<2*n; i++) {
    cin >> b[i];
  }

  splay_tree<splay_node<int, void>> seen;
  vector<int> ans(2);
  for(int i=0, paired=0; ans[0]+ans[1] < n; i++) {
    int before = ans[i % 2];
    if(paired) {
      paired--;
      ans[i % 2]++;
    } else {
      int r = *a.begin();
      a.pop_front();
      while(seen.contains(r)) {
        r = *a.begin();
        a.pop_front();
      }
      seen.insert(r);
      if(seen.contains(r^1)) {
        ans[i % 2]++;
      } else {
        int memo = r;
        r = *a.begin();
        a.pop_front();
        while(seen.contains(r)) {
          r = *a.begin();
          a.pop_front();
        }
        seen.insert(r);
        if(memo == (r^1)) {
          ans[i % 2]++;
        } else if(seen.contains(r^1)) {
          paired++;
        }
      }
    }
    if(ans[i % 2] == before) {
      swap(a, b);
    } else {
      i--;
    }
  }

  cout << (ans[0] > ans[1] ? 0 : ans[0] < ans[1] ? 1 : -1) << nl;

  return 0;
}

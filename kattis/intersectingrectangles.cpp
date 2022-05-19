#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"
//%:include "data_structure/segment_tree.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

/*
struct node {
  int sum;
  node() = default;
  void put(int v) { sum += v; }
  int get() const { return sum; }
  void pull(const node& a, const node& b) {
    sum = a.sum + b.sum;
  }
  static int merge(int a, int b) { return a + b; }
};
*/

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  vector<tuple<int, int, int, int>> ev;
  //map<int, int> remap;
  for(int i=0; i<n; i++) {
    pair<int, int> a, b;
    cin >> a >> b;
    ev.emplace_back(a.first, a.second, b.second, 1);
    ev.emplace_back(b.first, a.second, b.second, -1);
    //remap[a.second];
    //remap[b.second];
  }
  sort(begin(ev), end(ev));

  /*
  int rid = 0;
  for(auto& it : remap) {
    it.second = rid++;
  }

  segment_tree<node, int> st(rid);
  static_assert(st.has_pull);
  int ans = 0;
  for(auto [_, a, b, t] : ev) {
    if(t > 0) {
      ans |= st.query(remap[a], remap[b]);
    }
    st.update_point(remap[a], t);
    st.update_point(remap[b], t);
    if(t < 0) {
      ans |= st.query(remap[a], remap[b]);
    }
  }

  cout << !!ans << nl;
  */

  set<int> st;
  for(auto [_, a, b, t] : ev) {
    if(st.upper_bound(a) != st.lower_bound(b)) {
      cout << 1 << nl;
      return 0;
    }
    if(t > 0) {
      st.insert(a);
      st.insert(b);
    } else {
      st.erase(a);
      st.erase(b);
    }
  }
  cout << 0 << nl;

  return 0;
}

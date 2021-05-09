#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"
#include "../../lca/number/mod_int.h"

constexpr char nl = '\n';
using Int = mod_int<(int)1e9+7>

struct Node {
  Int value;
  Node(): value(1) {}
  void put(Int v) { value *= v; }
  Int get() const { return value; }
  void push(Node&, Node&) {}
  void pull(const Node& a, const Node& b) { value = a.value * b.value; }
  static Int default_value() { assert(false); }
  static Int merge(Int a, Int b) { return a * b; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  int m;
  cin >> m;
  vector<Int> ans(m);
  vector<tuple<int,int,int>> queries;
  for(int i=0; i<m; i++) {
    int l, r;
    cin >> l >> r;
    queries.emplace_back(l, r, i);
  }
  sort(begin(queries), end(queries), greater<>());

  int len = *max_element(begin(a), end(a)) + 1;
  vector<int> last(len);
  vector<Int> inv(len);
  for(int i=1; i<len; i++) {
    //inv[i] = Int(i).pow(-1);
    inv[i] = Int(i).inverse();
  }

  segment_tree<Node, Int> st(n+1);
  int pos = n;
  for(auto [l, r, i] : queries) {
    while(pos >= l) {
      for(int v=2; v*v<=a[pos]; v++) {
        if(a[pos] % v) continue;
        int cnt = 0;
        while(a[pos] % v == 0) {
          a[pos] /= v;
          cnt += 1;
        }
        if(last[v]) st.update_point(last[v], inv[v-1] * v);
        st.update_point(last[v] = pos, Int(v).pow(cnt-1) * (v-1));
      }
      if(a[pos] > 1) {
        if(last[a[pos]]) st.update_point(last[a[pos]], inv[a[pos]-1] * a[pos]);
        st.update_point(last[a[pos]] = pos, a[pos] - 1);
      }
      pos--;
    }
    ans[i] = st.query(l, r);
  }

  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"
#include "../../lca/number/square_matrix.h"
#include "../../lca/number/mod_int.h"

constexpr char nl = '\n';
using Int = mod_int<(int)1e9 + 9>;
using Matrix = square_matrix<Int, 2>;

const int N = 3e5 + 7;
Matrix fmat[N];
const Matrix one(1), zero(0);
const Matrix invf({
  { 0, -1 },
  {-1, -1 },
});
const Matrix fib({
  { 0,  1 },
  { 1,  1 },
});

struct Node {
  Matrix base, lazy;
  Int value;
  bool flag;
  int start, length;
  Node(): base(0), lazy(0), value(0), flag(false), start(0), length(0) {}
  void put(int l) {
    add(fmat[start - l + 1]);
  }
  void add(const Matrix& m) {
    base += m;
    lazy += m;
    value += (m * (one - fmat[length]) * invf)[0][1];
    flag = true;
  }
  void push(Node& l, Node& r) {
    if (flag) {
      l.add(lazy);
      r.add(lazy * fmat[length / 2]);
      lazy = zero;
      flag = false;
    }
  }
  Int get() const {
    return value;
  }
  void pull(const Node& a, const Node& b) { value = a.value + b.value; }
  static Int default_value() { assert(false); }
  static Int merge(const Int& a, const Int& b) { return a + b; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  fmat[0] = one;
  for (int i = 1; i < N; i++) {
    fmat[i] = fmat[i - 1] * fib;
  }

  int n, m;
  cin >> n >> m;
  vector<Int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  partial_sum(begin(a), end(a), begin(a));

  segment_tree<Node, Int> st(n + 1);
  for (int i = 0; i < st.length; i++) {
    st[i + st.length].start = i;
    st[i + st.length].length = 1;
  }
  for (int i = st.length - 1; i > 0; i--) {
    st[i].start = st[2 * i].start;
    st[i].length = st[2 * i].length + st[2 * i + 1].length;
  }

  for (int i = 0; i < m; i++) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 1) {
      st.update(l, r, l);
    } else {
      Int ans = a[r] - a[l - 1] + st.query(l, r);
      cout << ans << nl;
    }
  }

  return 0;
}

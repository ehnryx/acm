#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

using ld = long double;
using pt = complex<ld>;
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-9;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  ld lower, upper;
  lower = 0;
  upper = 1;

  splay_tree<splay_node<void, int>> a(n), b(n);
  for (int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
    if (a[i] < b[i]) swap(a[i], b[i]);
    if (i > 0) {
      if (a[i] == a[i-1] && b[i] == b[i-1]) continue;
      if (a[i] == a[i-1] && b[i] > b[i-1]) lower = 1;
      if (a[i] > a[i-1] && b[i] == b[i-1]) upper = 0;
      if (a[i] > a[i-1] && b[i] > b[i-1]) lower = INF;
    }
  }

  for (int i=1; i<n; i++) {
    if (a[i]-b[i] == a[i-1]-b[i-1]) continue;

    ld yval = line_inter(pt(i,a[i]), pt(i-1,a[i-1]), pt(i,b[i]), pt(i-1,b[i-1])).imag();
    if (a[i]-b[i] > a[i-1]-b[i-1]) {
      upper = min(upper, (yval-b[i])/(a[i]-b[i]));
    } else {
      lower = max(lower, (yval-b[i-1])/(a[i-1]-b[i-1]));
    }
  }

  if (lower < upper+EPS) cout << "YES" << nl;
  else cout << "NO" << nl;

  return 0;
}

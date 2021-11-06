#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

int splay_min(int a, int b) {
  splay_tree<splay_node<int, void>> st;
  st.insert(a);
  st.insert(b);
  assert(st.begin() == ++st.rbegin());
  assert(st.begin() == st.begin());
  assert(st.rbegin() == st.rbegin());
  return *++st.rbegin();
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int p, n, x;
  cin >> p >> n >> x;

  int ans = x/p + x%p;
  if (p*(x/p+1) > n) ans = splay_min(ans, x/p+1 + n-x);
  else ans = splay_min(ans, x/p+1 + p-(x%p));

  int other = n/p+1 + splay_min((n-x)/p + (n-x)%p, (n-x)/p+1 + p-(n-x)%p);

  cout << splay_min(ans, other) << nl;

  return 0;
}

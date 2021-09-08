#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/data_structure/splay_tree.h"
using node = splay_node_comparable<int>;

constexpr char nl = '\n';
using ll = long long;
int T = -1;

int main() {
  if(T < 0) { cin.tie(0)->sync_with_stdio(0); cin >> T; }
  if(--T) main();

  int n;
  cin >> n;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  vector<int> small(n), big(n);
  splay_tree<node> hs, hb;
  for(int i=0, j=1; i<n; i++) {
    while(j <= a[i]) {
      hs.insert(new node(j));
      hb.insert(new node(j));
      j++;
    }

    if(i == 0 || a[i] != a[i-1]) {
      small[i] = big[i] = a[i];
      hs.erase(hs.find(a[i]));
      hb.erase(hb.find(a[i]));
    } else {
      small[i] = hs.begin()->key;
      hs.erase(hs.begin().ptr);
      big[i] = splay_tree<node>::walk_right(hb.root)->key;
      hb.erase(splay_tree<node>::walk_right(hb.root));
    }
  }

  for(int it : small) {
    cout << it << " ";
  }
  cout << nl;
  for(int it : big) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

using ll = long long;

struct Q {
  int id;
  int cur;
  int prev;
  int cnt;
  Q(){}
  Q(int i, int nxt, int pre = 0, int cnt = 0):
    id(i), cur(nxt), prev(pre), cnt(cnt) {}
  bool operator < (const Q& v) const {
    if (value() == v.value()) return id > v.id;
    else return value() > v.value();
  }
  ll value() const {
    if (prev) return cnt*(cur+prev);
    else return cnt*(2*cur);
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;

  splay_tree<splay_node<void, int>> arr(n);
  for (int i=0; i<n; i++) {
    cin >> arr.at(i)->value;
  }

  splay_tree<splay_node<Q, void>> q;
  for (int i=1; i<=k; i++) {
    q.insert(Q(i,0));
  }

  splay_tree<splay_node<void, int>> ans(n);
  for (int i=0; i<n; i++) {
    Q cur = *q.rbegin(); q.erase(q.rbegin());
    ans.at(i)->value = cur.id;
    cur.prev = cur.cur;
    cur.cur = arr.at(i)->value;
    cur.cnt++;
    q.insert(cur);
  }

  for (int i=0; i<n; i++) {
    cout << ans.at(i)->value << " ";
  }
  cout << nl;

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

const int INF = 0x3f3f3f3f;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int x, y;
  cin >> x >> y;

  string dir;
  cin >> dir;

  int n;
  cin >> n;

  splay_tree<splay_node<int, string>> best;

  for (int i=0; i<n; i++) {
    string s;
    int a, b;
    cin >> s >> a >> b;
    a -= x;
    b -= y;

    int cur;
    if (dir == "LEFT") {
      a += (abs(b)+1)/2;
      if (a<0) cur = (abs(b)+1)/2 + (abs(a)+2)/3;
      else cur = (abs(b)+1)/2 + abs(a);
    } else if (dir == "RIGHT") {
      a -= (abs(b)+1)/2;
      if (a>0) cur = (abs(b)+1)/2 + (abs(a)+2)/3;
      else cur = (abs(b)+1)/2 + abs(a);
    } else if (dir == "UP") {
      b -= (abs(a)+1)/2;
      if (b>0) cur = (abs(a)+1)/2 + (abs(b)+2)/3;
      else cur = (abs(a)+1)/2 + abs(b);
    } else {
      b += (abs(a)+1)/2;
      if (b<0) cur = (abs(a)+1)/2 + (abs(b)+2)/3;
      else cur = (abs(a)+1)/2 + abs(b);
    }

    best.insert(cur, s);
  }

  cout << best.begin()->value << nl;

  return 0;
}

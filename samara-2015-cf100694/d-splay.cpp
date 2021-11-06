#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

vector<vector<int>> three = {
  { 3, 4, 8 },
  { 2, 6 ,7 },
  { 1, 5, 9 }
};

vector<vector<int>> four = {
  { 2, 3, 10, 11 },
  { 1, 7, 8, 9 },
  { 4, 5, 6, 12 }
};

vector<vector<int>> five = {
  { 1, 3, 7, 14, 15 },
  { 2, 6, 10, 11, 13 },
  { 4, 5, 8, 9, 12 }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  int cur = 0;
  vector<splay_tree<splay_node<void, int>>> ans(3);

  if (n < 3) {
    cout << "FAIL" << nl;
    return 0;
  }

  cout << "WIN" << nl;

  while (n >= 6) {
    n -= 3;
    for (int i=0; i<3; i++) {
      for (int it : three[i]) {
        ans[i].push_back(cur + it);
      }
    }
    cur += 9;
  }

  if (n == 3) {
    for (int i=0; i<3; i++) {
      for (int it : three[i]) {
        ans[i].push_back(cur + it);
      }
    }
  }

  if (n == 4) {
    for (int i=0; i<3; i++) {
      for (int it : four[i]) {
        ans[i].push_back(cur + it);
      }
    }
  }

  if (n == 5) {
    for (int i=0; i<3; i++) {
      for (int it : five[i]) {
        ans[i].push_back(cur + it);
      }
    }
  }

  for (int i=0; i<3; i++) {
    for (int it : ans[i]) {
      cout << it << " ";
    }
    cout << nl;
  }

  return 0;
}

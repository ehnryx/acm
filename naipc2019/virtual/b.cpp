#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  string s[n], t[n];
  for (int i=0; i<n; i++) {
    cin >> s[i];
  }
  for (int i=0; i<n; i++) {
    cin >> t[i];
  }

  {
    bool bad = false;
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        if (t[i][j] != s[i][j]) {
          bad |= (t[i][j] != s[i][j]);
        }
      }
    }
    if (!bad) {
      cout << 1 << nl;
      return 0;
    }
  }

  set<int> badr, badc;
  for (int i=0; i<n; i++) {
    vector<int> cur;
    for (int j=0; j<m; j++) {
      if (t[i][j] == 'X') {
        cur.push_back(j);
      }
    }
    if (cur.size() > 1) {
      badr.insert(i);
      for (int j : cur) {
        badc.insert(j);
      }
    }
  }
  for (int j=0; j<m; j++) {
    vector<int> cur;
    for (int i=0; i<n; i++) {
      if (t[i][j] == 'X') {
        cur.push_back(i);
      }
    }
    if (cur.size() > 1) {
      badc.insert(j);
      for (int i : cur) {
        badr.insert(i);
      }
    }
  }

  bool diff = false;
  for (int i=0; i<n; i++) {
    if (badr.count(i)) continue;
    for (int j=0; j<m; j++) {
      if (badc.count(j)) continue;
      diff |= (t[i][j] == 'X');
    }
  }

  if (!diff) {
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        if (t[i][j] != s[i][j]) {
          cout << 0 << nl;
          return 0;
        }
      }
    }
    cout << 1 << nl;
  }

  else {
    for (int i:badr) {
      for (int j:badc) {
        if (s[i][j] != t[i][j]) {
          cout << 0 << nl;
          return 0;
        }
      }
    }
    bool up = false;
    for (int i=0; i<n; i++) {
      if (badr.count(i)) continue;
      for (int j=0; j<m; j++) {
        if (badc.count(j)) continue;
        up |= (s[i][j] == 'O');
      }
    }
    if (up) {
      cout << 1 << nl;
    } else {
      cout << 0 << nl;
    }
  }

  return 0;
}

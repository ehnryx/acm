#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T; cin >> T;
  for (int tt = 1; tt <= T; tt++) {
    cout << "Case #" << tt << ": ";
    int g; string s; cin >> g >> s;
    vector<vector<string>> teams(5, vector<string>(20));
    vector<string> ecf(20);
    for (auto& v : teams) for (auto& t : v) cin >> t;
    for (auto& t : ecf) cin >> t;
    for (int y = 0; y <= g; y++) {
      unordered_set<string> sent; int x = g - y;
      for (int place = 0; place < 20 && sent.size() < x; place++) {
        for (int i = 0; i < 5 && sent.size() < x; i++) {
          if (!sent.count(teams[i][place])) {
            sent.insert(teams[i][place]);
          }
        }
      }
      for (int i = 0; sent.size() < g && i < 20; i++) {
        if (!sent.count(ecf[i])) {
          sent.insert(ecf[i]);
        }
      }
      if (!sent.count(s)) {
        cout << y << nl;
        goto end;
      }
    }
    cout << "ADVANCED!\n";
    end:;
  }

  return 0;
}

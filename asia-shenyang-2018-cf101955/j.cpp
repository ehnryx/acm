#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const unordered_map<string, int> m = {
  {"char", 1},
  {"int", 4},
  {"long long", 8},
  {"__int128", 16},
  {"float", 4},
  {"double", 8},
  {"long double", 16},
  {"bool", 1}
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T; cin >> T;
  for (int tt = 1; tt <= T; tt++) {
    int n; cin >> n;
    string s; getline(cin, s);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      getline(cin, s);
      istringstream in(s);
      string type; in >> type;
      if (type == "long") {
        string t; in >> t;
        type += " " + t;
      }
      int size = m.at(type);
      getline(in, s, '[');
      int cnt = 0;
      in >> cnt;
      if (cnt) ans += size * cnt;
      else ans += size;
    }
    cout << "Case #" << tt << ": " << (ll)ceil(ans/1024.L) << nl;
  }

  return 0;
}

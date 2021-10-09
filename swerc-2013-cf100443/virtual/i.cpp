#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

#define nl '\n'

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<vector<string>> texts;
  vector<string> cur;
  unordered_map<string, int> m;
  int day = 0;
  string s;
  while (cin >> s) {
    if (s == "<text>") {
      day++;
      continue;
    }
    if (s == "</text>") {
      for (const string& s : cur) {
        m[s]++;
      }
      texts.emplace_back(move(cur));
      cur = {};
      if (texts.size() > 7) {
        for (const string& s : texts[texts.size()-8]) {
          if (!--m[s]) m.erase(s);
        }
      }
      continue;
    }
    if (s[0] == '<') {
      int n; cin >> n;
      vector<pair<string, int>> v(m.begin(), m.end());
      cout << "<top " << n << ">\n";
      sort(v.begin(), v.end(), [&](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second != b.second ? a.second > b.second : a.first < b.first;
      });
      if (v.size() < n) {
        for (const auto& p : v) {
          cout << p.first << " " << p.second << nl;
        }
      } else {
        int cnt = v[n-1].second;
        for (int i = 0; i < v.size() && v[i].second >= cnt; i++) {
          cout << v[i].first << " " << v[i].second << nl;
        }
      }
      cout << "</top>\n";
    } else {
      if (s.size() >= 4) {
        cur.emplace_back(move(s));
      }
    }
  }

  return 0;
}

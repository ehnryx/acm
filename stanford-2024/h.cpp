#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  string p;
  cin >> p;
  auto patterns = vector<string>();
  for (size_t i = 0;;) {
    size_t to = p.find('*', i);
    if (auto cur = p.substr(i, to - i); not cur.empty()) {
      patterns.push_back(cur);
    }
    if (to == p.npos) break;
    i = to + 1;
  }

  static constexpr int N = 2e5;
  auto indices = vector(size(patterns), bitset<N>());
  for (int i = 0; i < size(patterns); i++) {
    for (int j = 0; j < size(s); j++) {
      indices[i][j] = (s.substr(j, size(patterns[i])) == patterns[i]);
    }
  }

  auto valid = [&] {
    int start = -1;
    for (int i = 0; i < size(patterns); i++) {
      // find next match for patterns[i]
      auto it = (start == -1 ? indices[i]._Find_first() : indices[i]._Find_next(start));
      if (it == indices[i].size()) return false;  // no matches found
      start = it;
    }
    return true;
  };

  cout << (valid() ? "Yes" : "No") << nl;

  int q;
  cin >> q;
  for (int qi = 0; qi < q; qi++) {
    int at;
    char c;
    cin >> at >> c;
    at -= 1;
    s[at] = c;
    for (int i = 0; i < size(patterns); i++) {
      int lb = max(0, at - (int)size(patterns[i]) + 1);
      for (int j = lb; j <= at; j++) {
        indices[i][j] = (s.substr(j, size(patterns[i])) == patterns[i]);
      }
    }
    cout << (valid() ? "Yes" : "No") << nl;
  }

  return 0;
}

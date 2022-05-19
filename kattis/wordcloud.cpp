#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  for(int w, n, tt = 1; cin >> w >> n && n; tt++) {
    vector<pair<string, int>> words;
    int cmax = 0;
    for(int i=0; i<n; i++) {
      string s;
      int c;
      cin >> s >> c;
      words.emplace_back(s, c);
      cmax = max(cmax, c);
    }
    sort(begin(words), end(words));

    int height = 0;
    int at = 0;
    int curh = 0;
    for(const auto& [s, c] : words) {
      int p = 8 + (40 * (c - 4) + (cmax - 4) - 1) / (cmax - 4);
      int width = (9 * s.size() * p + 16 - 1) / 16;
      if (at + width > w) {
        height += curh;
        at = width + 10;
        curh = p;
      } else {
        at += width + 10;
        curh = max(curh, p);
      }
    }
    height += curh;
    cout << "CLOUD " << tt << ": " << height << nl;
  }

  return 0;
}

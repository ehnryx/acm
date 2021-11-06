%:include <bits/stdc++.h>
using namespace std;

#include "../../../lca/misc/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int T;
  cin >> T;
  vector<future<bool>> all;
  for (auto _ : views::iota(0) | views::take(T)) {
    string in;
    cin >> in;
    all.push_back(
        async(launch::async,
          [](const string& s) { return ranges::count(s, 'A') + ranges::count(s, 'C') == ranges::count(s, 'B'); },
          in));
  }
  for(auto& it : all) {
    cout << (it.get() ? "YES" : "NO") << nl;
  }

  return 0;
}

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

struct out_t {
  int a, b, c;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int T;
  cin >> T;
  for ([[maybe_unused]] auto _ : views::iota(0) | views::take(T)) {
    int n;
    cin >> n;
    vector<int> a(n);
    ranges::for_each(a, [&](int& v) { cin >> v; });
    vector<int> b = a;
    ranges::sort(b);
    vector<out_t> ans;
    for (int i : views::iota(0) | views::take(n)) {
      if (a[i] == b[i]) continue;
      auto tail = views::drop(a, i);
      auto it = ranges::find(tail, b[i]);
      ans.emplace_back(i + 1, n, distance(begin(tail), it));
      ranges::rotate(tail, it);
    }
    cout << size(ans) << nl;
    ranges::for_each(ans, [](const auto& v) { cout << v.a << " " << v.b << " " << v.c << nl; });
  }

  return 0;
}

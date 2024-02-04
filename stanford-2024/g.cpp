#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ll = long long;

auto square(ll x) -> ll {
  return x * x;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  auto weight = vector<int>(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> weight[i];
  }
  auto to = vector<int>(n + 1);
  auto from = vector<int>(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    to[a] = b;
    from[b] = a;
  }

  struct Item {
    int weight, idx;
    auto operator<(Item const& o) const -> bool { return weight < o.weight; }
  };

  vector<Item> in, out;
  for (int i = 1; i <= n; i++) {
    if (not from[i]) {
      in.emplace_back(weight[i], i);
    }
    if (not to[i]) {
      out.emplace_back(weight[i], i);
    }
  }
  sort(begin(in), end(in));
  sort(begin(out), end(out));

  auto cycle = [&](vector<int> const& cyc) {
    ll cost = 0;
    for (int i = size(cyc) - 1, j = 0; j < size(cyc); i = j++) {
      if (in[cyc[i]].idx == out[cyc[j]].idx) continue;
      cost += square(in[cyc[i]].weight + out[cyc[j]].weight);
    }
    return cost;
  };

  auto dp = vector<ll>(size(in) + 1);
  for (int i = 1; i <= size(in); i++) {
    dp[i] = dp[i - 1] + cycle({i - 1});
    if (i >= 2) {
      dp[i] = max(dp[i], dp[i - 2] + cycle({i - 1, i - 2}));
    }
    if (i >= 3) {
      dp[i] = max(dp[i], dp[i - 3] + cycle({i - 1, i - 2, i - 3}));
      dp[i] = max(dp[i], dp[i - 3] + cycle({i - 1, i - 3, i - 2}));
    }
  }
  cout << dp[size(in)] << nl;

  return 0;
}

#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

struct segment_tree {
  int n;
  vector<int> value, cover, length;
  segment_tree(int len): n(1 << __builtin_clz(len)),
    value(2 * n), cover(2 * n), length(2 * n, 1) {
    for (int i = n - 1; i > 0; i--) {
      length[i] = length[2 * i] + length[2 * i + 1];
    }
  }
  void apply(int i, int v) {
    cover[i] += v;
    pull(i);
  }
  void pull(int i) {
    if (i < n) {
      value[i] = (cover[i] ? length[i] : value[2 * i] + value[2 * i + 1]);
    } else {
      value[i] = (cover[i] ? length[i] : 0);
    }
  }
  void update(int l, int r, int v) {
    return update(l, r, v, 1, 0, n - 1);
  }
  void update(int l, int r, int v, int i, int s, int e) {
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
      return apply(i, v);
    }
    int m = (s + e) / 2;
    update(l, r, v, 2 * i, s, m);
    update(l, r, v, 2 * i + 1, m + 1, e);
    pull(i);
  }
};

ll solve(vector<tuple<int,int,int,int>>& segs) {
  sort(begin(segs), end(segs));
  segment_tree st(10'000 + 400 + 1);
  ll ans = 0;
  int lastx = 0;
  for (auto [x, l, r, v] : segs) {
    ans += (x - lastx) * st.value[1];
    st.update(l, r, v);
    lastx = x;
  }
  return ans;
}

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  vector<int> S(300'000 + 1);
  for (int i = 1; i < size(S); i++) {
    static const int mod = 1'000'000;
    if (i <= 55) {
      S[i] = 100'003 - (ll)200'003 * i % mod + (ll)300'007 * i % mod * i % mod * i % mod;
      S[i] = (S[i] % mod + mod) % mod;
    } else {
      S[i] = (S[i - 24] + S[i - 55]) % mod;
    }
  }

  int n;
  cin >> n;
  vector<int> x(n + 1), y(n + 1), z(n + 1), dx(n + 1), dy(n + 1), dz(n + 1);
  vector<vector<tuple<int,int,int,int>>> rects(10'000 + 400);
  for (int i = 1; i <= n; i++) {
    x[i] = S[6 * i - 5] % 10'000;
    y[i] = S[6 * i - 4] % 10'000;
    z[i] = S[6 * i - 3] % 10'000;
    dx[i] = 1 + (S[6 * i - 2] % 399);
    dy[i] = 1 + (S[6 * i - 1] % 399);
    dz[i] = 1 + (S[6 * i - 0] % 399);
    for (int j = z[i]; j < z[i] + dz[i]; j++) {
      rects[j].emplace_back(x[i], y[i], y[i] + dy[i] - 1, 1);
      rects[j].emplace_back(x[i] + dx[i], y[i], y[i] + dy[i] - 1, -1);
    }
  }

  ll ans = 0;
  for (auto& segs : rects) {
    if (empty(segs)) continue;
    ans += solve(segs);
  }
  cout << ans << nl;

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ll = long long;

struct SegmentTree {
  int const n;
  vector<ll> sum;
  SegmentTree(int _n)
      : n(_n <= 1 ? 1 : 1 << (32 - countl_zero((unsigned)_n - 1))), sum(2 * n) {}
  auto update(int i, int v) -> void {
    i += n;
    sum[i] += v;
    for (i /= 2; i > 0; i /= 2) {
      sum[i] = sum[2 * i] + sum[2 * i + 1];
    }
  }
  auto query(int l, int r) -> ll {
    ll res = 0;
    for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
      if (l % 2) res += sum[l++];
      if (r % 2) res += sum[--r];
    }
    return res;
  }
};
struct Event {
  int value, index, left, right;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  auto events = vector<Event>();
  for (int i = 1; i <= n; i++) {
    int val;
    cin >> val;
    events.emplace_back(val, i, -1, -1);
  }
  for (int i = 0; i < m; i++) {
    int l, r, val;
    cin >> l >> r >> val;
    events.emplace_back(val, i, l, r);
  }
  sort(events.begin(), events.end(), [](Event const& a, Event const& b) {
    return a.value > b.value;
  });

  auto ans = vector<ll>(m);
  auto count = SegmentTree(n + 1);
  auto sum = SegmentTree(n + 1);
  for (auto const& ev : events) {
    if (ev.right == -1) {
      sum.update(ev.index, ev.value);
      count.update(ev.index, 1);
    } else {
      ans[ev.index] = sum.query(ev.left, ev.right) - ev.value * count.query(ev.left, ev.right);
    }
  }

  for (int i = 0; i < m; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}

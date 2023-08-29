#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  int m;
  cin >> m;
  vector<tuple<int, int, int>> ev;
  for(int i=0; i<m; i++) {
    int l, r;
    cin >> l >> r;
    ev.emplace_back(l, r, i);
  }
  vector<int> ans(m);

  static constexpr int N = 1e5 + 1;
  static constexpr int S = 320;
  vector<int> block_cnt(N/S + 1);
  vector<int> val_cnt(N);
  vector<int> cnt(N);
  val_cnt[0] = N;
  block_cnt[0] = N;

  sort(begin(ev), end(ev), [](const auto& x, const auto& y) {
      int ga = get<0>(x) / S;
      int gb = get<0>(y) / S;
      if(ga != gb) return ga < gb;
      return (ga % 2 ? get<1>(x) < get<1>(y) : get<1>(y) < get<1>(x)); });

  auto update = [&](int i, int v) {
    val_cnt[cnt[a[i]]]--;
    block_cnt[cnt[a[i]]/S]--;
    cnt[a[i]] += v;
    val_cnt[cnt[a[i]]]++;
    block_cnt[cnt[a[i]]/S]++;
  };

  auto query = [&] {
    for(int i=size(block_cnt)-1; i>=0; i--) {
      if(block_cnt[i]) {
        for(int j=i*S+S-1; j>=i*S; j--) {
          if(val_cnt[j]) {
            return j;
          }
        }
      }
    }
    assert(false);
  };

  int x = 1;
  int y = 0;
  for(auto [l, r, i] : ev) {
    while(y < r) update(++y, 1);
    while(x > l) update(--x, 1);
    while(y > r) update(y--, -1);
    while(x < l) update(x++, -1);
    ans[i] = query();
  }

  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}

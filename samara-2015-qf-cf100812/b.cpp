#include <bits/stdc++.h>
using namespace std;

//#define FILENAME sadcactus

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  map<string, int> cnt;
  for(int i=0; i<n; i++) {
    string bs;
    cin >> bs;
    int on = count(begin(bs), end(bs), '1');
    if(8 <= on && on <= 15) {
      cnt[bs] += 1;
    }
  }

  if(empty(cnt)) {
    string out(m, '0');
    fill(begin(out), begin(out) + 8, '1');
    cout << out << nl;
    return 0;
  }

  pair<int, string> ans;
  for(const auto& [bs, c] : cnt) {
    if (c >= ans.first) {
      ans.first = c;
      ans.second = bs;
    }
  }

  cout << ans.second << nl;

  return 0;
}

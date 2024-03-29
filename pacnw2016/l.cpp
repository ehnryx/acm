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

using pt = complex<ld>;

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

struct pivot {
  const pt base;
  pivot(pt b): base(b) {}
  bool operator()(const auto& a, const auto& b) const {
    return cp(a.first - base, b.first - base) > 0;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<pair<pt, int>> p;
  for(int i=1; i<=n; i++) {
    int x, y;
    cin >> x >> y;
    p.emplace_back(pt(x, y), i);
  }
  sort(begin(p), end(p), pivot(0));

  string s;
  cin >> s;
  cout << p.front().second;
  for(int i=0; i<size(s); i++) {
    sort(begin(p) + i+1, end(p), pivot(p[i].first));
    if(s[i] == 'R') {
      reverse(begin(p) + i+1, end(p));
    }
    cout << " " << p[i+1].second;
  }
  cout << " " << p.back().second << nl;
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

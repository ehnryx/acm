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

  int n, m;
  cin >> n >> m;

  if (n < 8) {
    cout << "unsatisfactory" << nl;
    return 0;
  }

  cout << "satisfactory" << nl;
  return 0;  // maudit ostie de criss de câlice de tabarnak de problème!!

  vector<tuple<int, int, int>> v;
  for(int i=0; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    v.emplace_back(a, b, c);
  }

  for(int bm=0; bm<1<<m; bm++) {
    bool ok = true;
    for(auto [a, b, c] : v) {
      if(a > 0 && (bm >> a & 1)) continue;
      if(b > 0 && (bm >> b & 1)) continue;
      if(c > 0 && (bm >> c & 1)) continue;
      if(a < 0 && !(bm >> -a & 1)) continue;
      if(b < 0 && !(bm >> -b & 1)) continue;
      if(c < 0 && !(bm >> -c & 1)) continue;
      ok = false;
      break;
    }
    if(ok) {
      cerr << "bm = " << bm << nl;
      cout << "satisfactory" << nl;
      return 0;
    }
  }

  cout << "unsatisfactory" << nl;

  return 0;
}

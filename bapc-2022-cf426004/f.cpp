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

auto get(const string& s) {
  if(size(s) == 1) {
    if(s == "N") return 90.L;
    if(s == "S") return -90.L;
    if(s == "E") return 0.L;
    if(s == "W") return 180.L;
    assert(false);
  }
  auto dir = s.substr(size(s) - 2);
  auto step = 45.L / 2;
  if(dir == "NW") {
    auto at = 135.L;
    for(int i=(int)size(s)-3; i>=0; i--) {
      if(s[i] == 'N') {
        at -= step;
      } else {
        at += step;
      }
      step /= 2;
    }
    return at;
  } else if(dir == "NE") {
    auto at = 45.L;
    for(int i=(int)size(s)-3; i>=0; i--) {
      if(s[i] == 'N') {
        at += step;
      } else {
        at -= step;
      }
      step /= 2;
    }
    return at;
  } else if(dir == "SE") {
    auto at = -45.L;
    for(int i=(int)size(s)-3; i>=0; i--) {
      if(s[i] == 'S') {
        at -= step;
      } else {
        at += step;
      }
      step /= 2;
    }
    return at;
  } else if(dir == "SW") {
    auto at = -135.L;
    for(int i=(int)size(s)-3; i>=0; i--) {
      if(s[i] == 'S') {
        at += step;
      } else {
        at -= step;
      }
      step /= 2;
    }
    return at;
  }
  assert(false);
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  string s, t;
  cin >> s >> t;
  auto a = get(s) - get(t);
  while(a > 180) a -= 360;
  while(a < -180) a += 360;
  cout << abs(a) << nl;
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

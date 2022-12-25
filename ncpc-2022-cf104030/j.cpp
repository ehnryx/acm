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

auto read() {
  int a, b;
  cin >> a >> b;
  return pair(a, b);
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  auto s = read();
  auto t = read();
  vector<decltype(read())> p;
  for(int i=0; i<n; i++) {
    p.push_back(read());
  }

  auto cur = s;
  auto left = [&](int x) {
    cur.first -= x;
    for(int i=0; i<x; i++) {
      cout << "left" << nl;
    }
  };
  auto right = [&](int x) {
    cur.first += x;
    for(int i=0; i<x; i++) {
      cout << "right" << nl;
    }
  };
  auto up = [&](int x) {
    cur.second += x;
    for(int i=0; i<x; i++) {
      cout << "up" << nl;
    }
  };
  auto down = [&](int x) {
    cur.second -= x;
    for(int i=0; i<x; i++) {
      cout << "down" << nl;
    }
  };

  // exit left
  left(s.first + 1);
  assert(cur == pair(-1, s.second));
  up(1);
  left(32);
  down(1);
  right(32);
  assert(cur == pair(-1, s.second));

  // go to (-1, -1)
  down(s.second + 1);
  assert(cur == pair(-1, -1));

  // push right
  for(int i=0; i<=30; i++) {
    up(1);
    right(t.first);
    left(t.first);
    assert(cur == pair(-1, i));
  }
  assert(cur == pair(-1, 30));

  // go to (-1, -1);
  down(31);
  assert(cur == pair(-1, -1));

  // push up
  for(int i=0; i<=63; i++) {
    right(1);
    up(t.second);
    down(t.second);
    assert(cur == pair(i, -1));
  }
  assert(cur == pair(63, -1));

  // go to (63, y-1);
  up(t.second + 1);
  assert(cur == pair(63, t.second));

  // push left and shift down
  for(int i=0; i<=30; i++) {
    left(64);
    assert(cur.first == -1);
    up(31 - i);
    for(int j=0; j<64; j++) {
      right(1);
      down(1);
      up(1);
    }
    down(31 - i);
    assert(cur == pair(63, t.second));
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

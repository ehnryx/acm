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


struct Cost {
  int f, r, l;
};

const int M = 100;
struct Edge {
  int x, y, dir; // dir: v > ^ <
  operator int() const {
    return 4 * (M * (x-1) + (y-1)) + dir;
  }
  Edge forward() const {
    switch(dir) {
      case 0: return Edge{ x+1, y, dir };
      case 1: return Edge{ x, y+1, dir };
      case 2: return Edge{ x-1, y, dir };
      case 3: return Edge{ x, y-1, dir };
    }
    assert(false);
  }
  Edge right() const {
    switch(dir) {
      case 0: return Edge{ x+1, y, (dir + 3) & 0b11 };
      case 1: return Edge{ x, y+1, (dir + 3) & 0b11 };
      case 2: return Edge{ x-1, y, (dir + 3) & 0b11 };
      case 3: return Edge{ x, y-1, (dir + 3) & 0b11 };
    }
    assert(false);
  }
  Edge left() const {
    switch(dir) {
      case 0: return Edge{ x+1, y, (dir + 1) & 0b11 };
      case 1: return Edge{ x, y+1, (dir + 1) & 0b11 };
      case 2: return Edge{ x-1, y, (dir + 1) & 0b11 };
      case 3: return Edge{ x, y-1, (dir + 1) & 0b11 };
    }
    assert(false);
  }
};
const Edge ret_up{ 2, 1, 2 };
const Edge ret_left{ 1, 2, 3 };

struct Item {
  int phase;
  Edge u;
  int d;
  bool operator < (const Item& o) const {
    return d > o.d;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m, c;
  cin >> n >> m >> c;
  auto input = [&cin]() -> pair<int, int> {
    int x, y;
    cin >> x >> y;
    return pair(x, y);
  };
  auto s = input();
  auto t = input();
  assert(s != pair(1, 1));
  assert(t != pair(1, 1));

  // f, r, l
  vector costs(n+1, vector(m+1, Cost{1, 2, 3}));
  for(int i=0; i<c; i++) {
    auto v = input();
    int f, r, l;
    cin >> f >> r >> l;
    costs[v.first][v.second] = Cost{f, r, l};
  }
  costs[1][1] = Cost{0, 0, 0};

  // three phases
  vector dists(3, vector<int>(M * M * 4, -1));

  priority_queue<Item> dijk;
  dijk.push(Item{0, Edge{1, 1, 0}, 0});
  dijk.push(Item{0, Edge{1, 1, 1}, 0});
  while(not empty(dijk)) {
    auto [phase, u, d] = dijk.top();
    dijk.pop();
    if(dists[phase][u] != -1) continue;
    dists[phase][u] = d;
    do {
      auto v = u.forward();
      if(v.x < 1 || n < v.x || v.y < 1 || m < v.y) break;
      int np = phase +
        (phase == 0 && make_pair(v.x, v.y) == s) +
        (phase == 1 && make_pair(v.x, v.y) == t);
      if(dists[np][v] != -1) break;
      dijk.push(Item{np, v, d + costs[v.x][v.y].f + 1});
    } while (false);
    do {
      auto v = u.right();
      if(v.x < 1 || n < v.x || v.y < 1 || m < v.y) break;
      int np = phase +
        (phase == 0 && make_pair(v.x, v.y) == s) +
        (phase == 1 && make_pair(v.x, v.y) == t);
      if(dists[np][v] != -1) break;
      dijk.push(Item{np, v, d + costs[v.x][v.y].r + 1});
    } while (false);
    do {
      auto v = u.left();
      if(v.x < 1 || n < v.x || v.y < 1 || m < v.y) break;
      int np = phase +
        (phase == 0 && make_pair(v.x, v.y) == s) +
        (phase == 1 && make_pair(v.x, v.y) == t);
      if(dists[np][v] != -1) break;
      dijk.push(Item{np, v, d + costs[v.x][v.y].l + 1});
    } while (false);
  }

  assert(dists[2][ret_up] != -1 && dists[2][ret_left] != -1);
  cout << 1 + min(dists[2][ret_up], dists[2][ret_left]) << nl;
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

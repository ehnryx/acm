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

struct pt {
  int x, y;
  bool operator!=(const pt& o) const { return !operator==(o); }
  bool operator==(const pt& o) const { return x == o.x and y == o.y; }
};

struct node {
  pt pivot;
  ld turn;
};

int sgn(int x) {
  return x < 0 ? -1 : x > 0 ? 1 : 0;
}

int cross(pt a, pt b) {
  return a.x * b.y - a.y * b.x;
}

bool pt_in_triangle(pt t, pt a, pt b, pt c) {
  return sgn(cross(a - t, b - t)) == sgn(cross(b - t, c - t)) and
    sgn(cross(b - t, c - t)) == sgn(cross(c - t, a - t));
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<pt> toys, trees;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    toys.emplace_back(pt{x, y});
  }
  for(int i=0; i<m; i++) {
    int x, y;
    cin >> x >> y;
    trees.emplace_back(pt{x, y});
  }

  vector<node> path = { node{ pt{0, 0}, 0 } };
  pt at = toys.front();
  ld need = abs(at);
  for(int i=1; i<n; i++) {
    pt last = at;
    at = toys[i];
    pt pivot = path.back().pivot;
    vector<pair<ld, pt>> sector;
    for(pt t : trees) {
      if(t != pivot and pt_in_triangle(t, pivot, last, at)) {
        sector.emplace_back(abs(arg((t - pivot) / (last - pivot))), t);
      }
    }
    sort(begin(sector), end(sector));

    ld mindist = 0;
    for(pt t : sector) {
      if(abs(t - pivot) < mindist) continue;
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(2);
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

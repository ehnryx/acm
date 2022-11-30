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
  pt(int _x, int _y): x(_x), y(_y) {}
  bool operator<(pt o) const { return x < o.x or (x == o.x and y < o.y); }
  pt operator-(pt o) const { return pt(x - o.x, y - o.y); }
  void fix_signs() {
    if(x < 0 or (x == 0 and y < 0)) {
      x *= -1;
      y *= -1;
    }
  }
};

bool slope_less(pt a, pt b) {
  // a.y / a.x < b.y / b.x
  a.fix_signs();
  b.fix_signs();
  return ll(a.y) * b.x < ll(b.y) * a.x;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.emplace_back(x, y);
  }
  vector<vector<int>> adj(n);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<map<int, int>> revmap(n);
  vector<vector<bool>> done(n);
  for(int i=0; i<n; i++) {
    sort(begin(adj[i]), end(adj[i]),
      [&p, i](int a, int b) {
        int ha = p[a] < p[i];
        int hb = p[b] < p[i];
        if(ha != hb) return ha < hb;
        return slope_less(p[a] - p[i], p[b] - p[i]);
      }
    );
    for(int j=0; j<size(adj[i]); j++) {
      revmap[i][adj[i][j]] = j;
    }
    done[i].resize(size(adj[i]), false);
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<size(adj[i]); j++) {
      if(done[i][j]) continue;
      int u = i;
      int v = adj[i][j];
      done[i][j] = true;
      while(v != i) {
        int rev = revmap[v][u]
      }
    }
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

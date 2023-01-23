#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/floyd_warshall.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

static constexpr unsigned shift = 6;
static constexpr ll mask = (1ll << shift) - 1;

struct state {
  ll used;
  vector<ll> groups;
  state() = default;
  state(vector<int> L): used(0) {
    for(int v : L) {
      used |= 1ll << v;
      groups.push_back((v << shift | v) ^ (mask << shift | mask) ^ (-1ll));
    }
  }
  bool operator<(const state& o) const {
    return used < o.used or (used == o.used and groups < o.groups);
  }
  void sort_all() {
    sort(begin(groups), end(groups));
  }
  bool good(vector<pair<int, int>> lines) {
    for(auto [a, b] : lines) {
      for(ll g : groups) {
        g >>= shift; // pop the front
        int cnt = 0;
        while((g & mask) != mask) {
          cnt += (g & mask) == a or (g & mask) == b;
          g >>= shift;
        }
        if(cnt == 1) return false;
        if(cnt) break;
      }
    }
    return true;
  }
  int front(int i) const {
    return groups[i] & mask;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  unordered_map<string, int> remap;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    remap[s] = i;
  }

  floyd_warshall dist(n, int(1e9) + 1);
  for(int i=0; i<m; i++) {
    string a, b;
    int c;
    cin >> a >> b >> c;
    dist.add_edge(remap[a], remap[b], c);
  }
  dist.run();

  vector<pair<int, int>> lines;
  vector<int> leaves;
  for(int i=0; i<4; i++) {
    string a, b;
    cin >> a >> b;
    leaves.push_back(remap[a]);
    leaves.push_back(remap[b]);
    if(remap[a] != remap[b]) {
      lines.emplace_back(remap[a], remap[b]);
    }
  }
  sort(begin(leaves), end(leaves));
  leaves.resize(distance(begin(leaves), unique(begin(leaves), end(leaves))));

  map<state, int> memo;
  auto solve = [&](auto&& self, state cur) {
    if(auto it = memo.find(cur); it != memo.end()) {
      return it->second;
    }
    if(cur.good(lines)) {
      return 0;
    }

    int gs = size(cur.groups);
    int res = 1e9 + 1;
    for(int i=0; i<gs; i++) {
      for(int j=0; j<i; j++) {
        for(int at=0; at<n; at++) {
          if((cur.used >> at & 1) and at != cur.front(i) and at != cur.front(j)) {
            continue;
          }
          state nxt;
          nxt.used = cur.used | 1ll << at;
          for(int k=0; k<gs; k++) {
            if(k != i and k != j) {
              nxt.groups.push_back(cur.groups[k]);
            }
          }
          ll last = at ^ mask ^ (-1ll);
          int idx = 1;
          ll gi = cur.groups[i] >> shift;
          ll gj = cur.groups[j] >> shift;
          while((gi & mask) != mask or (gj & mask) != mask) {
            if((gi & mask) < (gj & mask)) {
              last ^= ((gi & mask) ^ mask) << (idx * shift);
              gi >>= shift;
            } else {
              last ^= ((gj & mask) ^ mask) << (idx * shift);
              gj >>= shift;
            }
            idx++;
          }
          nxt.groups.push_back(last);
          nxt.sort_all();
          res = min(res, dist[at][cur.front(i)] + dist[at][cur.front(j)] + self(self, nxt));
        }
      }
    }

    return memo[cur] = res;
  };

  cout << solve(solve, state(leaves)) << nl;
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

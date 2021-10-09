#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

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

  vector<bool> res(m + 1);
  vector<vector<int>> adj(m + 1);
  vector<int> deg(n);
  vector<int> horn(n);
  queue<int> bfs;

  string line;
  getline(cin, line);
  for(int i=0; i<n; i++) {
    getline(cin, line);
    istringstream in(line);
    vector<string> tokens;
    for(string s; in >> s; ) {
      tokens.push_back(move(s));
    }

    if(tokens.back().front() == '!') {
      int u = stoi(tokens.back().substr(1));
      adj[u].push_back(i);
      deg[i]++;
    } else {
      int u = stoi(tokens.back());
      horn[i] = u;
    }
    tokens.pop_back();
    if(!empty(tokens)) {
      assert(tokens.back() == "->");
      tokens.pop_back();
      for(string s : tokens) {
        adj[stoi(s)].push_back(i);
        deg[i]++;
      }
    }

    if(deg[i] == 0) {
      bfs.push(i);
    }
  }

  while(!empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    if(!horn[u]) {
      cout << "conflict" << nl;
      return 0;
    }
    if(res[horn[u]]) continue;
    res[horn[u]] = true;
    for(int i : adj[horn[u]]) {
      if(--deg[i] == 0) {
        bfs.push(i);
      }
    }
  }

  for(int i=1; i<=m; i++) {
    cout << (res[i] ? 'T' : 'F');
  }
  cout << nl;

  return 0;
}

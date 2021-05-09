#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
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

  int n, k;
  cin >> n >> k;
  vector<int> a(n+1), pre(n+1), nxt(n+1, n+1);
  vector<vector<int>> idx(k+1);
  idx[0].push_back(0);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    idx[a[i]].push_back(i);
    if(empty(idx[a[i]-1])) continue;
    int j = idx[a[i]-1].back();
    pre[i] = j;
    nxt[j] = min(nxt[j], i);
  }
  for(int i=1; i<=k; i++) {
    for(int j=(int)size(idx[i])-2; j>=0; j--) {
      nxt[idx[i][j]] = min(nxt[idx[i][j]], nxt[idx[i][j+1]]);
    }
  }

  vector<int> path(n+1);
  set<int,greater<>> have(begin(idx[1]), end(idx[1]));
  for(int i=2; i<=k; i++) {
    set<int,greater<>> cur;
    for(int j : idx[i]) {
      auto par = have.lower_bound(pre[j]);
      if(par == end(have)) continue;
      path[j] = *par;
      have.erase(par);
      cur.insert(j);
    }
    have = move(cur);
  }
  int ans = size(have);

  int id = 0;
  vector<int> pid(n+1);
  for(int t : have) {
    id++;
    for(int i=t; i>0; i=path[i]) {
      pid[i] = id;
    }
  }
  assert(ans == id);
  vector<int> reach(ans+1);

  vector<set<int>> todo(k+1);
  for(int i=1; i<=k; i++) {
    for(int j : idx[i]) {
      todo[i].insert(j);
    }
  }
  queue<pair<int,bool>> bfs;
  vector vis(n+1, vector<bool>(2));
  vis[0][0] = true;
  bfs.emplace(0, 0);
  while(!empty(bfs)) {
    auto [u, left] = bfs.front();
    bfs.pop();
    if(pid[u] && !left && !vis[u][1]) {
      vis[u][1] = true;
      bfs.emplace(u, 1);
    }
    if(!pid[u] && left && !vis[u][0]) {
      vis[u][0] = true;
      bfs.emplace(u, 0);
    }
    if(pid[u] && left) {
      reach[pid[u]] = max(reach[pid[u]], u);
      if(!vis[path[u]][0]) {
        vis[path[u]][0] = true;
        bfs.emplace(path[u], 0);
      }
    }
    if(!left && a[u] < k) {
      set<int>& nbs = todo[a[u] + 1];
      for(auto it=nbs.lower_bound(nxt[u]); it!=end(nbs); it=nbs.erase(it)) {
        vis[*it][1] = true;
        bfs.emplace(*it, 1);
      }
    }
  }

  cout << ans << nl;
  for(int i=1; i<=ans; i++) {
    cout << reach[i] << " ";
  }
  cout << nl;

  return 0;
}

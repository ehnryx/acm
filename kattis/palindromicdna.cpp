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

namespace sat {
  const int N = 1e5 + 7;
  int low[N],vis[N],scomp[N],scompNum,I;
  vector<int> adj[N]; stack<int> verts;
  void init(int n) { fill(adj, adj+2*n, vector<int>()); }
  void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
    for (int v : adj[u]) {
      if (!vis[v]) scc(v);
      if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
    if (vis[u] <= low[u]) { int v;
      do { v=verts.top(); verts.pop(); scomp[v]=scompNum; }while (v != u);
      ++scompNum; }}
  void get_scc(int n) {
    memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
    scompNum=I=0; for (int i=0; i<n; ++i) if (!vis[i]) scc(i); }
  bool truth[N/2]; // N must be at least 2 times the number of variables
  // the clause a || b becomes !a => b and !b => a in implication graph
  void add_clause(int a, int b) {
    adj[a^1].push_back(b); adj[b^1].push_back(a); }
  bool two_sat(int n) { get_scc(n *= 2);
    for (int i = 0; i < n; i += 2) { if (scomp[i] == scomp[i^1]) return 0;
      truth[i/2] = (scomp[i] < scomp[i^1]); } return 1; }
}

const vector<char> var = { 'A', 'G', 'T', 'C' };

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

  for(int n, m; cin >> n >> m && n; ) {
    vector<int> dsu(n, -1);
    function<int(int)> find = [&](int i) {
      if(dsu[i] == -1) return i;
      return dsu[i] = find(dsu[i]);
    };
    function<void(int,int)> link = [&](int i, int j) {
      i = find(i);
      j = find(j);
      if(i != j) {
        dsu[i] = j;
      }
    };

    string s;
    cin >> s;
    for(int i=0; i<m; i++) {
      int k; char _;
      cin >> k >> _;
      vector<int> a(k);
      for(int j=0; j<k; j++) {
        cin >> a[j];
        if(j >= k/2) {
          link(a[j], a[k-1-j]);
        }
      }
    }

    sat::init(4*n);
    function<int(int,int)> get = [=](int i, int j) {
      return 2 * (i*4 + j);
    };

    vector<set<char>> groups(n);
    vector<vector<int>> pos(n);
    for(int i=0; i<n; i++) {
      groups[find(i)].insert(s[i]);
      pos[find(i)].push_back(i);
      if(i > 0) {
        for(int j=0; j<4; j++) {
          if(var[j] == s[i]) continue;
          for(int k=0; k<4; k++) {
            if(var[k] == s[i-1]) continue;
            // no adjacent pair both changed
            sat::adj[get(i, j)].push_back(get(i-1, k) ^ 1);
            sat::adj[get(i-1, k)].push_back(get(i, j) ^ 1);
          }
        }
      }
    }

    bool ok = true;
    for(int i=0; i<n && ok; i++) {
      int r = find(i);
      if(groups[r].size() <= 1) continue;
      ok &= (groups[r].size() <= 3);
      vector<int> to;
      for(int j=0; j<4; j++) {
        if(!groups[r].count(var[(j+2)%4])) {
          to.push_back(j);
        }
      }
      if(to.size() == 1 && var[to[0]] == s[i]) continue;
      for(int j=0; j<to.size(); j++) {
        // one of the two should change
        sat::adj[get(i, to[j]) ^ 1].push_back(get(i, to[(j+1) % size(to)]));
      }
      if(r == i) {
        for(int j=1; j<pos[r].size(); j++) {
          for(int k=0; k<4; k++) {
            sat::adj[get(pos[r][j], k)].push_back(get(pos[r][j-1], k));
            sat::adj[get(pos[r][j-1], k)].push_back(get(pos[r][j], k));
            sat::adj[get(pos[r][j], k) ^ 1].push_back(get(pos[r][j-1], k) ^ 1);
            sat::adj[get(pos[r][j-1], k) ^ 1].push_back(get(pos[r][j], k) ^ 1);
          }
        }
      }
    }

    if(ok && sat::two_sat(n*4)) {
      cout << "YES" << nl;
    } else {
      cout << "NO" << nl;
    }
  }

  return 0;
}

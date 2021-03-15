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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int L = 30;
const int N = 1 << 29;
vector<int> lc, rc;
vector<vector<int>> st;

vector<int> combine(vector<int> a, vector<int> b) {
  vector<int> out;
  merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(out), greater<int>());
  if(out.size() > 4) out.resize(4);
  return out;
}

int sid = 1;
int insert(int x, int v, int i=1, int s=0, int e=N-1) {
  if(!i) {
    i = lc.size();
    lc.push_back(0);
    rc.push_back(0);
    st.push_back({});
  }
  if(s == e) {
    st[i].push_back(v);
    return i;
  }
  int m = (s+e) / 2;
  if(x <= m) lc[i] = insert(x, v, lc[i], s, m);
  else rc[i] = insert(x, v, rc[i], m+1, e);
  st[i] = combine(st[lc[i]], st[rc[i]]);
  return i;
}

vector<int> query(int l, int r, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l || !i) return {};
  if(l<=s && e<=r) {
    return st[i];
  }
  int m = (s+e) / 2;
  auto left = query(l, r, lc[i], s, m);
  auto right = query(l, r, rc[i], m+1, e);
  return combine(left, right);
}

const int M = 1e5 + 1;
vector<pair<int,int>> adj[M][L];
int dist[M][L];

const int O = 1e8 + 7;

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

  lc.resize(2);
  rc.resize(2);
  st.resize(2);

  int n, k;
  cin >> n >> k;
  vector<int> x(n);
  for(int i=0; i<n; i++) {
    cin >> x[i];
    x[i] = (x[i] + O) * 2;
    insert(x[i], i);
  }
  x.push_back(O * 2);

  for(int i=0; i<=n; i++) {
    for(int r=1, z=0; r<8e8; r*=2, z++) {
      auto vals = query(x[i] - r, x[i] + r);
      for(int j=0; j<k && j<vals.size(); j++) {
        adj[i][z].emplace_back(vals[j], z);
      }
      if(r > 1) adj[i][z].emplace_back(i, z-1);
      if(2*r < 8e8) adj[i][z].emplace_back(i, z+1);
    }
  }

  memset(dist, -1, sizeof dist);
  queue<pair<int,int>> bfs;
  bfs.emplace(n, 1);
  dist[n][1] = 0;
  while(!bfs.empty()) {
    auto [u, z] = bfs.front();
    bfs.pop();
    for(auto [nu, nz] : adj[u][z]) {
      if(dist[nu][nz] == -1) {
        dist[nu][nz] = dist[u][z] + 1;
        bfs.emplace(nu, nz);
      }
    }
  }

  for(int i=0; i<n; i++) {
    int ans = INF;
    for(int r=1, z=0; r<8e8; r*=2, z++) {
      if(dist[i][z] == -1) continue;
      auto vals = query(x[i] - r, x[i] + r);
      bool ok = false;
      for(int j=0; j<k && j<vals.size(); j++) {
        if(vals[j] == i) {
          ok = true;
        }
      }
      if(ok) {
        ans = min(ans, dist[i][z]);
      }
    }
    if(ans < INF) {
      cout << ans << nl;
    } else {
      cout << -1 << nl;
    }
  }

  return 0;
}

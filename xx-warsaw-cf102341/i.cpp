#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5+1;
const int L = 18;
vector<int> adj[N];
bool vrai[N];

void add_edge(int a, int b) {
  adj[a].push_back(b);
  adj[b].push_back(a);
}

int anc[N][L];
int depth[N];
void build_lca(int u, int p) {
  depth[u] = depth[p]+1;
  anc[u][0] = p;
  for(int j=1; j<L; j++) {
    anc[u][j] = anc[anc[u][j-1]][j-1];
  }
  for(int v:adj[u]) {
    if(v!=p) build_lca(v,u);
  }
}

int jump(int a, int d) {
  for(int j=0; j<L; j++) {
    if(d&1<<j) a = anc[a][j];
  }
  return a;
}

int lca(int a, int b) {
  if(depth[a] < depth[b]) swap(a,b);
  ////cerr<<"lca "<<a<<" "<<b<<nl;
  ////cerr<<"jump "<<a<<" :: "<<depth[a]<<" -> "<<depth[b]<<nl;
  a = jump(a, depth[a]-depth[b]);
  ////cerr<<"get "<<a<<nl;
  if(a == b) return a;
  for(int j=L-1; j>=0; j--) {
    if(anc[a][j] != anc[b][j]) {
      a = anc[a][j];
      b = anc[b][j];
    }
  }
  return anc[a][0];
}

pii intersect(const pii& a, const pii& b) {
  if(a.second<0 || b.second<0) return make_pair(-1, -1);
  int u = a.first;
  int v = b.first;
  int c = lca(u, v);
  int d = depth[u]+depth[v] - 2*depth[c];
  if(a.second+d <= b.second) return a;
  if(b.second+d <= a.second) return b;
  ////cerr<<u<<" "<<v<<" w/ lca "<<c<<" -> "<<a.second<<" "<<b.second<<" "<<d<<nl;
  assert((a.second + b.second - d) % 2 == 0);
  int r = (a.second + b.second - d) / 2;
  if(r < 0) return make_pair(-1, -1);
  //////cerr<<"intersecting "<<u<<" and "<<v<<" -> lca "<<c<<nl;
  int len = a.second - r;
  assert(b.second - r == d - len);
  assert(len>=0 && d-len>=0);
  if(len <= depth[u] - depth[c]) {
    //////cerr<<"jump "<<u<<" up "<<len<<nl;
    return make_pair(jump(u, len), r);
  } else {
    //////cerr<<"jump "<<v<<" up "<<d-len<<nl;
    return make_pair(jump(v, d-len), r);
  }
}

bool vis[N];
int sz[N], par[N];
vector<pii> cpar[N], csub[N];
vector<int> dists[N], pard[N];

int dfs(int u, int p, int d, vector<int>& verts) {
  verts.push_back(u);
  par[u] = p;
  sz[u] = 1;
  for(int v:adj[u]) {
    if(v == p || vis[v]) continue;
    sz[u] += dfs(v, u, d+1, verts);
  }
  return sz[u];
}

int get_dists(int u, int p, int r, int d) {
  cpar[u].push_back(make_pair(r, d));
  csub[r].push_back(make_pair(u, d));
  int res = d;
  for(int v:adj[u]) {
    if(v == p || vis[v]) continue;
    res = max(res, get_dists(v, u, r, d+1));
  }
  return res;
}

int centroid(int u) {
  vector<int> verts;
  int s = dfs(u, 0, 0, verts);
  for(int v:verts) {
    bool ok = true;
    for(int w:adj[v]) {
      if(vis[w]) continue;
      if(2*sz[v] < s || (sz[v] > sz[w] && 2*sz[w] > s)) {
        ok = false;
        break;
      }
    }
    if(ok) {
      int maxv = get_dists(v, 0, v, 0);
      dists[v].resize(maxv+1, 0);
      for(const pii& it:csub[v]) {
        dists[v][it.second] += vrai[it.first];
      }
      return v;
    }
  }
  assert(false);
}

int decompose(int u) {
  int c = centroid(u);
  vis[c] = true;
  assert(csub[c][0].first == c);
  int j = 1;
  int pre = -1;
  for(int v:adj[c]) {
    if(!vis[v]) {
      int nc = decompose(v);
      if(pre != -1) {
        int maxv = 0;
        for(int k=j; v!=csub[c][k].first; k++) {
          maxv = max(maxv, csub[c][k].second);
        }
        pard[pre].resize(maxv+1, 0);
        for( ; v != csub[c][j].first; j++) {
          pard[pre][csub[c][j].second] += vrai[csub[c][j].first];
        }
      }
      assert(j < csub[c].size());
      pre = nc;
    }
  }
  if(pre != -1) {
    int maxv = 0;
    for(int k=j; k<csub[c].size(); k++) {
      maxv = max(maxv, csub[c][k].second);
    }
    pard[pre].resize(maxv+1, 0);
    for( ; j < csub[c].size(); j++) {
      pard[pre][csub[c][j].second] += vrai[csub[c][j].first];
    }
  }
  return c;
}

int get(const vector<int>& sum, int i) {
  if(i >= sum.size()) return sum.back();
  else return sum[i];
}

int calc(const pii& ball) {
  int v, r;
  tie(v, r) = ball;
  //cerr<<"calc "<<v<<" "<<r<<nl;
  int res = 0;
  for(int i=0; i<cpar[v].size(); i++) {
    int c, d;
    tie(c, d) = cpar[v][i];
    //cerr<<"do centroid "<<c<<" w/ distance "<<d<<nl;
    if(d > r) continue;
    int cur = r - d;
    res += get(dists[c], cur);
    if(i+1 < cpar[v].size()) {
      res -= get(pard[cpar[v][i+1].first], cur);
    }
  }
  //cerr<<"got "<<res<<nl;
  //cerr<<nl;
  return res;
}

void prefix_sums(vector<int>& v) {
  for(int i=1; i<v.size(); i++) {
    v[i] += v[i-1];
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    add_edge(a,i+n);
    add_edge(i+n,b);
    vrai[a] = vrai[b] = true;
  }
  build_lca(1, 0);
  decompose(1);

  ////////cerr<<"TREE: "<<nl; for(int i=1; i<=n; i++) {
  ////////cerr<<"csub: "; for(pii it:csub[i]) //////cerr<<it.first<<','<<it.second<<"  ";
  ////////cerr<<nl;
  ////////cerr<<"pard: "<<nl; for(int j=0; j<pard[i].size(); j++) //////cerr<<j<<": "<<pard[i][j]<<nl; }
  ////////cerr<<nl;

  for(int i=1; i<2*n; i++) {
    prefix_sums(dists[i]);
    prefix_sums(pard[i]);
  }

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    //////cerr<<"query "<<i<<nl;
    int k;
    cin >> k;
    vector<pii> balls;
    for(int j=0; j<k; j++) {
      int v, r;
      cin >> v >> r;
      balls.push_back(make_pair(v, 2*r));
    }
    vector<pii> pre(balls), suf(balls);
    pre[0] = balls[0];
    suf[k-1] = balls[k-1];
    for(int j=1; j<k; j++) {
      //////cerr<<"intersect pre "<<j<<" and suf "<<k-j-1<<nl;
      pre[j] = intersect(pre[j-1], balls[j]);
      suf[k-j-1] = intersect(suf[k-j], balls[k-j-1]);
    }
    ll res = calc(suf[1]) + calc(pre[k-2]);
    for(int j=1; j+1<k; j++) {
      //////cerr<<"intersect "<<j-1<<" and "<<j+1<<nl;
      res += calc(intersect(pre[j-1], suf[j+1]));
    }
    res -= (ll) (k-1) * calc(pre[k-1]);
    cout << res << nl;
    //////cerr<<endl;
  }

  return 0;
}

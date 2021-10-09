#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
  int i, c;
};

struct Query {
  int a, b, c;
};

struct SegTree { int n; ll *segt; // EXAMPLE
  SegTree(int len) { n = 1<<(32-__builtin_clz(len));
    segt = new ll[2*n]; fill(segt, segt+2*n, 0);
  }

  void update(int i, ll v) {
    segt[i+=n] = v;
    for (i/=2; i>0; i/=2) {
      segt[i] = segt[2*i] + segt[2*i+1];
    }
  }

  ll sum(int l, int r) {
    ll res = 0;
    for (l+=n,r+=n+1; l<r; l/=2,r/=2) {
      if (l&1) res += segt[l++];
      if (r&1) res += segt[--r];
    }
    return res;
  }

  ll query(int l, int r, ll g) {
    assert(g >= 0);
    int s = l;
    while (l<r) {
      int m = (l+2+r)/2-1;
      if (sum(s,m) < g) {
        l = m+1;
      } else {
        r = m;
      }
    }
    ll one = sum(s,l);
    ll two = sum(s,l-1);
    assert(one >= g);
    assert(two <= g);
    if (abs(one-g) < abs(two-g)) {
      return one;
    } else {
      return two;
    }
  }
};

namespace HLD {
  const int N = 2e5+1;
  SegTree* segt[N];
  vector<int> adj[N];
  int d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; int dn, cn;
  int dfs(int u, int p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
    for (int x:adj[u]) if (x!=p) sub[u] += dfs(x,u); return sub[u]; }
  void hld(int u, int p) { if (dn == cn) { root[cn]=u; sz[cn++]=0; }
    pos[u] = sz[ch[u]=dn]++; int b=-1, c=-1;
    for (int x:adj[u]) if (x!=p && sub[x]>b) b=sub[c=x]; if (c!=-1) hld(c,u);
    for (int y:adj[u]) if (y!=p && y!=c) { dn++; hld(y,u); } }
  void build(int r) { d[0] = dn = cn = 0; dfs(r,0); hld(r,0);
    for (int i=0; i<cn; i++) segt[i] = new SegTree(sz[i]);
  }

  // Returns LCA of path ab, MODIFY for insert_node, query_path, query_node
  ll query_path(int a, int b, ll tot) { // please expand this when typing
    ll half = tot/2;
    int sid = 0;
    ll sum[2];
    sum[0] = sum[1] = 0;
    while (ch[a] != ch[b]) {
      if (d[root[ch[a]]] < d[root[ch[b]]]) { swap(a,b); sid ^= 1; }
      ll cur = segt[ch[a]]->sum(0, pos[a]);
      sum[sid] += cur;
      if (sum[sid] >= half) {
        ll last = segt[ch[a]]->query(0, pos[a], sum[sid]-half);
        ll res = max(sum[sid]-last, tot - (sum[sid]-last));
        if (sum[sid] >= half+1) {
          ll other = segt[ch[a]]->query(0, pos[a], sum[sid]-(half+1));
          res = min(res, max(sum[sid]-other, tot - (sum[sid]-other)));
        }
        return res;
      }
      a = par[root[ch[a]]];
    }
    if (pos[a] != pos[b]) {
      if (d[a] < d[b]) { swap(a,b); sid ^= 1; }
      ll last = segt[ch[a]]->query(pos[b]+1, pos[a], half-sum[sid^1]);
      ll other = segt[ch[a]]->query(pos[b]+1, pos[a], half+1-sum[sid^1]);
      return min(
        max(sum[sid^1]+last, tot - (sum[sid^1]+last)),
        max(sum[sid^1]+other, tot - (sum[sid^1]+other))
      );
    }
    assert(half == 0);
    return 0;
  }

  void insert_node(int a, int v) {
    segt[ch[a]]->update(pos[a], v);
  }
}


struct Path {
  int a, b, c;
  ll len;
  Path(int u=0, ll l=0): a(u), b(u), c(0), len(l) {}
  Path(int a, int b, int c, ll l): a(a), b(b), c(c), len(l) {}
  bool operator < (const Path& o) const {
    if (len != o.len) return len < o.len;
    else return a < o.a;
  }
  Path through(int child) {
    return Path(a, b, child, len);
  }
  Path extend(ll add) {
    return Path(a, b, 0, len + add);
  }
  Path join(const Path& o) const {
    assert(a == b);
    assert(o.a == o.b);
    return Path(a, o.a, 0, len + o.len);
  }
};


const int N = 2e5+1;
vector<Edge> adj[N];
int par[N], pcost[N];
Path best[N], sec[N], third[N], dp2[N], cbest[N], csec[N];
Path up1[N], up2[N];

void precomp(int u, int p) {
  par[u] = p;
  for (const Edge& e : adj[u]) {
    if (e.i != p) {
      pcost[e.i] = e.c;
      precomp(e.i, u);
    }
  }
}

void solve_down(int u) {
  best[u] = sec[u] = third[u] = Path(u);
  cbest[u] = csec[u] = Path(u);
  dp2[u] = Path(u);
  for (const Edge& e : adj[u]) {
    if (e.i != par[u]) {
      solve_down(e.i);
      dp2[u] = max(dp2[u], dp2[e.i]);
      // diam
      Path diam = dp2[e.i].through(e.i);
      if (cbest[u] < diam) {
        csec[u] = cbest[u];
        cbest[u] = diam;
      } else if (csec[u] < diam) {
        csec[u] = diam;
      }
      // path
      Path path = best[e.i].extend(e.c).through(e.i);
      if (best[u] < path) {
        third[u] = sec[u];
        sec[u] = best[u];
        best[u] = path;
      } else if (sec[u] < path) {
        third[u] = sec[u];
        sec[u] = path;
      } else if (third[u] < path) {
        third[u] = path;
      }
    }
  }
  dp2[u] = max(dp2[u], best[u].join(sec[u]));
}

void solve_up(int u) {
  up1[u] = Path(par[u], 0);
  up2[u] = Path(par[u], -1);
  if (par[u]) {
    // path
    up1[u] = max(up1[u], up1[par[u]].extend(pcost[u]));
    if (best[par[u]].c != u) {
      up1[u] = max(up1[u], best[par[u]].extend(pcost[u]));
    } else {
      up1[u] = max(up1[u], sec[par[u]].extend(pcost[u]));
    }
    // update paths
    Path path = up1[u].through(par[u]);
    if (best[u] < path) {
      third[u] = sec[u];
      sec[u] = best[u];
      best[u] = path;
    } else if (sec[u] < path) {
      third[u] = sec[u];
      sec[u] = path;
    } else if (third[u] < path) {
      third[u] = path;
    }
    // diam
    up2[u] = max(up2[u], up2[par[u]]);
    if (cbest[par[u]].c != u) {
      up2[u] = max(up2[u], cbest[par[u]]);
    } else {
      up2[u] = max(up2[u], csec[par[u]]);
    }
    if (best[par[u]].c == u) {
      up2[u] = max(up2[u], sec[par[u]].join(third[par[u]]));
    } else if (sec[par[u]].c == u) {
      up2[u] = max(up2[u], best[par[u]].join(third[par[u]]));
    } else {
      up2[u] = max(up2[u], best[par[u]].join(sec[par[u]]));
    }
  }
  for (const Edge& e : adj[u]) {
    if (e.i != par[u]) {
      solve_up(e.i);
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  vector<Query> edges;
  For(i,n-1) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].push_back({b,c});
    adj[b].push_back({a,c});
    edges.push_back({a,b,c});
    HLD::adj[a].push_back(b);
    HLD::adj[b].push_back(a);
  }

  precomp(1, 0);
  solve_down(1);
  solve_up(1);

  HLD::build(1);
  FOR(i,1,n) {
    HLD::insert_node(i, pcost[i]);
  }

  for (Query it : edges) {
    int a = it.a;
    int b = it.b;
    int c = it.c;
    if (par[b] == a) {
      swap(a,b);
    }
    assert(par[a] == b);

    Path up = up2[a];
    Path down = dp2[a];
    assert(up.a && up.b);
    assert(down.a && down.b);

    ll upath = HLD::query_path(up.a, up.b, up.len);
    ll dpath = HLD::query_path(down.a, down.b, down.len);
    cout << max(upath+c+dpath, max(up.len, down.len)) << nl;
  }

  return 0;
}

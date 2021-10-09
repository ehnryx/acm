#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

const int L = 18;
const int N = 1<<L;

vector<int> adj[N];

template<class T> struct RMQ {
  T rmq[2*N][L+1]; int lg[2*N];
  void build() { for (int j=1; j<2*N; j++) lg[j]=31-__builtin_clz(j);
    for (int j=1; j<L+1; j++) for (int i=0; i+(1<<j)-1<2*N; i++)
      rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]); }
  T query(int a, int b) { if (a>b) swap(a,b);
    int j=lg[b-a+1]; return min(rmq[a][j], rmq[b-(1<<j)+1][j]); }
};

struct LCA : RMQ<pii> {
  int dh[N], sp[N], par[N], subsz[N];
  int lcan; LCA() { lcan = dh[0] = 0; }
  void build(int root) { build(root,0); RMQ::build(); }
  int build(int cur, int p) {
    dh[cur] = dh[par[cur]=p]+1; sp[cur] = lcan; subsz[cur] = 1;
    rmq[lcan++][0] = pii(dh[cur],cur);
    for (int i:adj[cur]) if (i!=p) { subsz[cur] += build(i,cur);
      rmq[lcan++][0] = pii(dh[cur],cur); } return subsz[cur]; }
  int query(int a, int b) { return RMQ::query(sp[a],sp[b]).second; }
};

void UPDATE(int,int,int);

struct HLD : LCA {
  vector<int> sz, root, start;
  int chain[N], pos[N];
  int hldn, segn; HLD(): LCA() { hldn = segn = 0; }
  int get(int i) const { return start[chain[i]] + pos[i]; }
  void build(int r) { LCA::build(r); build_hld(r,0); }
  void build_hld(int cur, int p) {
    if (hldn == root.size()) {
      root.push_back(cur); start.push_back(segn); sz.push_back(0);
    } chain[cur] = hldn; pos[cur] = sz[chain[cur]]++; segn++;
    int best = -1, child = -1;
    for (int x:adj[cur])
      if (x!=p && subsz[x]>best) { best = subsz[child=x]; }
    if (child != -1) build_hld(child, cur);
    for (int x:adj[cur])
      if (x!=p && x!=child) { hldn++; build_hld(x,cur); } }
  /// insert
  void insert_path(int a, int b, int v) {
    while (chain[a] != chain[b]) {
      int s = start[chain[a]];
      UPDATE(s, s+pos[a], v);
      a = par[root[chain[a]]];
    }
    if (pos[a] != pos[b]) {
      int s = start[chain[a]];
      UPDATE(s+pos[b]+1, s+pos[a], v);
    }
  }
};

int ans[N], cnt[N];
int lazy[2*N], col[2*N];

void push(int i) {
  if (lazy[i]) {
    lazy[2*i] = lazy[2*i+1] = lazy[i];
    col[2*i] = col[2*i+1] = lazy[i];
    lazy[i] = 0;
  }
}

void pull(int i) {
  if (col[2*i] == col[2*i+1]) {
    col[i] = col[2*i];
  } else {
    col[i] = -1;
  }
}

// UPDATE
void update(int a, int b, int v, int i=1, int l=0, int r=N-1) {
  if (b<l || r<a) return;
  //cerr << "visit " << a << " " << b << " @ " << i << " " << l << " " << r << endl;
  if (a<=l && r<=b && col[i] != -1) {
    //cerr << "update " << i << endl;
    // update old
    if (col[i] != 0) {
      ans[cnt[col[i]]]--;
      cnt[col[i]] -= r-l+1;
      ans[cnt[col[i]]]++;
    }
    // update seg
    col[i] = v;
    lazy[i] = v;
    // update new
    ans[cnt[col[i]]]--;
    cnt[col[i]] += r-l+1;
    ans[cnt[col[i]]]++;
    return;
  }
  push(i);
  int m = (l+r)/2;
  update(a, b, v, 2*i, l, m);
  update(a, b, v, 2*i+1, m+1, r);
  pull(i);
}
void UPDATE(int a, int b, int v) {
  //cerr << "UPDATE " << a << " " << b << " " << v << endl;
  update(a,b,v);
}

HLD hld;

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, C, Q;
  cin >> n >> C >> Q;
  ans[0] = C;

  for (int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  hld.build(1);

  while (Q--) {
    int u, c, m;
    cin >> u >> c >> m;
    //cerr << "u c m " << u << " " << c << " " << m << endl;
    hld.insert_path(u, 1, c);
    cout << ans[m] << nl;
  }

  return 0;
}

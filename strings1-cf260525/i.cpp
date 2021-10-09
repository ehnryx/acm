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

const int N = 1<<20;
const int M = 26;

vector<int> adj[N];
int start[N], sz[N];
bool alive[N];

int st[2*N];
void st_update(int l, int r, int v) {
  for(l+=N, r+=N; l<r; l/=2, r/=2) {
    if(l&1) st[l++] += v;
    if(r&1) st[--r] += v;
  }
}
int st_query(int x) {
  int res = st[x+=N];
  for(x/=2;x;x/=2) {
    res += st[x];
  }
  return res;
}

struct AhoCorasick {
  struct Node {
    int ch[M], par, fail;
    Node(int p=0): par(p) {
      memset(ch, 0, sizeof ch);
      fail = 0;
    }
  };

  int root;
  vector<Node> nds;
  AhoCorasick(): root(0) {
    nds.push_back(Node());
  }

  int insert(const string& s) {
    int u = root;
    for(char C:s) {
      int c = C - 'a';
      if(!nds[u].ch[c]) {
        nds[u].ch[c] = nds.size();
        nds.push_back(Node(u));
      }
      u = nds[u].ch[c];
    }
    return u;
  }

  void build() {
    queue<int> bfs;
    bfs.push(root);
    while(!bfs.empty()) {
      int u = bfs.front();
      bfs.pop();
      for(int i=0; i<M; i++) {
        if(nds[u].ch[i]) {
          int v = nds[u].ch[i];
          int to = nds[u].fail;
          while(to && !nds[to].ch[i]) {
            to = nds[to].fail;
          }
          if(nds[to].ch[i] && nds[to].ch[i] != v) {
            nds[v].fail = nds[to].ch[i];
          }
          bfs.push(v);
          adj[nds[v].fail].push_back(v);
        }
      }
    }
  }

  int dfs(int u, int& id) {
    start[u] = id++;
    sz[u] = 1;
    for(int v:adj[u]) {
      sz[u] += dfs(v, id);
    }
    return sz[u];
  }

  void build_st() {
    int id = 0;
    dfs(root, id);
  }

  void update(int u, int v) {
    if((alive[u] && v>0) || (!alive[u] && v<0)) return;
    st_update(start[u], start[u]+sz[u], v);
    alive[u] = (v > 0);
  }

  ll query(const string& s) {
    ll res = 0;
    int u = root;
    for(char C:s) {
      int c = C - 'a';
      while(u && !nds[u].ch[c]) {
        u = nds[u].fail;
      }
      if(nds[u].ch[c]) {
        u = nds[u].ch[c];
      } else {
        assert(u == 0);
      }
      res += st_query(start[u]);
    }
    return res;
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> m >> n;
  AhoCorasick ac;
  int idx[n+1];
  for(int i=1; i<=n; i++) {
    string s;
    cin >> s;
    idx[i] = ac.insert(s);
  }
  ac.build();
  ac.build_st();

  for(int i=1; i<=n; i++) {
    ac.update(idx[i], 1);
  }

  for(int i=0; i<m; i++) {
    char t;
    cin >> t;
    if(t == '+') {
      int x;
      cin >> x;
      ac.update(idx[x], 1);
    } else if(t == '-') {
      int x;
      cin >> x;
      ac.update(idx[x], -1);
    } else {
      string s;
      cin >> s;
      cout << ac.query(s) << nl;
    }
  }

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ll = long long;

const ll INF = (1 << 30) + 7;

const int N = 1e5 + 1;
const int L = 17;
vector<int> adj[N];
int anc[N][L], depth[N];
vector<int> leaf;
int node[N], add[N];

int nid = 0;
void build(int u) {
  node[++nid] = u;
  add[nid] = add[nid-1] + adj[u].empty();
  for(int j=1; j<L; j++) {
    anc[u][j] = anc[anc[u][j-1]][j-1];
  }
  for(int v : adj[u]) {
    anc[v][0] = u;
    depth[v] = depth[u] + 1;
    build(v);
  }
  if(adj[u].empty()) {
    leaf.push_back(u);
  }
}

int lca(int a, int b) {
  if(depth[a] < depth[b]) swap(a, b);
  for(int j=L-1; j>=0; j--) {
    if(anc[a][j] && depth[anc[a][j]] >= depth[b]) {
      a = anc[a][j];
    }
  }
  if(a == b) return a;
  for(int j=L-1; j>=0; j--) {
    if(anc[a][j] != anc[b][j]) {
      a = anc[a][j];
      b = anc[b][j];
    }
  }
  return anc[a][0];
}

/*
 * N_0 = 1
 * N_k = N_{k-1} + (n-1) * L^{k-1}
 */
const int M = 60;
ll multiplier[M];
int num(int n, int m) {
  return min(INF, 1 + (n-1) * multiplier[min(M-1, m)]);
}

ll get_depth(int, int, int);
ll get_leaf(int, int, int);
ll lca_depth(int, int, int, int);
ll lca_leaf(int, int, int, int);

ll search_depth(int a, int n, int m) {
  ll d = depth[leaf[0]];
  if(a <= 1 + m * d) {
    return (a - 1) / d;
  }
  ll l = 0;
  ll r = m;
  while(l < r) {
    ll k = (l + r + 1) / 2;
    if(k*d + num(n, m-k) < a) {
      r = k - 1;
    } else {
      l = k;
    }
  }
  return r;
}

int search_leaf(int a, int n, int m) {
  ll child = num(n, m-1);
  int l = 1;
  int r = n;
  while(l < r) {
    ll k = (l + r) / 2;
    if(k + add[k] * (child - 1) < a) {
      l = k + 1;
    } else {
      r = k;
    }
  }
  return r;
}

ll get_depth(int a, int n, int m) {
  ll r = search_depth(a, n, m);
  ll len = r * depth[leaf[0]];
  return len + get_leaf(a - len, n, m - r);
}

ll get_leaf(int a, int n, int m) {
  if(m == 0) return 0;
  int r = search_leaf(a, n, m);
  if(!adj[node[r]].empty()) {
    return depth[node[r]];
  }
  ll rem = r - 1 + add[r - 1] * (num(n, m-1) - 1);
  return depth[node[r]] + get_depth(a - rem, n, m-1);
}

ll lca_depth(int a, int b, int n, int m) {
  ll ra = search_depth(a, n, m);
  ll rb = search_depth(b, n, m);
  if(ra == rb) {
    ll len = ra * depth[leaf[0]];
    return len + lca_leaf(a - len, b - len, n, m - ra);
  } else {
    if(ra > rb) {
      swap(ra, rb);
      swap(a, b);
    }
    ll len = ra * depth[leaf[0]];
    int other = node[search_leaf(a - len, n, m - ra)];
    return len + depth[lca(other, leaf[0])];
  }
}

ll lca_leaf(int a, int b, int n, int m) {
  int ra = search_leaf(a, n, m);
  int rb = search_leaf(b, n, m);
  if(ra == rb) {
    ll rem = ra - 1 + add[ra - 1] * (num(n, m-1) - 1);
    return depth[node[ra]] + lca_depth(a - rem, b - rem, n, m-1);
  } else {
    return depth[lca(node[ra], node[rb])];
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  for(int i=2; i<=n; i++) {
    cin >> anc[i][0];
    adj[++anc[i][0]].push_back(i);
  }
  build(1);

  multiplier[1] = 1;
  for(int i=2; i<M; i++) {
    multiplier[i] = min(INF, multiplier[i-1] * (ll)leaf.size());
  }
  for(int i=2; i<M; i++) {
    multiplier[i] = min(INF, multiplier[i-1] + multiplier[i]);
  }

  int m;
  cin >> m;
  m++;

  int q;
  cin >> q;
  while(q--) {
    int a, b;
    cin >> a >> b;
    if(leaf.size() == 1 || a == b) {
      cout << abs(a - b) << nl;
    } else {
      ll da = get_depth(a, n, m);
      ll db = get_depth(b, n, m);
      ll dc = lca_depth(a, b, n, m);
      cout << da + db - 2*dc << nl;
    }
  }

  return 0;
}

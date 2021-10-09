#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int MAXI = 22;
const int I = MAXI-1;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

struct Edge {
  int a, b, c;
  bool operator < (const Edge& e) const {
    return c < e.c;
  }
};

const int N = MAXI*1e5+1;
int root[N], sz[N];
int find(int i) {
  if (root[i] == -1) return i;
  return root[i] = find(root[i]);
}
bool link(int i, int j) {
  i = find(i); j = find(j);
  if (i==j) return false;
  if (sz[i] < sz[j]) swap(i,j);
  sz[i] += sz[j];
  root[j] = i;
  return true;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, m, ee;
  cin >> n >> m >> ee;

  vector<Edge> edges[MAXI];
  for (int i=0; i<ee; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    --a; --b;
    for (int j=2; j<=I; j++) {
      for (int k=1; k<j; k++) {
        edges[j].push_back({j*a+k, j*b+k-1, c});
      }
    }
  }

  ll ans[MAXI];
  for (int j=2; j<=I; j++) {
    memset(root, -1, sizeof root);
    fill(sz, sz+N, 1);
    sort(edges[j].begin(), edges[j].end());
    ans[j] = 0;
    for (const Edge& e : edges[j]) {
      if (link(e.a, e.b)) {
        ans[j] += e.c;
      }
    }
  }

/*
  cout << ans[2] << nl;
  if (m > 1) cout << ans[3] << nl;
  if (m > 2) {
    ll cur = ans[4];
    ll diff = ans[5]-ans[4];
    for (int k=3; k<=m; k++) {
      cout << cur << nl;
      cur += diff;
    }
  }
*/

  cerr << nl << "diff:" << nl;
  for (int k=2; k<=m; k++) {
    cerr << ans[k+1]-ans[k] << nl;
  }

  return 0;
}

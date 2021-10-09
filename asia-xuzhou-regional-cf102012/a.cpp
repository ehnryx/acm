#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const ll MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

unsigned long long k1, k2;

unsigned long long xorShift128Plus() {
  unsigned long long k3 = k1, k4 = k2;
  k1 = k4;
  k3 ^= k3 << 23;
  k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
  return k2 + k4;
}

struct edge {
  int u, v; unsigned long long w;
};

const int N = 1e5+10;
int uf[N];

int find(int x) {
  return x == uf[x] ? x : uf[x] = find(uf[x]);
}
void merge(int a, int b) {
  uf[find(a)] = find(b);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T; cin >> T;
  while (T--) {
    int n, m; cin >> n >> m >> k1 >> k2;
    iota(uf, uf + n, 0);
    vector<edge> edges(m);
    unordered_set<ull> s;
    for (int i = 0; i < m; i++) {
      int u = xorShift128Plus() % n;
      int v = xorShift128Plus() % n;
      ull w = xorShift128Plus();
      if (s.count(w)) assert(0);
      s.insert(w);
      edges[i] = {u, v, w};
    }
    sort(edges.begin(), edges.end(), [&](const edge& a, const edge& b) {
      return a.w < b.w;
    });
    ll ans = 0;
    for (const auto& e : edges) {
      if (find(e.u) != find(e.v)) {
        merge(e.u, e.v);
        ans = (ans+e.w%MOD)%MOD;
      }
    }
    for (int i = 0; i < n; i++) {
      if (find(i) != find(0)) {
        cout << 0 << nl;
        goto bad;
      }
    }
    cout << ans << nl;
    bad:;
  }

  return 0;
}

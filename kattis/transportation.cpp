#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
//%:include "graph/dinic.h"
%:include "graph/push_relabel.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int vn, n, m, k;
  cin >> vn >> n >> m >> k;
  //dinic<int> g(vn + 2*k + 2);
  push_relabel<int> g(vn + 2*k + 2);
  const int source = vn + 2*k;
  const int sink = source + 1;

  int rid = 0;
  unordered_map<string, int> remap;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    g.add_edge(source, rid, 1);
    remap[s] = rid++;
  }
  for(int i=0; i<m; i++) {
    string s;
    cin >> s;
    g.add_edge(rid, sink, 1);
    remap[s] = rid++;
  }

  for(int i=0; i<k; i++) {
    int kn;
    cin >> kn;
    for(int j=0; j<kn; j++) {
      string s;
      cin >> s;
      if(!remap.count(s)) remap[s] = rid++;
      g.add_edge(remap[s], vn + i, 1);
      g.add_edge(vn + k + i, remap[s], 1);
    }
    g.add_edge(vn + i, vn + k + i, 1);
  }

  cout << g.flow(source, sink) << nl;

  return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define FILENAME "graph"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const char nl = '\n';

const int N = 1e5+1;
vector<int> adj[N];
int in[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);

  int n, m, k;
  cin >> n >> m >> k;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    in[b]++;
  }

  set<int> out, store;
  for(int i=1; i<=n; i++) {
    if(in[i] == 0) {
      out.insert(i);
    }
  }

  vector<int> ans;
  vector<pii> edges;
  while(!out.empty() || !store.empty()) {
    if(!out.empty()) {
      while(k>0 && out.size() > 1) {
        auto it = out.begin();
        store.insert(*it);
        out.erase(it);
        --k;
      }
      if(k>0 && out.size() == 1 && !store.empty() && *out.begin() < *store.rbegin()) {
        auto it = out.begin();
        store.insert(*it);
        out.erase(it);
        --k;
      }
    }
    int u = -1;
    if(!out.empty()) {
      u = *out.begin();
      out.erase(out.begin());
    } else {
      assert(!store.empty());
      u = *store.rbegin();
      store.erase(prev(store.end()));
      edges.push_back(make_pair(ans.back(), u));
    }
    assert(u != -1);
    ans.push_back(u);
    for(int v:adj[u]) {
      in[v]--;
      if(in[v] == 0) {
        out.insert(v);
      }
    }
  }

  //assert(ans.size() == n);
  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;
  cout << edges.size() << nl;
  for(auto [a, b] : edges) {
    cout << a << " " << b << nl;
  }

  return 0;
}

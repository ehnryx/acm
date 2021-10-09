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

const int MAXN = 1e5+10;
int n, m;
set<int> adj[MAXN];
int killed[MAXN];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  cin >> n >> m;
  for(int i=0;i<m;i++) {
    int u, v;
    cin >> u >> v;
    adj[u].insert(v);
    adj[v].insert(u);
  }
  set<int> q;
  for(int i=1;i<=n;i++) {
    if(adj[i].size()==2) q.insert(i);
  }
  while(q.size()) {
    int u = *q.begin();
    //cerr << "KILLING " << u <<endl;
    killed[u] = 1;
    q.erase(q.begin());
    int l = *adj[u].begin();
    int r = *adj[u].rbegin();
    if (adj[l].size() == 2) q.erase(l);
    if (adj[r].size() == 2) q.erase(r);
    adj[l].erase(u);
    adj[r].erase(u);
    if (l!=r) {
      adj[l].insert(r);
      adj[r].insert(l);
    }
    if (adj[l].size()==2) q.insert(l);
    if (adj[r].size()==2) q.insert(r);
  }
  int cnt = 0;
  for(int i=1;i<=n;i++) {
    if(!killed[i]) cnt++;
  }
  if (cnt<=2) cout << "Yes" <<endl;
  else cout << "No" <<endl;
  return 0;
}

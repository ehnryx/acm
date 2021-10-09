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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 4e5+1;
vector<int> adj[N],rev[N];
int indeg[N],outdeg[N];
int c[N],val[N];

struct Node {
  int i,v;
  bool operator < (const Node& o) const {
    return v < o.v;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=1;i<=n;i++) {
    int d;
    cin>>c[i]>>d;
    for(int j=0;j<d;j++) {
      int v;
      cin>>v;
      adj[v].push_back(i);
      rev[i].push_back(v);
      outdeg[v]++;
      indeg[i]++;
    }
  }

  queue<int> nxt;
  for(int i=1;i<=n;i++) {
    if(outdeg[i]==0) {
      nxt.push(i);
    }
  }
  while(!nxt.empty()) {
    int u = nxt.front();
    nxt.pop();
    val[u] = max(val[u], c[u]);
    for(int v:rev[u]) {
      val[v] = max(val[v], val[u]);
      if(--outdeg[v] == 0) {
        nxt.push(v);
      }
    }
  }

  int ans = 0;
  priority_queue<Node> dijk;
  for(int i=1;i<=n;i++) {
    if(indeg[i]==0) {
      dijk.push({i,val[i]});
    }
  }
  for(int t=0;!dijk.empty();t++) {
    Node cur = dijk.top();
    dijk.pop();
    ans = max(ans, c[cur.i]+t);
    for(int v:adj[cur.i]) {
      if(--indeg[v] == 0) {
        dijk.push({v,val[v]});
      }
    }
  }
  cout<<ans<<nl;

  return 0;
}

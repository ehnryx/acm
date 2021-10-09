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

const int N = 3e5+1;
int l[N], r[N];

vector<int> dag[N], rev[N];
int indeg[N], outdeg[N];
int ans[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin >> n >> m;

  for(int i=1; i<=n; i++) {
    cin >> l[i] >> r[i];
  }

  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    dag[a].push_back(b);
    rev[b].push_back(a);
    outdeg[a]++;
    indeg[b]++;
  }

  // fix left
  {
    queue<int> tp;
    for(int i=1; i<=n; i++) {
      if(indeg[i] == 0) {
        tp.push(i);
      }
    }

    int viscnt = 0;
    while(!tp.empty()) {
      int u = tp.front();
      tp.pop();
      viscnt++;
      for(int v:dag[u]) {
        l[v] = max(l[v], l[u] + 1);
        if(--indeg[v] == 0) {
          tp.push(v);
        }
      }
    }

    if(viscnt<n) {
      cout << -1 << nl;
      return 0;
    }
  }

  // fix right
  {
    queue<int> tp;
    for(int i=1; i<=n; i++) {
      if(outdeg[i] == 0) {
        tp.push(i);
      }
    }

    int viscnt = 0;
    while(!tp.empty()) {
      int u = tp.front();
      tp.pop();
      viscnt++;
      for(int v:rev[u]) {
        r[v] = min(r[v], r[u] - 1);
        if(--outdeg[v] == 0) {
          tp.push(v);
        }
      }
    }

    if(viscnt<n) {
      cout << -1 << nl;
      return 0;
    }
  }

  priority_queue<pii> nxt, take;
  for(int i=1; i<=n; i++) {
    if(l[i] > r[i]) {
      cout << -1 << nl;
      return 0;
    }
    nxt.push(make_pair(r[i], i));
  }

  for(int i=n; i>0; i--) {
    while(!nxt.empty() && nxt.top().first == i) {
      int j = nxt.top().second;
      take.push(make_pair(l[j], j));
      nxt.pop();
    }
    if(take.empty() || take.top().first > i) {
      cout << -1 << nl;
      return 0;
    }
    int j = take.top().second;
    ans[i] = j;
    take.pop();
  }

  for(int i=1; i<=n; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}

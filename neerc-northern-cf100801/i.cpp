#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "insider"

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

const int N = 1e5+1;
vector<int> adj[N];
vector<int> vals[N];
int mid[N];
int ans[2*N], idx[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  if(fopen(FILENAME ".in", "r")) {
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
  }

  int n, m;
  cin >> n >> m;
  int a[m], b[m], c[m];
  set<int> active;
  for(int i=0; i<m; i++) {
    cin >> a[i] >> b[i] >> c[i];
    mid[b[i]]++;
    active.insert(i);
    adj[a[i]].push_back(i);
    adj[c[i]].push_back(i);
  }

  queue<int> nxt;
  for(int i=1; i<=n; i++) {
    if(mid[i] == 0) {
      nxt.push(i);
    }
  }

  vector<int> order;
  while(!nxt.empty()) {
    int u = nxt.front();
    nxt.pop();
    order.push_back(u);
    for(int i : adj[u]) {
      if(active.count(i)) {
        active.erase(i);
        vals[u].push_back(i);
        mid[b[i]]--;
        if(mid[b[i]] == 0) {
          nxt.push(b[i]);
        }
      }
    }
  }
  reverse(order.begin(), order.end());
  assert(order.size() == n);

  int lb, rb;
  lb = rb = N;
  for(int u : order) {
    int sz = vals[u].size();
    int good = 0;
    for(int i : vals[u]) {
      assert(a[i] == u || c[i] == u);
      if(c[i] == u) swap(a[i], c[i]);
      good += (idx[b[i]] < idx[c[i]]);
    }
    if(2*good >= sz) {
      idx[u] = --lb;
      ans[idx[u]] = u;
    } else {
      idx[u] = rb++;
      ans[idx[u]] = u;
    }
  }

  assert(rb - lb == n);
  for(int i=lb; i<rb; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}

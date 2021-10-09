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

struct Item {
  int a, b, c;
};

const int N = 1e5+1;
vector<int> adj[N];
unordered_set<int> skip[N];
bool vis[N];

vector<Item> ans;

int solve(int u, int p) {
  if(vis[u]) {
    skip[u].insert(p);
    return 0;
  }

  vis[u] = true;
  vector<int> child;
  for(int v:adj[u]) {
    if(v == p || skip[u].count(v)) continue;
    int got = solve(v, u);
    if(got) {
      ans.push_back({got, v, u});
    } else {
      child.push_back(v);
    }
  }

  for(int i=1; i<child.size(); i+=2) {
    ans.push_back({child[i-1], u, child[i]});
  }
  return (child.size() % 2 ? child.back() : 0);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  for(int i=1; i<=n; i++) {
    solve(i, 0);
  }

  cout << ans.size() << nl;
  for(const Item& it : ans) {
    cout << it.a << " " << it.b << " " << it.c << nl;
  }

  return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+1;
int par[N];
vector<int> adj[N];
int pre[N], post[N];
int prei, posti;

void dfs(int u) {
  pre[u] = prei++;
  for (int v : adj[u]) {
    dfs(v);
  }
  post[u] = posti++;
}

bool anc(int x, int y) {
  return (pre[x]<=pre[y] && post[x]>=post[y]);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, q;
  cin >> n >> q;

  vector<int> root;
  for (int i=0; i<n; i++) {
    cin >> par[i];
    if (par[i] == -1) root.push_back(i);
    else adj[par[i]].push_back(i);
  }
  for (int r : root) {
    dfs(r);
  }

  while (q--) {
    int x, y;
    cin >> x >> y;
    if (anc(y,x)) {
      cout << "Yes" << nl;
    } else {
      cout << "No" << nl;
    }
  }

  return 0;
}

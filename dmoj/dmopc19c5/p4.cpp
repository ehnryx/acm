//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<17;
ll val[N];
int par[N];
ll st[2*N];

int query(ll v, int i=1) {
  if(i>=N) return i-N;
  if(st[2*i] >= v) return query(v, 2*i);
  else return query(v, 2*i+1);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    cin >> val[i];
  }
  for(int i=1; i<=n; i++) {
    cin >> par[i];
    val[i] += val[par[i]];
    st[i+N] = val[i];
  }
  for(int i=N-1; i>0; i--) {
    st[i] = max(st[2*i], st[2*i+1]);
  }

  for(int i=0; i<m; i++) {
    ll v, c;
    cin >> v >> c;
    if(v >= c || v+st[1] < c) {
      cout << -1 << nl;
    } else {
      cout << query(c-v) << nl;
    }
  }

  return 0;
}

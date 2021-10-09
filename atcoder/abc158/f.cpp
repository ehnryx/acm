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
const ll MOD = 998244353;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1 << 19;
int far[N], dp[N];

int st[2*N];
void insert(int x, int v) {
  for(x+=N; x>0; x/=2) {
    st[x] = max(st[x], v);
  }
}
int query(int l, int r) {
  int res = 0;
  for(l+=N, r+=N+1; l<r; l/=2, r/=2) {
    if(l&1) res = max(res, st[l++]);
    if(r&1) res = max(res, st[--r]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  map<int,int> rmp;
  map<int,int> maxd;
  vector<pair<int,int>> p;
  for(int i=0; i<n; i++) {
    int x, d;
    cin >> x >> d;
    maxd[x] = max(maxd[x], d);
    rmp[x]; rmp[x+d-1];
  }

  int rid = 0;
  for(auto& it : rmp) {
    it.second = rid++;
  }

  for(auto it = maxd.rbegin(); it != maxd.rend(); it++) {
    int x, d; tie(x, d) = *it;
    int y = rmp[x];
    far[y] = max(query(y, rmp[x+d-1]), rmp[x+d-1]);
    insert(y, far[y]);
  }

  dp[rid] = 1;
  for(int i=rid-1; i>=0; i--) {
    // skip + take
    dp[i] = (dp[i+1] + dp[far[i] + 1]) % MOD;
  }
  cout << dp[0] << nl;

  return 0;
}

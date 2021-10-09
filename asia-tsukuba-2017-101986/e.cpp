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

const int N = 1<<19;
int dp[N], pre[N];

int st[2*N];
void insert(int i, int v) {
  st[i+=N] = v;
  for(i/=2;i;i/=2) {
    st[i] = min(st[2*i], st[2*i+1]);
  }
}
int query(int l, int r) {
  int res = INF;
  for(l+=N,r+=N+1; l<r; l/=2,r/=2) {
    if(l&1) res = min(res, st[l++]);
    if(r&1) res = min(res, st[--r]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,k;
  cin>>n>>k;
  string s,t;
  cin>>s>>t;

  for(int i=1;i<n;i++) {
    pre[i] = pre[i-1] + (t[i] != t[i-1]);
  }

  memset(st,INF,sizeof st);
  insert(0, 0);
  for(int i=0;i<n;i++) {
    if(s[i]==t[i]) {
      dp[i+1] = dp[i];
    } else {
      int top = query(max(0,i-k+1), i) + pre[i] + 2;
      dp[i+1] = (top+1)/2;
    }
    insert(i+1, 2*dp[i+1] - pre[i+1]);
  }
  cout<<dp[n]<<nl;

  return 0;
}

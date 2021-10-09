#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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

const int N = 2e5+1;
const int M = 1e6+1;
int a[N], t[N], orig[N];
int ans[M];

void solve(int n, int l, int r, int lv, int rv) {
  if(l>r) return;

  int m = (l+r)/2;
  int cur = 0;
  int cnt = 1;
  for(int i=0;i<n;i++) {
    if(cur+a[i] > t[m]) {
      cur = 0;
      cnt++;
    }
    cur += a[i];
  }
  ans[t[m]] = cnt;

  if(cnt == lv) {
    for(int i=t[l];i<t[m];i++) {
      ans[i] = cnt;
    }
  } else {
    solve(n, l, m-1, lv, cnt);
  }

  if(cnt == rv) {
    for(int i=t[r];i>t[m];i--) {
      ans[i] = cnt;
    }
  } else {
    solve(n, m+1, r, cnt, rv);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  int maxv = 0;
  for(int i=0;i<n;i++) {
    cin>>a[i];
    maxv = max(maxv, a[i]);
  }

  int m;
  cin>>m;
  for(int i=0;i<m;i++) {
    cin>>t[i];
    orig[i] = t[i];
  }
  sort(t,t+m);

  solve(n, lower_bound(t,t+m,maxv)-t, m-1, n, 1);
  for(int i=0;i<m;i++) {
    if(orig[i]<maxv) cout<<"Impossible"<<nl;
    else cout<<ans[orig[i]]<<nl;
  }

  return 0;
}

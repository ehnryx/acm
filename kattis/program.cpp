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

const int N = 1<<20;
int cnt[N];
ll st[2*N];
void build() {
  for(int i=N-1;i>0;i--) {
    st[i] = st[2*i] + st[2*i+1];
  }
}
ll query(int l, int r) {
  ll res = 0;
  for(l+=N,r+=N+1;l<r;l/=2,r/=2) {
    if(l&1) res += st[l++];
    if(r&1) res += st[--r];
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,k;
  cin>>n>>k;
  for(int i=0;i<k;i++) {
    int a;
    cin>>a;
    cnt[a]++;
  }

  for(int i=1;i<n;i++) {
    if(cnt[i]) {
      for(int j=0;j<n;j+=i) {
        st[N+j] += cnt[i];
      }
    }
  }
  build();

  int m;
  cin>>m;
  for(int i=0;i<m;i++) {
    int l,r;
    cin>>l>>r;
    cout<<query(l,r)<<nl;
  }

  return 0;
}

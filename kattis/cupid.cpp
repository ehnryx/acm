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

const int N = 5e4+1;
const int S = 240;
const int M = N/S+1;

struct Query {
  int l,r,i;
  bool operator < (const Query& o) const {
    if(l/S != o.l/S) return l < o.l;
    return ((l/S)%2 ? r > o.r : r < o.r);
  }
};

const int K = 1e6+1;
int ac[K], bc[K];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m,k;
  cin>>n>>m>>k;
  int a[n],b[n];
  for(int i=0;i<n;i++) {
    cin>>a[i];
  }
  for(int i=0;i<n;i++) {
    cin>>b[i];
  }

  Query q[m];
  int ans[m];
  for(int i=0;i<m;i++) {
    cin>>q[i].l>>q[i].r;
    q[i].i = i;
  }
  sort(q,q+m);

  int cur = 0;
  function<void(int)> insert = [&](int i) {
    ac[a[i]]++;
    bc[b[i]]++;
    if(a[i]==b[i]) {
      cur++;
    } else {
      if(ac[a[i]]<=bc[a[i]]) cur++;
      if(bc[b[i]]<=ac[b[i]]) cur++;
    }
  };
  function<void(int)> remove = [&](int i) {
    if(a[i]==b[i]) {
      cur--;
    } else {
      if(ac[a[i]]<=bc[a[i]]) cur--;
      if(bc[b[i]]<=ac[b[i]]) cur--;
    }
    ac[a[i]]--;
    bc[b[i]]--;
  };

  int left = 0;
  int right = -1;
  for(int i=0;i<m;i++) {
    while(right<q[i].r) insert(++right);
    while(left>q[i].l) insert(--left);
    while(right>q[i].r) remove(right--);
    while(left<q[i].l) remove(left++);
    ans[q[i].i] = cur;
  }

  for(int i=0;i<m;i++) {
    cout<<ans[i]<<nl;
  }

  return 0;
}

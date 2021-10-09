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

const int N = 25e4+1;
int f[N];

void init() {
  memset(f,0,sizeof f);
}
void insert(int x, int v) {
  for(;x<N;x+=x&-x) {
    f[x] += v;
  }
}
void update(int l, int r) {
  insert(l, 1);
  insert(r+1, -1);
}
int query(int x) {
  int res = 0;
  for(;x>0;x-=x&-x) {
    res += f[x];
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  int a[n+1],b[n+1];
  for(int i=1;i<=n;i++) {
    cin>>a[i];
  }
  for(int i=1;i<=n;i++) {
    cin>>b[i];
  }

  ll ans = INFLL;

  //cerr<<nl<<"LEFT"<<nl;
  // left
  {
    init();
    ll cur = 0;
    set<int> left, right;
    for(int i=1;i<=n;i++) {
      if(2*a[i] <= n+1) {
        //cerr<<"ins left "<<i<<nl;
        left.insert(i);
      } else {
        //cerr<<"ins right "<<i<<nl;
        right.insert(i);
      }
    }
    for(int i=1;i<=n;i++) {
      int j;
      if(2*b[i] >= n+1) {
        j = *left.begin();
        left.erase(left.begin());
      } else {
        j = *right.begin();
        right.erase(right.begin());
      }
      //cerr<<"match "<<i<<" w/ "<<j<<nl;
      cur += j-i + query(j);
      update(1, j);
    }
    //cerr<<cur<<nl;
    ans = min(ans, cur);
  }

  //cerr<<nl<<"RIGHT"<<nl;
  // right
  {
    init();
    ll cur = 0;
    set<int> left, right;
    for(int i=1;i<=n;i++) {
      if(2*a[i] >= n+1) {
        //cerr<<"ins left "<<i<<nl;
        left.insert(i);
      } else {
        //cerr<<"ins right "<<i<<nl;
        right.insert(i);
      }
    }
    for(int i=1;i<=n;i++) {
      int j;
      if(2*b[i] <= n+1) {
        j = *left.begin();
        left.erase(left.begin());
      } else {
        j = *right.begin();
        right.erase(right.begin());
      }
      //cerr<<"match "<<i<<" w/ "<<j<<nl;
      cur += j-i + query(j);
      update(1, j);
    }
    //cerr<<cur<<nl;
    ans = min(ans, cur);
  }

  //cerr<<nl<<"MID"<<nl;
  // mid
  {
    init();
    ll cur = 0;
    set<int> left, right;
    int mid = -1;
    for(int i=1;i<=n;i++) {
      if(2*a[i] < n+1) {
        left.insert(i);
        //cerr<<"ins left "<<i<<nl;
      } else if (2*a[i] > n+1) {
        right.insert(i);
        //cerr<<"ins right "<<i<<nl;
      } else {
        mid = i;
      }
    }
    for(int i=1;i<=n;i++) {
      int j;
      if(2*b[i] > n+1) {
        j = *left.begin();
        left.erase(left.begin());
      } else if (2*b[i] < n+1) {
        j = *right.begin();
        right.erase(right.begin());
      } else {
        //cerr<<"ins mid "<<i<<nl;
        j = mid;
      }
      //cerr<<"match "<<i<<" w/ "<<j<<nl;
      cur += j-i + query(j);
      update(1, j);
    }
    //cerr<<cur<<nl;
    ans = min(ans, cur);
  }

  cout<<ans<<nl;

  return 0;
}

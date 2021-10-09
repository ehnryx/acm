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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int sqr(int x) {
  return x*x;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  int x[n],y[n];
  for(int i=0;i<n;i++) {
    cin>>x[i]>>y[i];
  }

  auto dist = [&](int i, int j) {
    return sqrtl(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
  };

  auto cp = [&](int i, int j, int k) {
    return (x[j]-x[i])*(y[k]-y[i]) - (y[j]-y[i])*(x[k]-x[i]);
  };

  auto between = [&](int i, int j, int k) {
    //return cp(i,j,k) == 0 && abs(dist(i,k)+dist(k,j)-dist(i,j)) < EPS;
    return abs(dist(i,k)+dist(k,j)-dist(i,j)) < EPS;
  };

  auto positive = [&](int i, int j, int k) {
    return cp(i,j,k) > 0;
  };

  auto area = [&](int i, int j, int k) {
    return abs(cp(i,j,k));
  };

  int cnt[n][n];
  memset(cnt,0,sizeof cnt);
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      if(i==j) continue;
      for(int k=0;k<n;k++) {
        if(k==i||k==j) continue;
        cnt[i][j] += (between(i,j,k) || positive(i,j,k));
      }
    }
  }

  auto value = [&](int a, int b) {
    ld res = 1;
    for(int i=0;i<b;i++) {
      if(i<b-2) {
        res *= a-2-i;
      } else {
        res *= i+1;
      }
      res /= n-i;
    }
    return res / (n-b);
  };

  ld count[n+1];
  for(int m=2;m<n;m++) {
    count[m-2] = 0;
    for(int i=2;i<=m;i++) {
      count[m-2] += value(m,i);
    }
  }

  for(int i=0;i<n;i++) {
    ld cur = 0;
    for(int j=0;j<n;j++) {
      if(i==j) continue;
      for(int k=0;k<j;k++) {
        if(i==k) continue;
        if(positive(j,k,i)) {
          cur += count[cnt[k][j]] * area(i,j,k);
        } else if(positive(k,j,i)) {
          cur += count[cnt[j][k]] * area(i,j,k);
        }
      }
    }
    cout<<cur/2<<nl;
  }

  return 0;
}

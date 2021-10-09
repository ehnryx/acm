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

const int M = 1000;
const int N = 1e5;
int x[N],y[N];

ll cp(int x1, int y1, int x2, int y2) {
  return (ll)x1*y2 - (ll)y1*x2;
}

int solve(int n, int a, int b) {
  int cnt = 0;
  for(int i=0;i<n;i++) {
    cnt += (cp(x[a]-x[b],y[a]-y[b], x[a]-x[i],y[a]-y[i]) == 0);
  }
  return cnt;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  int p;
  cin>>p;
  int need = (n*p+99)/100;
  for(int i=0;i<n;i++) {
    cin>>x[i]>>y[i];
  }
  if(n==1) {
    cout<<"possible"<<nl;
    return 0;
  }

  for(int it=0;it<M;it++) {
    int a = rng()%n;
    int b = rng()%n;
    while(a==b) b = rng()%n;
    if(solve(n,a,b) >= need) {
      cout<<"possible"<<nl;
      return 0;
    }
  }
  cout<<"impossible"<<nl;
  return 0;

  return 0;
}

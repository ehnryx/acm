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

ll egcd(ll a, ll b, ll& x, ll &y) {
  if (!b) {x = 1; y = 0; return a;}//to ensure d>=0: x=sgn(a);y=0;return abs(a);
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d; }
bool chin_rem(ll a1, ll m1, ll a2, ll m2, ll& A, ll& M) {
  ll X1, X2, d = egcd(m1, m2, X1, X2); if (a1 % d != a2 % d) return false;
  M = m1/d*m2, A = ((X1*(a2/d)%m2*m1 + X2*(a1/d)%m1*m2 + a1%d)%M + M)%M;
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int a,b,c,d,e,f,g;
  cin>>a>>b>>c>>d>>e>>f>>g;

  vector<int> v;
  for(int x=1;2*x<min(a,b);x++) {
    v.push_back(x*(a-2*x)*(b-2*x));
  }
  sort(v.begin(),v.end(),greater<int>());

  ll A,M,X,Y;
  chin_rem(c,v[0],d,v[1],A,M);
  chin_rem(A,M,e,v[2],X,Y);
  X += f/Y * Y;
  while(X<f) X += Y;
  while(X>g) X -= Y;
  cout<<(ll)X<<nl;

  return 0;
}

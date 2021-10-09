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
const ld EPS = 1e-6;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld search(const pt& a, const pt& b, const pt& c, const pt& d) {
  //cerr<<"search "<<a<<" "<<b<<" "<<c<<" "<<d<<nl;
  ld dist = abs(a-b);
  assert(abs(dist-abs(c-d))<EPS);
  pt ab = (b-a)/dist;
  pt cd = (d-c)/dist;
  ld l = 0;
  ld r = dist;
  while(r-l>EPS) {
    ld lm = (2*l+r)/3;
    ld rm = (l+2*r)/3;
    ld lval = abs((a+ab*lm) - (c+cd*lm));
    ld rval = abs((a+ab*rm) - (c+cd*rm));
    if(lval < rval) {
      r = rm;
    } else {
      l = lm;
    }
  }
  return abs((a+ab*l) - (c+cd*l));
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  vector<pt> a;
  for(int i=0;i<n;i++) {
    int x,y;
    cin>>x>>y;
    a.push_back(pt(x,y));
  }

  int m;
  cin>>m;
  vector<pt> b;
  for(int i=0;i<m;i++) {
    int x,y;
    cin>>x>>y;
    b.push_back(pt(x,y));
  }

  ld ans = INF;
  pt A = a[0];
  pt B = b[0];
  for(int i=1,j=1;i<n&&j<m;) {
    //cerr<<"@ "<<i<<" "<<j<<" w/ "<<A<<" "<<B<<nl;
    ld adist = abs(A-a[i]);
    ld bdist = abs(B-b[j]);
    if(adist < bdist) {
      pt nB = B + (b[j]-B) * adist / bdist;
      ans = min(ans, search(A,a[i], B,nB));
      A = a[i];
      B = nB;
      i++;
    } else {
      pt nA = A + (a[i]-A) * bdist / adist;
      ans = min(ans, search(A,nA, B,b[j]));
      A = nA;
      B = b[j];
      j++;
    }
  }
  cout<<ans<<nl;

  return 0;
}

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

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }

// Projection of (a -> p) to vector (a -> b), SIGNED - positive in front
inline ld proj_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) / abs(b - a);
}

// SIGNED distance. Pt on the right of vector (a -> b) will be NEGATIVE.
inline ld lp_dist(const pt &a, const pt &b, const pt &p) {
  return cp(b - a, p - a) / abs(b - a);
}

ld sqr(ld x) { return x*x; }

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  pt p[3];
  for(int i=0;i<3;i++) {
    int a,b;
    cin>>a>>b;
    p[i] = pt(a,b);
  }

  int x,y,r;
  cin>>x>>y>>r;
  pt v = pt(x,y);

  ld d[3], lpd[3];
  d[1] = d[2] = INF;
  for(int t=1;t<3;t++) {
    lpd[t] = abs(lp_dist(p[0],p[0]+v,p[t]));
    if(lpd[t] < 2*r) {
      d[t] = proj_dist(p[0],p[0]+v,p[t]);
      if(d[t]<0) d[t] = INF;
    }
  }

  if(min(d[1],d[2]) > INF-1) {
    cout<<5<<nl;
  }

  else if(min(d[1],d[2]) == d[1]) {
    ld shift = sqrt(sqr(2*r)-sqr(lpd[1]));
    assert(d[1]-shift+EPS>0);
    pt c = p[0] + v/abs(v)*(d[1]-shift);
    assert(abs(abs(c-p[1])-2*r) < EPS);
    if(abs(lp_dist(c,p[1],p[2])) < 2*r
        && proj_dist(c,p[1],p[2]) > 0) {
      cout<<1<<nl;
    } else {
      cout<<3<<nl;
    }
  }

  else {
    ld shift = sqrt(sqr(2*r)-sqr(lpd[2]));
    assert(d[2]-shift+EPS>0);
    pt c = p[0] + v/abs(v)*(d[2]-shift);
    assert(abs(abs(c-p[2])-2*r) < EPS);
    if(abs(lp_dist(c,p[2],p[1])) < 2*r
        && proj_dist(c,p[2],p[1]) > 0) {
      cout<<2<<nl;
    } else {
      cout<<4<<nl;
    }
  }

  return 0;
}

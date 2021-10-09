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
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Line {
  ld a,b,c;
  friend ostream& operator << (ostream& os, const Line& v) {
    return os<<v.a<<","<<v.b<<","<<v.c;
  }
};

Line convert(const pt& a, const pt& b) {
  if(abs(a.real()-b.real())<EPS) {
    return {1,0,a.real()};
  } else {
    ld m = (a.imag()-b.imag())/(a.real()-b.real());
    return {m,-1,m*a.real()-a.imag()};
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=0;i<n;i++) {
    ld x,y;
    cin>>x>>y;
    pt p(x,y);
    ld d = abs(p);
    ld ang = acos(1/d);
    pt c = p/d;
    pt a = c * exp(pt(0,ang));
    pt b = c * exp(pt(0,-ang));
    cout<<"("<<convert(a,p)<<","<<convert(b,p)<<")"<<nl;
  }

  return 0;
}

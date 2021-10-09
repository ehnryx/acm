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

struct Frac {
  ll n, d;
  Frac(ll a, ll b) {
    n = a; d = b;
    if(d<0) {
      n = -n;
      d = -d;
    }
    assert(d!=0);
  }
  bool operator < (const Frac& o) const { return n*o.d < d*o.n; }
  bool operator == (const Frac& o) const { return n*o.d == d*o.n; }
};

template <class T>
bool intersect(const T& a, const T& b, const T& c, const T& d) {
  if(!(a<b) || !(c<d)) return false;
  return (a<c && c<b) || (a<d && d<b) || (c<a && a<d) || (c<b && b<d)
    || (a==c && b==d);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  map<char,int> dirmap;
  dirmap['N'] = dirmap['S'] = 1;

  int t;
  cin>>t;

  char c[2]; int x[2],y[2],s[2],w[2],l[2];
  for(int i=0;i<2;i++) {
    cin>>c[i]>>x[i]>>y[i]>>s[i]>>w[i]>>l[i];
    x[i] *= 2;
    y[i] *= 2;
    s[i] *= 2;
  }

  if(dirmap[c[0]]==dirmap[c[1]]) {
    if(dirmap[c[0]]) {
      swap(x,y);
    }
    // check intersection
    if(!intersect(y[0]-w[0],y[0]+w[0],y[1]-w[1],y[1]+w[1])) {
      cout<<"safe"<<nl;
      return 0;
    }

    // check speed
    for(int i=0;i<2;i++) {
      if(c[i]=='W' || c[i]=='S') {
        s[i] *= -1;
      }
    }
    if(s[0] == s[1]) {
      cout<<"safe"<<nl;
      return 0;
    }

    bool bug = false;
    for(int i:{-1,1}) {
      for(int j:{-1,1}) {
        Frac tm((x[1]+i*l[1]) - (x[0]+j*l[0]), s[0]-s[1]);
        bug |= (Frac(0,1)<tm && tm<Frac(t,1));
      }
    }
    if(bug) {
      cout<<"crash"<<nl;
    } else {
      cout<<"safe"<<nl;
    }
  }

  else {
    if(dirmap[c[0]]) {
      swap(c[0],c[1]);
      swap(x[0],x[1]);
      swap(y[0],y[1]);
      swap(s[0],s[1]);
      swap(w[0],w[1]);
      swap(l[0],l[1]);
    }
    if(c[0] == 'W') {
      x[1] = x[0] + x[0]-x[1];
    } else {
      assert(c[0]=='E');
    }
    if(c[1] == 'S') {
      y[1] = y[0] + y[0]-y[1];
    } else {
      assert(c[1]=='N');
    }
    Frac hs((x[1]-w[1]) - (x[0]+l[0]), s[0]);
    Frac ht((x[1]+w[1]) - (x[0]-l[0]), s[0]);
    Frac vs((y[0]-w[0]) - (y[1]+l[1]), s[1]);
    Frac vt((y[0]+w[0]) - (y[1]-l[1]), s[1]);
    hs = max(hs, Frac(0,1));
    ht = min(ht, Frac(t,1));
    vs = max(vs, Frac(0,1));
    vt = min(vt, Frac(t,1));
    if(intersect(hs,ht,vs,vt)) {
      cout<<"crash"<<nl;
    } else {
      cout<<"safe"<<nl;
    }
  }

  return 0;
}

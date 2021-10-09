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

struct p3d {
  ld x,y,z;
  p3d operator - () const {
    return {-x, -y, -z};
  }
  p3d operator - (const p3d& o) const {
    return {x-o.x, y-o.y, z-o.z};
  }
};
p3d cross(const p3d& a, const p3d& b) {
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}
ld dot(const p3d& a, const p3d& b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    p3d p[4];
    for(int i=0;i<4;i++) {
      cin>>p[i].x>>p[i].y>>p[i].z;
    }
    p3d x;
    cin>>x.x>>x.y>>x.z;
    for(int i=0;i<4;i++) {
      p3d d = p[i];
      p3d a = p[(i+1)%4];
      p3d b = p[(i+2)%4];
      p3d c = p[(i+3)%4];
      p3d n = cross(b-a,c-a);
      if(dot(n, d-a) > 0) {
        n = -n;
      }
      if(dot(n, x-a) > EPS) {
        cout<<"Y";
      } else {
        cout<<"N";
      }
    }
    cout<<nl;
  }

  return 0;
}

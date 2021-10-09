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



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,a,b,q;
  cin>>n>>a>>b>>q;

  int x[a]; char c[a];
  for(int i=0;i<a;i++) {
    cin>>x[i]>>c[i];
  }

  int ph = 0;
  int py = 0;
  map<int,pii> segs;
  for(int i=0;i<b;i++) {
    int y, h;
    cin>>y>>h;
    segs[y] = pii(py, ph);
    ph = h;
    py = y;
  }
  segs[n+1] = pii(py, ph);

  function<int(int)> traverse = [&](int u) {
    for(;;) {
      auto it = segs.upper_bound(u);
      int r = it->first;
      int l = it->second.first;
      int h = it->second.second;
      if(h == 0 || u < l) {
        break;
      }
      int d = l-h;
      int v = u - (u-h)/d * d;
      assert(v>=h && v-h<r-l);
      u = v;
    }
    return u;
  };

  unordered_map<int,char> ch;
  for(int i=0;i<a;i++) {
    int u = traverse(x[i]);
    if(ch.count(u)) assert(ch[u] == c[i]);
    ch[u] = c[i];
  }

  for(int i=0;i<q;i++) {
    int u;
    cin>>u;
    u = traverse(u);
    if(ch.count(u)) {
      cout<<ch[u];
    } else {
      cout<<'?';
    }
  }
  cout<<nl;

  return 0;
}

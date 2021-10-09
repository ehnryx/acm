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



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,k;
  cin>>n>>k;
  int x[n],y[n];
  ld d[n];
  for(int i=0;i<n;i++) {
    cin>>x[i]>>y[i];
    d[i] = hypot(x[i],y[i]);
  }

  auto count = [&](ld r) {
    vector<pair<ld,int>> p;
    for(int i=0;i<n;i++) {
      if(d[i]>2*r) continue;
      ld ang = atan2(y[i],x[i]);
      ld diff = acos(d[i]/2/r);
      ld s = ang-diff;
      ld t = ang+diff;
      for(int j=0;j<3;j++) {
        p.push_back(make_pair(s+j*2*M_PI,1));
        p.push_back(make_pair(t+j*2*M_PI,-1));
      }
    }
    sort(p.begin(),p.end());

    int res = 0;
    int cur = 0;
    for(const auto& it:p) {
      cur += it.second;
      res = max(res,cur);
    }
    return res;
  };

  const ld BS = 1e-9;
  const ld BIG = 1e12;
  ld l = 0;
  ld r = BIG;
  while(r-l>BS) {
    ld m = (l+r)/2;
    if(count(m)>=k) {
      r = m;
    } else {
      l = m;
    }
  }
  if(r>BIG-1) cout<<-1<<nl;
  else cout<<(l+r)/2<<nl;

  return 0;
}

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

struct Segment {
  ll l,r; int i;
  bool operator < (const Segment& o) const {
    return l < o.l;
  }
};

const int N = 5e4;
int dsu[N];
ll sz[N];

int find(int i) {
  if(dsu[i]==-1) return i;
  return dsu[i]=find(dsu[i]);
}
void link(int i, int j) {
  i=find(i); j=find(j);
  if(i!=j) {
    dsu[i] = j;
    sz[j] += sz[i];
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(10);

  memset(dsu,-1,sizeof dsu);

  int n;
  cin>>n;
  ll x[n],y[n],w[n],h[n];
  unordered_map<int,vector<Segment>> hline,vline;
  for(int i=0;i<n;i++) {
    cin>>x[i]>>y[i]>>w[i]>>h[i];
    sz[i] = w[i]*h[i];
    hline[x[i]].push_back({y[i],y[i]+h[i],i});
    hline[x[i]+w[i]].push_back({y[i],y[i]+h[i],i});
    vline[y[i]].push_back({x[i],x[i]+w[i],i});
    vline[y[i]+h[i]].push_back({x[i],x[i]+w[i],i});
  }

  for(auto& mp:{&hline,&vline}) {
    for(auto& line:*mp) {
      auto& v = line.second;
      sort(v.begin(),v.end());
      ll rb = -INF;
      int pre = -1;
      for(const auto& seg:v) {
        if(seg.l<=rb) link(seg.i,pre);
        rb = max(rb, seg.r);
        pre = seg.i;
      }
    }
  }

  ll ans = 0;
  for(int i=0;i<n;i++) {
    if(find(i)==i) {
      ans = max(ans, sz[i]);
    }
  }
  cout<<ans<<nl;

  return 0;
}

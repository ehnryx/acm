#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<19;
const int K = 5;
list<pii> st[K+1][2*N];

void combine(int k, list<pii>& a, const list<pii>& b) {
  for(const pii& it:b) {
    bool found = false;
    for(pii& jt:a) {
      if(it.first==jt.first) {
        found = true;
        jt.second += it.second;
      }
    }
    if(!found) {
      a.push_back(it);
      if(a.size()>=k) {
        int minv = INF;
        for(const pii& jt:a) {
          minv = min(minv, jt.second);
        }
        for(auto jt=a.begin();jt!=a.end();) {
          jt->second -= minv;
          if(jt->second) jt++;
          else jt=a.erase(jt);
        }
      }
    }
  }
}

void build(int k) {
  for(int i=N-1;i>0;i--) {
    st[k][i] = st[k][2*i];
    combine(k,st[k][i],st[k][2*i+1]);
  }
}

list<pii> solve(int k, int l, int r) {
  list<pii> res;
  for(l+=N,r+=N+1;l<r;l/=2,r/=2) {
    if(l&1) combine(k,res,st[k][l++]);
    if(r&1) combine(k,res,st[k][--r]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  vector<int> idx[n+1];
  for(int i=1;i<=n;i++) {
    int a;
    cin>>a;
    idx[a].push_back(i);
    for(int k=2;k<=K;k++) {
      st[k][N+i] = { pii(a,1) };
    }
  }
  for(int k=2;k<=K;k++) {
    build(k);
  }

  for(int i=0;i<m;i++) {
    int l,r,k;
    cin>>l>>r>>k;
    int ans = INF;
    int lb = (r-l+1)/k;
    for(const pii& it:solve(k,l,r)) {
      auto left = lower_bound(idx[it.first].begin(),idx[it.first].end(),l);
      auto right = upper_bound(idx[it.first].begin(),idx[it.first].end(),r);
      if(right-left>lb) ans = min(ans,it.first);
    }
    if(ans==INF) cout<<-1<<nl;
    else cout<<ans<<nl;
  }

  return 0;
}

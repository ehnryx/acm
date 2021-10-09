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

struct Q {
  int t,i,v;
};

const int N = 1<<17;
vector<int> adj[N];
ll ans[N], bonus[N];
int start[N], sz[N];
int sid=0;

int build(int u) {
  sz[u]=1;
  start[u] = sid++;
  for(int v:adj[u]) {
    sz[u] += build(v);
  }
  return sz[u];
}

ll st[2*N];

void update(int l, int r, ll v) {
  for(l+=N,r+=N;l<r;l/=2,r/=2) {
    if(l&1) st[l++]+=v;
    if(r&1) st[--r]+=v;
  }
}

ll query(int i) {
  ll r = st[i+=N];
  for(i/=2;i;i/=2) {
    r += st[i];
  }
  return r;
}

ll query_point(int u) {
  ll r = query(start[u]);
  update(start[u],start[u]+1,-r);
  return r;
}

void update_subtree(int u, int v) {
  update(start[u],start[u]+sz[u],v);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,s;
  cin>>n>>s;
  int nid = 1;
  vector<Q> p;
  for(int i=0;i<n;i++) {
    int t;
    cin>>t;
    if(t==1) {
      int id;
      cin>>id;
      adj[id].push_back(++nid);
      p.push_back({2,nid,s});
    } else if(t==2) {
      int id,m;
      cin>>id>>m;
      p.push_back({2,id,m});
    } else if(t==3) {
      int id,b;
      cin>>id>>b;
      p.push_back({3,id,b});
    } else {
      int id;
      cin>>id;
      p.push_back({4,id});
    }
  }
  build(1);

  bonus[1] = s;
  for(Q it:p) {
    if(it.t==2) {
      ans[it.i] += bonus[it.i]*query_point(it.i);
      bonus[it.i] = it.v;
    } else if(it.t==3) {
      update_subtree(it.i,it.v);
    } else {
      ans[it.i] += bonus[it.i]*query_point(it.i);
      cout<<ans[it.i]<<nl;
    }
  }

  return 0;
}

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

const int N = 1<<17;
vector<int> adj[N];

namespace RU {
  ll len[2*N], tag[2*N], st[2*2*N];
  void update(int l, int r, int v, int i=1, int s=0, int e=N-1) {
    if(r<s||e<l) return;
    if(l<=s&&e<=r) {
      tag[i] += v;
      if(tag[i]) st[i]=len[i];
      else st[i]=st[2*i]+st[2*i+1];
      return;
    }
    int m=(s+e)/2;
    update(l,r,v,2*i,s,m);
    update(l,r,v,2*i+1,m+1,e);
    if(tag[i]) st[i]=len[i];
    else st[i]=st[2*i]+st[2*i+1];
  }

  struct Segment {
    int x, t, a, b;
    bool operator < (const Segment& o) const {
      return x<o.x;
    }
  };
  vector<Segment> segs;

  void insert_rect(int s, int t, int a, int b) {
    ++t;
    segs.push_back({s,1,a,b});
    segs.push_back({t,-1,a,b});
  }

  map<ll,ll> pre;
  void insert_query(int s, int t) {
    ++t;
    segs.push_back({s,0});
    segs.push_back({t,0});
  }

  map<ll,ll> pref;
  ll query(int s, int t) {
    assert(pref.count(s));
    assert(pref.count(++t));
    return pref[t]-pref[s];
  }

  void solve() {
    fill(len,len+2*N,1);
    fill(tag,tag+2*N,0);
    fill(st,st+2*2*N,0);
    for(int i=N-1;i>0;i--) len[i]=len[2*i]+len[2*i+1];
    sort(segs.begin(),segs.end());
    ll cur = 0;
    ll px = -INF;
    for(const Segment& it:segs) {
      cur += (it.x-px)*st[1];
      if(it.t==0) {
        pref[it.x] = cur;
      } else {
        update(it.a, it.b, it.t);
      }
      px = it.x;
    }
  }
}

namespace HLD {
  int st[N];
  int d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; int dn, cn;
  int dfs(int u, int p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
    for(int x:adj[u]) { if (x!=p) sub[u] += dfs(x,u); } return sub[u]; }
  void hld(int u, int p) { if (dn==cn) { root[cn]=u; sz[cn++]=0; }
    pos[u] = sz[ch[u]=dn]++; int b=-1, c=-1;
    for (int x:adj[u]) { if(x!=p && sub[x]>b) b=sub[c=x]; } if(c!=-1) hld(c,u);
    for (int y:adj[u]) { if(y!=p && y!=c) { dn++; hld(y,u); } } }
  void build(int r) { d[0]=dn=cn=0; dfs(r,0); hld(r,0); st[0] = 0;
    for(int i=1;i<cn;i++) st[i] = st[i-1] + sz[i-1]; }
  void insert_path(int a, int b, int s, int t) {
    while(ch[a] != ch[b]) { if(d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      RU::insert_rect(s, t, st[ch[a]]+0, st[ch[a]]+pos[a]); a = par[root[ch[a]]]; }
    if(pos[a] != pos[b]) { if (d[a]<d[b]) swap(a,b);
      RU::insert_rect(s, t, st[ch[a]]+pos[b]+1, st[ch[a]]+pos[a]); } return; }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m,q;
  cin>>n>>m>>q;
  for(int i=1;i<n;i++) {
    int a,b;
    cin>>a>>b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  HLD::build(1);

  for(int i=0;i<m;i++) {
    int a,b,s,t;
    cin>>a>>b>>s>>t;
    HLD::insert_path(a,b,s,t);
  }

  vector<pii> range;
  for(int i=0;i<q;i++) {
    int a,b;
    cin>>a>>b;
    RU::insert_query(a,b);
    range.push_back({a,b});
  }
  RU::solve();

  for(pii it:range) {
    cout<<RU::query(it.first,it.second)<<nl;
  }

  return 0;
}

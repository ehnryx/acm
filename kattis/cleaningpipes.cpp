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

const int N = 2e3+1;
namespace SAT {
  int low[N],vis[N],scomp[N],scompNum,I;
  vector<int> adj[N]; stack<int> verts;
  void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
    for (int v : adj[u]) {
      if (!vis[v]) scc(v);
      if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
    if (vis[u] <= low[u]) { int v;
      do { v=verts.top(); verts.pop(); scomp[v]=scompNum; } while (v != u);
      ++scompNum; }}
  void get_scc(int n) { memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
    scompNum=I=0; for (int i=0; i<n; ++i) if (!vis[i]) scc(i); }
  bool truth[N/2]; // N must be at least 2 times the number of variables
  void add_clause(int a, int b) {
    adj[a^1].push_back(b);
    adj[b^1].push_back(a);
    adj[a].push_back(b^1);
    adj[b].push_back(a^1);
  }
  bool two_sat(int n) { get_scc(n);
    for (int i = 0; i < n; i += 2) { if (scomp[i] == scomp[i^1]) return false;
      truth[i/2] = (scomp[i] < scomp[i^1]); } return true; }
}

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
int sgn(const ld& x) { return abs(x)<EPS ? 0 : (x<0 ? -1 : 1); }
bool seg_x_seg(pt a, pt b, pt c, pt d) {
  //cerr<<"sxs w/ "<<a<<" "<<b<<" "<<c<<" "<<d<<nl;
  if(a==c || a==d || c==b) return false;
  if(b==d) return true;
  int s1 = sgn(cp(b-a,c-a)); int s2 = sgn(cp(b-a,d-a));
  int s3 = sgn(cp(d-c,a-c)); int s4 = sgn(cp(d-c,b-c));
  if(!s1 && !s2 && !s3) return false;
  else return s1*s2<=0 && s3*s4<=0;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  pt p[n];
  for(int i=0;i<n;i++) {
    int x,y;
    cin>>x>>y;
    p[i] = pt(x,y);
  }
  int a[m]; pt q[m];
  for(int i=0;i<m;i++) {
    int x,y;
    cin>>a[i]>>x>>y;
    --a[i];
    q[i] = pt(x,y);
    for(int j=0;j<i;j++) {
      if(seg_x_seg(p[a[i]],q[i],p[a[j]],q[j])) {
        //cerr<<"segxseg @ "<<i<<" "<<j<<nl;
        SAT::add_clause(2*i,2*j);
      }
    }
  }
  if(SAT::two_sat(2*m)) {
    cout<<"possible"<<nl;
  } else {
    cout<<"impossible"<<nl;
  }

  return 0;
}

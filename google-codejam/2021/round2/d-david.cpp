#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const int INF = 0x3f3f3f3f;
const int R = 12;
int r, c, f, ss;
string s[R], t[R];

const int N = 2022;
struct Edge { int v, r; ll f, c, p; };

vector<Edge> adj[N]; int sz[N]; ll mc;
vector<Edge> mcf_edges; // for mcf on large graphs with negative costs
void init(int n=N) {
  mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
void add_edge(int a, int b, ll c=1, ll p=0) { mc = max(mc,c); // scaling
  // mcf_edges.push_back({b,a,0,c,p});
	adj[a].push_back({b,sz[b]++,0,c,p});
	adj[b].push_back({a,sz[a]++,0,0,-p}); }

int L[N], cur[N], Q[N];
bool bfs(int s, int t, ll lim=1) {
  memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
  int f,b; Q[f=b=0] = s; L[s] = 0;
  while(f<=b && L[t]==INF) { int u = Q[f++];
    for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c-e.f >= lim) {
      Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
      ll dfs(int u, int t, ll f) { if (u == t || !f) return f;
        for (int i = cur[u]; i < sz[u]; cur[u] = ++i) { Edge& e = adj[u][i];
          if(e.f<e.c && L[e.v]==L[u]+1) {
            if(ll cf = dfs(e.v, t, min(e.c-e.f, f))) {
              e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0; }
              ll flow(int s, int t, bool scaling=0) {ll inf=numeric_limits<ll>::max();
                ll res = 0; for(ll lim=(scaling?mc:1); lim; lim/=2) {
                  while(bfs(s,t,lim))while(ll cf=dfs(s,t,inf))res += cf;} return res;}


// if f == s, then only swap if inverted? or do we take a matching? Take matching
int hsh(int i, int j) { return 10*i+j+2;}
int main(){
  cin.tie(0); ios_base::sync_with_stdio(0);
  int T; cin >> T; 
  for(int tt=1;tt<=T;tt++) {
    cout << "Case #" << tt << ": ";
    cin >> r >> c >> f >> ss;
    for(int i=0;i<r;i++) cin >> s[i];
    for(int i=0;i<r;i++) cin >> t[i];
    int ans = 0;
    int SS = 0; int TT = 1;
    init();
    for(int i=0;i<r;i++) {
      for(int j=0;j<c;j++) {

        if (s[i][j] =='M') add_edge(SS, hsh(i,j));
        else add_edge(hsh(i,j), TT);
        if (s[i][j]!=t[i][j]) {
          ans++;
          int ni = i+1;
          int nj = j+1;
          if (ni<r && s[ni][j]!=s[i][j] && s[ni][j]!=t[ni][j])
            add_edge(hsh(i,j), hsh(ni,j)), add_edge(hsh(ni,j), hsh(i,j));
          if (nj<c && s[i][nj]!=s[i][j] && s[i][nj]!=t[i][nj])
            add_edge(hsh(i,j), hsh(i,nj)), add_edge(hsh(i,nj), hsh(i,j));
        }
      }
    }
    int fo = flow(SS, TT);
    //cerr << ans << " " << fo <<endl;
    cout << ans - fo;
    cout <<endl;
  }
}

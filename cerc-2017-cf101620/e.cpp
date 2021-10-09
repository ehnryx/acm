#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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

const int N = 3e5+1;
vector<int> graph[N];
vector<int> adj[N];

bool convert(int u, int p) {
  if(graph[u].size() - (p!=0) > 2) {
    return false;
  }
  for(int v:graph[u]) {
    if(v==p) continue;
    adj[u].push_back(v);
    if(!convert(v, u)) {
      return false;
    }
  }
  return true;
}

int plen[N], nxt2[N], dto2[N];
void build(int u) {
  for(int v:adj[u]) {
    build(v);
    nxt2[u] = nxt2[v];
    dto2[u] = dto2[v]+1;
    plen[u] = plen[v]+1;
  }
  if(adj[u].size() == 2) {
    plen[u] = INF;
    nxt2[u] = u;
    dto2[u] = 0;
  } else if(adj[u].empty()) {
    plen[u] = 1;
    dto2[u] = INF;
  }
}

ll dp[N][2];  // node in first row, offset
ll solve(int u, int d) {
  if(dp[u][d] != -1) return dp[u][d];

  if(adj[u].empty()) {
    return dp[u][d] = 1;
  }

  else if(adj[u].size() == 2) {
    if(d == 0) {
      return dp[u][d] = 0;
    }

    ll res = 0;
    for(int rot=0; rot<2; rot++) {
      int a = u;
      int b = adj[u][1];
      if(adj[b].size() == 2) {
      } else if(adj[b].empty()) {
        res += solve(adj[a][0], 1);
        //cerr<<"@ "<<u<<" "<<d<<" -> "<<adj[a][0]<<" "<<1<<" w/ thorn"<<nl;
        //cerr<<"get "<<solve(adj[a][0], 1)<<nl;
      } else {
        a = adj[a][0];
        b = adj[b][0];
        while(adj[a].size() == 1 && adj[b].size() == 1) {
          a = adj[a][0];
          b = adj[b][0];
        }
        // don't overcount here
        if(adj[a].empty()) {
          res += solve(b, 0);
          //cerr<<"@ "<<u<<" "<<d<<" -> "<<b<<" "<<0<<" w/ walk"<<nl;
          //cerr<<"get "<<solve(b,0)<<nl;
        } else if(adj[b].empty()) {
          res += solve(a, 0);
          //cerr<<"@ "<<u<<" "<<d<<" -> "<<a<<" "<<0<<" w/ walk"<<nl;
          //cerr<<"get "<<solve(a,0)<<nl;
        }
      }
      swap(adj[u][0], adj[u][1]); // swap order of branches
    }

    return dp[u][d] = res % MOD;
  }

  else if(d==0) {
    ll res = solve(adj[u][0], 1);
    //cerr<<"@ "<<u<<" "<<d<<" -> "<<adj[u][0]<<" "<<1<<" w/ bump"<<nl;
    //cerr<<"get "<<solve(adj[u][0],1)<<nl;
    return dp[u][d] = res;
  }

  else {
    ll res = solve(adj[u][0], 0) + solve(adj[u][0], 1);
    //cerr<<"@ "<<u<<" "<<d<<" -> "<<adj[u][0]<<" "<<0<<" w/ flat"<<nl;
    //cerr<<"get "<<solve(adj[u][0],0)<<nl;
    //cerr<<"@ "<<u<<" "<<d<<" -> "<<adj[u][0]<<" "<<1<<" w/ push"<<nl;
    //cerr<<"get "<<solve(adj[u][0],1)<<nl;
    if(plen[u] < INF) {
      if(plen[u] > 2 && plen[u]%2 == 0) {
        res += 1;
      }
    }

    else {
      int v = nxt2[u];
      for(int rot=0; rot<2; rot++) {
        int a = adj[v][0];
        int b = adj[v][1];
        if(dto2[u] == plen[a]-1) {
          res += solve(b, 1);
          //cerr<<"@ "<<u<<" "<<d<<" -> "<<b<<" "<<1<<" w/ early br"<<nl;
          //cerr<<"get "<<solve(b,1)<<nl;
        }
        if(dto2[u]-1 == plen[a]) {
          res += solve(b, 1);
          //cerr<<"@ "<<u<<" "<<d<<" -> "<<b<<" "<<1<<" w/ late br"<<nl;
          //cerr<<"get "<<solve(b,1)<<nl;
        }
        if(adj[a].size() == 2) {
          for(int br=0; br<2; br++) {
            if(plen[adj[a][br]] == dto2[u]) {
              int x = adj[a][br^1];
              int y = b;
              while(adj[x].size() == 1 && adj[y].size() == 1) {
                x = adj[x][0];
                y = adj[y][0];
              }
              // don't overcount here
              if(adj[x].empty()) {
                res += solve(y, 0);
                //cerr<<"@ "<<u<<" "<<d<<" -> "<<y<<" "<<0<<" w/ weird walk"<<nl;
                //cerr<<"get "<<solve(y,0)<<nl;
              } else if(adj[y].empty()) {
                res += solve(x, 0);
                //cerr<<"@ "<<u<<" "<<d<<" -> "<<x<<" "<<0<<" w/ weird walk"<<nl;
                //cerr<<"get "<<solve(x,0)<<nl;
              }
            }
          }
        }

        swap(adj[v][0], adj[v][1]); // swap order of branches
      }
    }
    return dp[u][d] = res % MOD;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=1;i<n;i++) {
    int a,b;
    cin>>a>>b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  if(!convert(1,0)) {
    cout<<0<<nl;
    return 0;
  }

  build(1);
  for(int i=1;i<=n;i++) {
    if(nxt2[i] == 0) {
      assert(plen[i] < INF);
      assert(dto2[i] >= INF);
    } else {
      assert(plen[i] >= INF);
      assert(dto2[i] < INF);
    }
    ////cerr<<i<<": plen nxt2 dto2 :: "<<plen[i]<<" "<<nxt2[i]<<" "<<dto2[i]<<nl;
  }

  memset(dp,-1,sizeof dp);
  cout << solve(1, 1) << nl;

  for(int i=1;i<=n;i++) {
    for(int d=0;d<2;d++) {
      //cerr<<i<<','<<d<<": "<<dp[i][d]<<nl;
    }
  }

  return 0;
}

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

vector<char> cmap = { 'r', 'g', 'b', 'y' };

void set_grid(string g[], int bm) {
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      if(g[i][j]=='W') {
        g[i][j] = cmap[bm&0b11];
        bm >>= 2;
      }
    }
  }
}

void clear_grid(string g[]) {
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      if(g[i][j]==tolower(g[i][j])) {
        g[i][j] = 'W';
      }
    }
  }
}

int idmap[4][4];
bool adj[12][12];
bool vis[1<<12][12];

bool hamiltonian(int bm, int u, int t, int n) {
  if(bm==0) return u==t;
  if(vis[bm][u]) return false;
  vis[bm][u] = true;
  if(u==t) return false;
  ////cerr<<"ham w/ "<<bitset<16>(bm)<<" "<<u<<nl;
  for(int i=0;i<n;i++) {
    if((bm&1<<i) && adj[u][i] && hamiltonian(bm^1<<i, i, t, n)) {
      return true;
    }
  }
  return false;
}

bool check_c(string g[], char c) {
  ////cerr<<"check w/ colour "<<c<<nl;
  int id = 0;
  vector<int> s;
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      if(tolower(g[i][j])==c) {
        if(g[i][j]!=c) s.push_back(id);
        ////cerr<<"idmap "<<i<<" "<<j<<" = "<<id<<nl;
        idmap[i][j] = id++;
      }
    }
  }
  if(s.empty()) return id==0;
  ////cerr<<"source set to "<<s<<nl;

  memset(adj,0,sizeof adj);
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      if(tolower(g[i][j])==c) {
        if(i>0 && tolower(g[i-1][j])==c) {
          adj[idmap[i][j]][idmap[i-1][j]] = true;
        }
        if(j>0 && tolower(g[i][j-1])==c) {
          adj[idmap[i][j]][idmap[i][j-1]] = true;
        }
        if(i+1<4 && tolower(g[i+1][j])==c) {
          adj[idmap[i][j]][idmap[i+1][j]] = true;
        }
        if(j+1<4 && tolower(g[i][j+1])==c) {
          adj[idmap[i][j]][idmap[i][j+1]] = true;
        }
      }
    }
  }
  ////cerr<<"adjacency:" << nl; for(int i=0;i<id;i++) {
    ////cerr<<i<<": "; for(int j=0;j<id;j++) { if(adj[i][j]) ////cerr<<j<<" "; }
    ////cerr<<nl; }

  assert(id<=12);
  fill(&vis[0][0], &vis[0][0]+(1<<id)*12, false);
  return hamiltonian(((1<<id)-1) ^ 1<<s.front(), s.front(), s.back(), id);
}

bool check(string g[], int bm) {
  set_grid(g,bm);
  ////cerr<<"checking grid "<<nl; for(int i=0;i<4;i++) { for(int j=0;j<4;j++) {
      ////cerr<<g[i][j]; } ////cerr<<nl; }

  bool ok = true;
  for(char c:cmap) {
    if(ok) ok &= check_c(g,c);
  }

  clear_grid(g);
  return ok;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string g[4];
  for(int i=0;i<4;i++) {
    cin>>g[i];
  }

  for(int bm=0;bm<1<<20;bm++) {
    if(check(g,bm)) {
      //cerr<<"solvable @ "; set_grid(g,bm);
      //cerr<<nl; for(int i=0;i<4;i++) { for(int j=0;j<4;j++) {
        //cerr<<g[i][j]; } //cerr<<nl; }
      cout<<"solvable"<<nl;
      return 0;
    }
  }
  cout<<"not solvable"<<nl;

  return 0;
}

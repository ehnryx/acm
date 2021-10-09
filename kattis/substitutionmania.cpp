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

const int N = 12;
const int M = 26;
string v[N];
char adj[N][M];
char dp[M][1<<N][M];
bool pre[M][1<<N][M][N];

bool solve(int s, int g, int bm) {
  if(bm==0) return s==g;
  if(dp[s][bm][g]!=-1) return dp[s][bm][g];
  bool res = false;
  for(int i=0;i<N;i++) {
    if(bm&1<<i) {
      int ng = adj[i][g];
      if(solve(s,ng,bm^1<<i)) {
        res = true;
        pre[s][bm][g][i] = true;
      }
    }
  }
  return dp[s][bm][g] = res;
}

bool dfs(vector<int>& order, int goal[M], int bm) {
  if(bm==0) return true;
  for(int i=0;i<N;i++) {
    if(bm&1<<i) {
      bool ok = true;
      for(int j=0;j<M;j++) {
        if(goal[j]!=-1) {
          ok &= pre[j][bm][goal[j]][i];
        }
      }
      if(ok) {
        int nxt[M];
        memset(nxt,-1,sizeof nxt);
        for(int j=0;j<M;j++) {
          if(goal[j]!=-1) {
            nxt[j] = adj[i][goal[j]];
          }
        }
        if(dfs(order,nxt,bm^1<<i)) {
          order.push_back(i);
          return true;
        }
      }
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  string s,t;
  getline(cin,s);
  getline(cin,t);

  int goal[M];
  memset(goal,-1,sizeof goal);
  int m = s.size();
  for(int i=0;i<m;i++) {
    if(s[i]==' ') continue;
    goal[s[i]-'a'] = t[i]-'a';
  }

  int n;
  cin>>n;
  for(int i=0;i<n;i++) {
    cin>>v[i];
    for(int j=0;j<M;j++) {
      adj[i][v[i][j]-'a'] = j;
    }
  }

  memset(dp,-1,sizeof dp);
  for(int i=0;i<M;i++) {
    if(goal[i]!=-1) {
      assert(solve(i,goal[i],(1<<n)-1));
    }
  }
  //cerr<<"DP ok"<<endl;

  vector<int> order;
  dfs(order,goal,(1<<n)-1);
  reverse(order.begin(),order.end());
  //cerr<<"Order: "; for(int i:order) //cerr<<i<<" ";
  //cerr<<endl;

  for(string w;cin>>w;) {
    for(char c:w) {
      for(int i:order) {
        c = adj[i][c-'a']+'a';
      }
      cout<<c;
    }
    cout<<" ";
  }
  cout<<nl;

  return 0;
}

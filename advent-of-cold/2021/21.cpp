#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

pair<ll,ll> dp[10][10][33][33][3][10];
pair<ll,ll> solve(int a, int b, int x, int y, int t=0, int c=0) {
  if(dp[a][b][x][y][t][c].first!=-1)return dp[a][b][x][y][t][c];
  if(y>=21)return pair(0 ,1);
    ll A=0,B=0;
    int na;

  if(t == 3){

    na=(a+c)%10;
    auto [cb,ca]=solve(b,na,y,x+na+1,0,0);
    A+=ca; B+=cb;

  }
  else{

    auto [ca,cb]=solve(a,b,x,y,t+1,c+1);
    A+=ca; B+=cb;

    tie(ca,cb)=solve(a,b,x,y,t+1,c+2);
    A+=ca; B+=cb;
    tie(ca,cb)=solve(a,b,x,y,t+1,c+3);
    A+=ca; B+=cb;

  }

  return dp[a][b][x][y][t][c]=pair(A,B);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int a, b;
  cin >> a >> b;

  memset(dp,-1,sizeof dp);
  auto [x,y] = solve(a-1,b-1,0,0);
  cout << max(x,y) << nl;

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'

const int MOD = 1e9 + 7;

const int N = 5e3 + 1;
const int M = 60;
ll dp[N][M][M][2]; // i, sum, x-f(x), follow
int p10[N];

int solve(int m, const string& r) {
  int n = r.size();
  dp[0][0][0][1] = 1;
  for(int i=1; i<=n; i++) {
    for(int s=0; s<m; s++) {
      for(int f=0; f<m; f++) {
        { // follow
          int d = r[i-1]-'0';
          int os = (s - d) % m;
          int of = (f - d * (p10[n-i] - os + m)) % m;
          if(os < 0) os += m;
          if(of < 0) of += m;
          //assert(os>=0 && of>=0);
          //assert(os<m && of<m);
          dp[i][s][f][1] = dp[i-1][os][of][1];
        }
        { // not follow
          dp[i][s][f][0] = 0;
          for(int d=0; d<10; d++) {
            int os = (s - d) % m;
            int of = (f - d * (p10[n-i] - os + m)) % m;
            if(os < 0) os += m;
            if(of < 0) of += m;
            //assert(os>=0 && of>=0);
            //assert(os<m && of<m);
            dp[i][s][f][0] += dp[i-1][os][of][0];
            if(d < r[i-1]-'0') {
              dp[i][s][f][0] += dp[i-1][os][of][1];
            }
          }
          dp[i][s][f][0] %= MOD;
        }
      }
    }
  }
  ll res = 0;
  for(int s=0; s<m; s++) {
    res += dp[n][s][0][0] + dp[n][s][0][1];
    //cerr<<"got "<<dp[n][s][0][0]<<" + "<<dp[n][s][0][1]<<nl;
  }
  //cerr<<"solve "<<r<<" -> "<<res<<nl;

  /*
  int ub = stoi(r);
  int bf = 0;
  for(int x=0; x<=ub; x++) {
    int fun = 0;
    int sum = 0;
    for(int d=x; d>0; d/=10) {
      fun += (d%10) * sum % m;
      sum += (d%10);
    }
    if(fun % m == x % m) {
      //cerr<<"+ bf @ "<<x<<" w/ "<<fun<<" and "<<x<<nl;
      bf++;
    }
  }
  cerr<<"bf: "<<bf<<nl;
  assert(bf == res);
  */

  return res % MOD;
}

int calc(int m, const string& r) {
  int n = r.size();
  int x = 0;
  int f = 0;
  int s = 0;
  for(int i=1; i<=n; i++) {
    int d = r[i-1]-'0';
    x += p10[n-i] * d % m;
    f += d * s % m;
    s += d;
  }
  return (x % m == f % m);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    string l, r;
    cin >> l >> r;
    int m;
    cin >> m;
    int k = 1;
    for(int i=0; i<r.size(); i++) {
      p10[i] = k;
      k = k * 10 % m;
    }
    cout << (solve(m, r) - solve(m, l) + calc(m, l) + MOD) % MOD << nl;
  }

  return 0;
}

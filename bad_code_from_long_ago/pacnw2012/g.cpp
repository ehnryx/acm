#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;
const int N = 65;

ll n;
string nstr;
ll dp[N][3][2];
ll solve(int pos, int num, bool less) {
  if (pos >= nstr.size() && num == 0) return 1;
  if (pos >= nstr.size()) return 0;
  if (dp[pos][num][less] != -1) return dp[pos][num][less];
  ll ans;
  if (less) {
    ans = solve(pos+1, (num+1)%3, less) + solve(pos+1, num, less);
  } else if (nstr[pos] == '0') {
    ans = solve(pos+1, num, less);
  } else if (nstr[pos] == '1') {
    ans = solve(pos+1, num, 1) + solve(pos+1, (num+1)%3, 0);
  } else assert(0);
  return dp[pos][num][less] = ans;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  while (cin >> n) {
    memset(dp, -1, sizeof dp);
    bitset<64> b(n);
    nstr = b.to_string();
    cout << "Day " << n << ": Level = " << solve(0, 0, 0)-1 << endl;
  }

  return 0;
}

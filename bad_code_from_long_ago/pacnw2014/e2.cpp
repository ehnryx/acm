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

string s;
int dp[75][11][2][2];

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int T; cin >> T;
  while (T--) {
    cin >> s;
    bool good = 1, dec = 0;
    for (int i = 1; i < s.size(); i++) {
      if (s[i] < s[i-1]) {
        decr = 1;
      } else if (decr && 

  return 0;
}

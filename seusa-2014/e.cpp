#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 20;
const int D = 10;
ll dp[N][D][2][2]; // index, follow, inc
ll solve(const string& s, int id, int dig, bool follow, bool inc) {
  if (dp[id][dig][follow][inc] != -1) return dp[id][dig][follow][inc];
  if (id == s.size()) return 1;
  ll res = 0;
  for (int d=0; d<10; d++) {
    if (follow && inc) {
      if (d > s[id]-'0') continue;
      if (d < s[id]-'0') {
        if (d >= dig) res += solve(s, id+1, d, false, true);
        else if (d <= dig) res += solve(s, id+1, d, false, false);
      } else {
        if (d >= dig) res += solve(s, id+1, d, true, true);
        else if (d <= dig) res += solve(s, id+1, d, true, false);
      }
    }
    else if (follow && !inc) {
      if (d > s[id]-'0') continue;
      if (d < s[id]-'0') {
        if (d <= dig) res += solve(s, id+1, d, false, false);
      } else {
        if (d <= dig) res += solve(s, id+1, d, true, false);
      }
    }
    else if (!follow && inc) {
      if (d >= dig) res += solve(s, id+1, d, false, true);
      else if (d <= dig) res += solve(s, id+1, d, false, false);
    }
    else {
      if (d <= dig) res += solve(s, id+1, d, false, false);
    }
  }
  return dp[id][dig][follow][inc] = res;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  memset(dp, -1, sizeof dp);

  string s;
  cin >> s;

  for (int i=1; i+1<s.size(); i++) {
    if (s[i-1] > s[i] && s[i] < s[i+1]) {
      cout << -1 << nl;
      return 0;
    }
  }

  ll ans = 0;
  for (int d=0; d<10; d++) {
    if (d<s[0]-'0') {
      ans += solve(s, 1, d, false, true);
    } else if (d==s[0]-'0') {
      ans += solve(s, 1, d, true, true);
    }
  }
  cout << ans-1 << nl;

  return 0;
}

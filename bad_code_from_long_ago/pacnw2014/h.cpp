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
const int N = 5005;

int dp[N][N];
int n, m;
vector<int> s;
int solve(int push, int num) {
  if (push < 0) return -INF;
  if (num == 0 && push) return -INF;
  if (num == 0 && push == 0) return 0;
  if (dp[push][num] != -1) return dp[push][num];
  int best = -INF;
  for (int i : s)
    best = max(best, solve(push - i*num, num-1) + i);
  return dp[push][num] = best;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int T; cin >> T;
  while (T--) {
    cin >> n >> m;
    s.resize(m);
    for (int i = 0; i < m; i++)
      cin >> s[i];
    sort(s.rbegin(), s.rend());
    memset(dp, -1, sizeof dp);
    int best = -1;
    for (int i = 0; i <= n; i++)
      best = max(best, solve(n, i));
    cout << (best < 0 ? -1 : best) << endl;
  }

  return 0;
}

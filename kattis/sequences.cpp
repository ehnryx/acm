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

const int N = 5e5+1;
ll two[N];
char s[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  two[0] = 1;
  for (int i=1; i<N; i++) {
    two[i] = two[i-1]*2 % MOD;
  }

  scanf("%s",s);
  int tot = 0;
  for (int i=0; s[i]; i++) {
    tot += (s[i]=='?');
  }

  ll ans = 0;
  int ones = 0;
  int n = 0;
  for (int i=0; s[i]; i++) {
    if (s[i]=='1') {
      ones += 1;
    } else if (s[i]=='0') {
      ans += two[tot]*ones % MOD;
      if (n>0) ans += two[tot-1]*n % MOD;
    } else {
      ans += two[tot-1]*ones % MOD;
      if (n>0) ans += two[tot-2]*n % MOD;
      n += 1;
    }
  }
  printf("%d\n", ans%MOD); 

  return 0;
}

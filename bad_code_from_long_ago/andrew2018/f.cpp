#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ ";
  for (const T& it : v) os << it << " ";
  os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e6+3;
const ld EPS = 1e-9;

ll dp[1001][1001];
ll ans[1001][1001];

void init() {
  memset(dp, 0, sizeof dp);
  dp[0][0] = 1;
  for (int i = 1; i <= 1000; i++) {
    dp[i][i] = 1;
    for (int j = i+1; j <= 1000; j++) {
      dp[j][i] = ((i-1) * dp[j-1][i] % MOD + dp[j-1][i-1] % MOD);
    }
  }
  for (int i = 1; i <= 1000; i++) {
    ans[i][0] = 0;
    for (int j = 1; j <= 1000; j++) {
      ans[i][j] = (ans[i][j-1] + dp[i][j]) % MOD;
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  init();

  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    cout << ans[n][m] << endl;
  }

  return 0;
}

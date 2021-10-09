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
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const int N = 10;

ll dp[N];
void pre() {
  dp[1] = 8;
  for (int i = 2; i < N; i++)
    dp[i] = dp[i-1] * 9;
}



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
#ifdef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  pre();
  int n; cin >> n;
  if (n < N)
    cout << dp[n] << endl;
  else {
    string ans = to_string(dp[N-1]);
    int k = n - N + 1;
    while (k--)
      ans.push_back('0');
    cout << ans << endl;
  }

  return 0;
}

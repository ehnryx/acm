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



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  string s;
  cin >> s;
  vector<int> dp(s.size()+1);
  dp[0] = 1;
  dp[1] = 1;
  for(int i=2;i<=s.size();++i) {
    dp[i] = dp[i-1];
    string ss = s.substr(i-2, 2);
    if(ss == "NW" || ss == "NE" || ss == "SW" || ss == "SE")
      dp[i] += dp[i-2];
    dp[i]%= MOD;
  }

  cout << dp[s.size()] << endl;


  return 0;
}

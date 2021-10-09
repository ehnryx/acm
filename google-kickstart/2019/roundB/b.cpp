#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; 
  return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
  return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    solve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

struct Item {
  int s, e, l;
  bool operator < (const Item& o) const {
    if (l*o.s != o.l*s) return l*o.s > o.l*s;
    else return e > o.e;
  }
};

const int T = 1e4+1;
int dp[T];

void caseinit() {
  memset(dp, 0, sizeof dp);
}

void solve() {
  caseinit();

  int n;
  cin >> n;

  vector<Item> items;
  for (int i=0; i<n; i++) {
    int s, e, l;
    cin >> s >> e >> l;
    items.push_back({s,e,l});
  }
  sort(items.begin(), items.end());

  for (const Item& it : items) {
    int s = it.s;
    int e = it.e;
    int l = it.l;
    for (int j=T-1; j-s>=0; j--) {
      dp[j] = max(dp[j], dp[j-s] + max(0, e-l*(j-s)));
    }
    //cerr << nl << " STONE " << s << " " << e << " " << l << nl;
    //for (int j=0; j<=150; j+=5) {
      //cerr << j << ": " << dp[j] << nl;
    //}
  }
  //cerr << nl;

  int ans = 0;
  for (int i=0; i<T; i++) {
    ans = max(ans, dp[i]);
  }
  cout << ans << nl;

  return;
}


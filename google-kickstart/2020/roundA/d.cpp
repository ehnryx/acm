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
  for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
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

const int N = 1e5 + 1;
const int M = 26;
string s[N];

void caseinit() {
}

int solve(int l, int r, int j, int m) {
  int res = 0;
  char pre = 0;
  int first = -1;
  for(int i=l; i<r; i++) {
    char cur = (j < s[i].size() ? s[i][j] : 0);
    if(pre != cur) {
      if(pre) {
        res += (i-first) / m;
        res += solve(first, i, j+1, m);
      }
      first = i;
      pre = cur;
    }
  }
  if(pre) {
    res += (r-first) / m;
    res += solve(first, r, j+1, m);
  }
  return res;
}

void solve() {
  caseinit();

  int n, m;
  cin >> n >> m;
  for(int i=0; i<n; i++) {
    cin >> s[i];
  }
  sort(s, s+n);
  cout << solve(0, n, 0, m) << nl;

  return;
}


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

const int N = 1e5+1;
int bit[26][N];
void insert(int id, int x) {
  for ( ; x<N; x+=x&-x)
    bit[id][x]++;
}
int query(int id, int x) {
  int res = 0;
  for ( ; x>0; x-=x&-x)
    res += bit[id][x];
  return res;
}
int answer(int id, int l, int r) {
  return query(id, r) - query(id, l-1);
}

void caseinit() {
}

void solve() {
  caseinit();

  int n, q;
  cin >> n >> q;
  for (int i=0; i<26; i++) {
    memset(bit[i], 0, (n+1)*sizeof(bit[i][0]));
  }

  string s;
  cin >> s;
  for (int i=1; i<=n; i++) {
    insert(s[i-1]-'A', i);
  }

  int ans = 0;
  for (int i=0; i<q; i++) {
    int l, r;
    cin >> l >> r;
    int odd = 0;
    for (int j=0; j<26; j++) {
      odd += answer(j, l, r) % 2;
    }
    ans += (odd <= 1);
  }
  cout << ans << nl;

  return;
}


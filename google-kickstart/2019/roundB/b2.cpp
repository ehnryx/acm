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
const int INF = 0x3f3f3f3f;
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

const int N = 100+1;
int s[N], e[N], l[N];

void caseinit() {
}

void solve() {
  caseinit();

  int n;
  cin >> n;

  unordered_set<int> active;
  for (int i=0; i<n; i++) {
    cin >> s[i] >> e[i] >> l[i];
    active.insert(i);
  }

  function<int(int,int)> get = [&] (int id, int t) {
    return max(0, e[id] - t*l[id]);
  };

  int ans = 0;
  int t = 0;
  for (int i=0; i<n; i++) {
    int bestj = -1;
    int best = INF;
    for (int j : active) {
      int lose = 0;
      for (int k : active) {
        if (k==j) lose -= get(k, t) - get(k, t+s[j]);
        else lose += get(k, t) - get(k, t+s[j]);
      }
      if (lose < best) {
        bestj = j;
        best = lose;
      }
    }
    //cerr << i << " " << t << " -> " << bestj << " los " << best << endl;
    ans += get(bestj, t);
    t += s[bestj];
    active.erase(bestj);
  }
  cout << ans << nl;

  return;
}



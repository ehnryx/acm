#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;
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

// get_sarray()[i] = idx of suffix s[i..L-1] in list of sorted suffixes
struct suff_array {
  const int L; string s; int i, skip, lvl;
  vector<vi> P; vector<pair<pii,int>> M;
  suff_array(const string &s) : L(s.size()), s(s), P(1, vi(L, 0)), M(L) {
    for (i = 0; i < L-(L==1); i++) P[0][i] = int(s[i]);
    for (skip = 1, lvl = 1; skip < L; skip *= 2, lvl++) {
      P.push_back(vi(L, 0));
      for (int i = 0; i < L; i++)
        M[i] = {{P[lvl-1][i], i+skip<L ? P[lvl-1][i + skip] : -1000}, i};
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++)
        P[lvl][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ?
            P[lvl][M[i-1].second] : i; } }
  const vi& get_sarray() { return P.back(); }
  //returns len of longest common prefix of s[i...L-1] and s[j...L-1], O(lg L)
  int lcp(int i, int j) {
    int len = 0; if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--)
      if (P[k][i] == P[k][j]) { i += 1 << k; j += 1 << k; len += 1 << k; }
    return len; }
};

struct Pair {
  int i, j, len;
  bool operator < (const Pair& o) const {
    return len > o.len;
  }
};

const int N = 1000+1;
int pos[N];
string s[N];

void caseinit() {
}

void solve() {
  caseinit();

  int n;
  cin >> n;

  string line;
  for (int i=0; i<n; i++) {
    cin >> s[i];
    line += s[i];
    pos[i] = line.size();
  }

  int m = line.size();
  reverse(line.begin(), line.end());
  suff_array sa(line);

  vector<Pair> p;
  for (int i=0; i<n; i++) {
    for (int j=0; j<i; j++) {
      int len = sa.lcp(m-pos[i],m-pos[j]);
      len = min(len, (int)min(s[i].size(),s[j].size()));
      p.push_back({i,j,len});
    }
  }
  sort(p.begin(), p.end());

  unordered_set<int> done;
  unordered_set<string> seen;
  for (const Pair& it : p) {
    if (done.count(it.i) || done.count(it.j)) continue;
    for (int k=it.len; k>0; k--) {
      string suff = s[it.i].substr(s[it.i].size()-k);
      if (!seen.count(suff)) {
        seen.insert(suff);
        done.insert(it.i);
        done.insert(it.j);
        break;
      }
    }
  }
  cout << seen.size() * 2 << nl;

  return;
}


#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct suff_array {
  const int L; vi s; int i, skip, lvl;
  vector<vi> P; vector<pair<pii,int>> M;
  suff_array(const vi &s) : L(s.size()), s(s), P(1, vi(L, 0)), M(L) {
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
}; //! code adapted from the Stanford Team Notebook

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, k, a;
  cin >> n;

  vi s;
  for (int i=0; i<n; i++) {
    cin >> k;
    for (int j=0; j<k; j++) {
      cin >> a;
      s.push_back(a);
    }
    s.push_back(301);
  }
  n = s.size();

  suff_array sa(s);
  const auto& idx = sa.get_sarray();
  vi id(n);
  for (int i=0; i<n; i++) {
    id[idx[i]] = i;
  }

  priority_queue<int,vi,greater<int>> front;
  for (int i=0; i<n; i++) {
    if (i==0 || s[i-1]==301) {
      front.push(idx[i]);
    }
  }

  ll ans = 0;
  while (!front.empty()) {
    int cur = front.top();
    front.pop();

    ans = (ans*365 + s[id[cur]]) % MOD;
    if (s[id[cur]+1] != 301) {
      front.push(idx[id[cur]+1]);
    }
  }

  cout << (ans*365) % MOD << nl;

  return 0;
}

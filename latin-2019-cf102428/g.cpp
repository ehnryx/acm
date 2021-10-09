#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<int> vi;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// get_sarray()[i] = idx of suffix s[i..L-1] in list of sorted suffixes
struct suff_array {
  const int L; int skip, lvl;
  vector<vi> P; vector<pair<pii,int>> M;
  suff_array(const string &s) : L(s.size()), P(1, vi(L, 0)), M(L) {
    for (int i = 0; i < L-(L==1); i++) P[0][i] = int(s[i]);
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

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  int m = s.size();
  s.push_back(' ');

  int n;
  cin >> n;
  int start[n], len[n];
  for(int i=0; i<n; i++) {
    string t;
    cin >> t;
    start[i] = s.size();
    len[i] = t.size();
    s += t;
  }

  int tot = s.size();
  suff_array sa(s);
  const auto& inv = sa.get_sarray();
  vector<int> idx(tot);
  for(int i=0; i<tot; i++) {
    idx[inv[i]] = i;
  }

  set<int> vals;
  for(int i=0; i<m; i++) {
    vals.insert(inv[i]);
  }

  for(int i=0; i<n; i++) {
    int cnt = 0;
    for(int j=0; j<len[i]; ) {
      int clen = 0;
      int v = start[i]+j;
      auto it = vals.lower_bound(inv[v]);
      if(it!=vals.end()) {
        clen = max(clen, sa.lcp(v, idx[*it]));
      }
      if(it!=vals.begin()) {
        clen = max(clen, sa.lcp(v, idx[*prev(it)]));
      }
      if(clen == 0) {
        cnt = -1;
        break;
      } else {
        j += clen;
        cnt++;
      }
    }
    cout << cnt << nl;
  }

  return 0;
}

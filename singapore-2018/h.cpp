#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ll BIG = 1e15 + 7;
const int M = 26;
const int L = 50;

struct Int {
  ll x;
  Int(ll v=0): x(min(v, BIG)) {}
  Int operator + (const Int& o) const { return Int(x + o.x); }
  Int operator * (const Int& o) const {
    return o.x && x > BIG/o.x + 7 ? Int(BIG) : Int(x*o.x);
  }
};

string to[M];
vector<array<Int,M>> pref;
array<Int,M> jump[M][L];
char first[M][L];

// L * M^2
Int expand(const string& s, int k, int m) {
  array<Int,M> cnt;
  if(s.size() <= L) {
    for(int i=0; i<m; i++) {
      cnt[s[i] - 'a'] = cnt[s[i] - 'a'] + 1;
    }
  } else {
    cnt = pref[m];
  }
  for(int j=L-1; j>=0; j--) {
    if(!(k & 1LL<<j)) continue;
    array<Int,M> nxt;
    for(int i=0; i<M; i++) {
      for(int c=0; c<M; c++) {
        nxt[i] = nxt[i] + cnt[c] * jump[c][j][i];
      }
    }
    cnt = move(nxt);
  }
  return accumulate(cnt.begin(), cnt.end(), Int(0));
}

// L^2 * O(expand) = L^3 * M^2
char solve(const string& s, int k, ll x) {
  //cerr << "solve " << s << " " << k << " " << x << nl;
  if(k == 0) {
    //assert(x <= s.size());
    return s[x - 1];
  }

  int l = 1;
  int r = s.size();
  while(l < r) {
    int m = (l + r) / 2;
    Int len = expand(s, k, m);
    if(x <= len.x) {
      r = m;
    } else {
      l = m + 1;
    }
  }

  Int len = expand(s, k, r - 1);
  //assert(x > len.x);
  //assert(x <= expand(s, k, r).x);
  return solve(to[s[r - 1] - 'a'], k - 1, x - len.x);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  string s;
  cin >> s;
  pref.resize(s.size() + 1);
  for(int i=0; i<s.size(); i++) {
    pref[i+1] = pref[i];
    pref[i+1][s[i] - 'a'] = pref[i+1][s[i] - 'a'] + Int(1);
  }

  for(int i=0; i<M; i++) {
    cin >> to[i];
    first[i][0] = to[i].front();
    for(char c : to[i]) {
      jump[i][0][c-'a'] = jump[i][0][c-'a'] + Int(1);
    }
  }
  for(int j=1; j<L; j++) {
    for(int i=0; i<M; i++) {
      first[i][j] = first[first[i][j-1] - 'a'][j-1];
      for(int c=0; c<M; c++) {
        for(int k=0; k<M; k++) {
          jump[i][j][c] = jump[i][j][c] + jump[i][j-1][k] * jump[k][j-1][c];
        }
      }
    }
  }

  ll k;
  cin >> k;
  for(int j=L-1; j>=0; j--) {
    if(k - (1LL<<j) > L) {
      s[0] = first[s[0] - 'a'][j];
      k -= 1LL << j;
    }
  }

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    ll x;
    cin >> x;
    //assert(x <= expand(s, k, s.size()).x);
    //cerr << "SOLVE " << x << nl;
    cout << solve(s, k, x) << nl;
    //cerr << nl;
  }

  return 0;
}

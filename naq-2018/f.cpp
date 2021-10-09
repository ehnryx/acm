#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef __int128 lll;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 25;
int val[N];
bool adj[N][N];
int childbm[N];
vector<pii> children[N];

int hashlll(const lll& v) {
  return v % MOD;
}

unordered_map<int,ll> memo[N];

void precompute(int root, lll bm) {
  for (const pii& it : children[root]) {
    for (const auto& left : it.first
  }
}

ll solve(int root, lll bm) {
  return 0;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  map<int,int> cnt;
  int a;
  for (int i=0; i<n; i++) {
    cin >> a;
    cnt[a]++;
  }

  int m = 0;
  lll ha = 0;
  for (const auto& it : cnt) {
    ha |= it.second << (5*m);
    val[m++] = it.first;
  }

  for (int i=0; i<m; i++) {
    for (int j=0; j<m; j++) {
      if (val[i] % val[j] == 0) {
        adj[i][j] = true;
        childbm[i] |= 1<<j;
      }
      if (i <= j) {
        ll lcm = (ll)val[i]*val[j] / __gcd(val[i],val[j]);
        for (int k=0; k<m; k++) {
          if (lcm == val[k]) {
            children[k].push_back(pii(i,j));
          }
        }
      }
    }
  }

  lll mask = 0;
  for (int i=0; i<m; i++) {
    mask = mask<<5 | 31;
    precompute(i, (ha & mask) - ((lll)1 << 5*i));
  }

  cout << solve(m-1, ha) << nl;

  return 0;
}

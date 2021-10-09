#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define TESTFILE "mahdi"

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

vector<int> idx[26];

void init() {
  for (int i=0; i<26; i++) {
    idx[i].clear();
  }
}

void solve() {
  init();

  char c; ll l, m, a;
  cin >> c >> l >> m >> a;
  if (!isalpha(c)) for(;;);
  int d = c-'a';
  for (int i=0; i<l; i++) {
    idx[d].push_back(i);
    d = (d*m + (i+1)*a) % 26;
  }

  int n;
  cin >> n;
  for (int i=0; i<n; i++) {
    char ci; ll li, mi, ai;
    cin >> ci >> li >> mi >> ai;
    if (!isalpha(ci)) for(;;);
    int di = ci-'a';
    int pos = -1;
    for (int ii=0; ii<li; ii++) {
      auto it = upper_bound(idx[di].begin(), idx[di].end(), pos);
      if (it == idx[di].end()) {
        pos = -1;
        break;
      } else {
        pos = *it;
      }
      di = (di*mi + (ii+1)*ai) % 26;
    }
    //cerr << nl;
    if (pos == -1) {
      cout << "REPEAT" << nl;
    } else {
      cout << "BRAVO" << nl;
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(TESTFILE ".in", "r", stdin);
#endif

  int T;
  cin >> T;

  for (int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ":" << nl;
    solve();
  }

  return 0;
}

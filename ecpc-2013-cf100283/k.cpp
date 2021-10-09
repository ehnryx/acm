#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define TESTFILE "cubes"

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

const int N = 100;
int len[N];
int ans[N];

bool inrange(int v, int n) { return 0<=v && v<n; }

void solve() {
  int n;
  cin >> n;
  for (int i=0; i<n; i++) {
    cin >> len[i];
  }
  sort(len, len+n);

  if (n%2 == 0) {
    for (int i=0; i<n; i++) {
      (i%2 == 0 ? ans[n/2-1-(i+1)/2] : ans[n/2-1+(i+1)/2]) = len[i];
    }
  } else {
    for (int i=0; i<n; i++) {
      (i%2 == 0 ? ans[n/2+(i+1)/2] : ans[n/2-(i+1)/2]) = len[i];
    }
  }
  cout << nl;
  for (int i=0; i<n; i++) {
    cout << ans[i] << " \n"[i+1==n];
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
    cout << "Case " << tt << ":";
    solve();
  }

  return 0;
}

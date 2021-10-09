#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 5;
const int T = 20;
string grid[N];
bitset<N> sub[T];
int ans[T];

void solve() {
  int t, n;
  cin >> t >> n;

  for (int i=0; i<t; i++) {
    sub[i].reset();
    ans[i] = i;
  }
  for (int i=0; i<n; i++) {
    cin >> grid[i];
    for (int j=0; j<t; j++) {
      if (grid[i][j] == '0') {
        sub[j].set(i);
      }
    }
  }

  for (int i=0; i<t; i++) {
    int best = -1;
    int id = INF;
    cerr << "TIME " << i << nl;
    for (int j=i; j<t; j++) {
      int cnt = sub[ans[j]].count();
      cerr << "check " << sub[ans[j]] << nl;
      if (cnt > best || (cnt == best && ans[j] < ans[id])) {
        best = cnt;
        id = j;
      }
    }
    swap(ans[i], ans[id]);
    cerr << "get ans -> " << sub[ans[i]] << nl;
    for (int j=i+1; j<t; j++) {
      sub[ans[j]] &= ~sub[ans[i]];
    }
  }

  int sum = 0;
  for (int i=0; i<n; i++) {
    for (int j=0; j<t; j++) {
      sum++;
      if (grid[i][ans[j]] == '0') {
        break;
      }
    }
  }

  cout << sum << nl;
  for (int i=0; i<t; i++) {
    cout << ans[i]+1 << " ";
  }
  cout << nl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#define FILENAME "tests"
  cerr << "File IO: " << FILENAME << nl;
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}

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



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#define FILENAME "hamming"
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;

    int ao, ai, bo, bi;
    ao = ai = bo = bi = 0;
    for (char c : a) {
      if (c == '0') ao++;
      else ai++;
    }
    for (char c : b) {
      if (c == '0') bo++;
      else bi++;
    }
    cout << min(ao,bi) + min(ai,bo) << nl;
  }

  return 0;
}

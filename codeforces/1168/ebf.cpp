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

const int N = (1<<12) + 1;
int a[N], b[N], c[N];

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

  FOR(i,1,1<<n) {
    cin >> a[i];
    c[i] = i;
  }

  do {
    unordered_set<int> vals;
    FOR(i,1,1<<n) {
      b[i] = a[i]^c[i];
      vals.insert(b[i]);
    }
    if (vals.size() == (1<<n)) {
      cout << "Shi" << nl;
      return 0;
    }
  } while (next_permutation(c+1,c+1+(1<<n)));
  cout << "Fou" << nl;

  return 0;
}

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

const int N = 1e5+1;
int col[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int T;
  cin >> T;

  while (T--) {
    int n;
    cin >> n;

    int dis = 0;
    FOR(i,1,n-2) {
      int c = rng()%2;
      if (c) cout << i << " " << i+1 << " " << i << " " << i+2 << endl;
      else cout << i << " " << i+2 << " " << i << " " << i+1 << endl;
      cin >> col[i];
      col[i] ^= !c;
      if (i>1 && col[i] == col[i-1]) {
        dis = i+1;
        i++;
      }
    }

    if (dis == 0 || dis == n-1) {
      // pray to paul
      if (rng()%2) cout << n << " " << n-1 << " " << n << " " << n-2 << endl;
      else cout << n << " " << n-2 << " " << n << " " << n-1 << endl;
      cin >> col[n];
    } else {
      // blessed by paul
      cout << n << " " << n-1 << " " << n << " " << dis << endl;
      cin >> col[n];
      if (col[n] != col[n-2]) {
        cout << dis << " " << dis+1 << " " << dis << " " << dis+2 << endl;
        cin >> col[n];
      } else {
        cout << n-1 << " " << dis << " " << n-1 << " " << dis-2 << endl;
        cin >> col[n];
      }
    }
  }

  return 0;
}

// paul pls

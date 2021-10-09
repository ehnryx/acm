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

const int N = 12;
int a[1<<N], b[1<<N], c[1<<N], cnt[N];

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

  For(i,1<<n) {
    cin >> a[i];
    b[i] = i;
    For(j,n) {
      if (a[i]&1<<j) {
        cnt[j]++;
      }
    }
  }

  For(j,n) {
    if (cnt[j]%2 == 1) {
      cout << "Fou" << nl;
      return 0;
    }
  }

  while (clock() < 0.97*CLOCKS_PER_SEC) {
    shuffle(b, b+(1<<n), rng);
    unordered_set<int> vals;
    For(i,1<<n) {
      c[i] = a[i]^b[i];
      vals.insert(c[i]);
    }
    if (vals.size() == 1<<n) {
      cout << "Shi" << nl;
      For(i,1<<n) {
        cout << b[i] << " ";
      }
      cout << nl;
      For(i,1<<n) {
        cout << c[i] << " ";
      }
      cout << nl;
      return 0;
    }
  }
  cout << "Fou" << nl;

  return 0;
}

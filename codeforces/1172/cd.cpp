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
const ll MOD = 998244353;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5+1;
bool good[N]; 
ld val[N];

ld inv(ld x) {
  return 1/x;
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

  int n, m;
  cin >> n >> m;

  For(i,n) {
    cin >> good[i];
  }

  ld sum = 0;
  For(i,n) {
    cin >> val[i];
    sum += val[i];
  }

  For(i,m) {
    ld d = inv(sum);
    sum = 0;
    For(j,n) {
      if (good[j]) {
        val[j] = (val[j] + val[j]*d);
        sum += val[j];
      } else {
        val[j] = (val[j] - val[j]*d);
        sum += val[j];
      }
    }
  }

  For(i,n) {
    cout << val[i] << nl;
  }

  return 0;
}

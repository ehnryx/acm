#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
  for (cin>>n; n; cin>>n) {
    vector<int> bit(32,-1);
    string s;
    int a, b;
    for (int i=0; i<n; i++) {
      cin >> s;
      if (s == "SET") {
        cin >> a;
        bit[a] = 1;
      } else if (s == "CLEAR") {
        cin >> a;
        bit[a] = 0;
      } else if (s == "OR") {
        cin >> a >> b;
        if (bit[a] == 1 || bit[b] == 1) {
          bit[a] = 1;
        } else if (bit[a] == -1 || bit[b] == -1) {
          bit[a] = -1;
        } else {
          bit[a] = 0;
        }
      } else if (s == "AND") {
        cin >> a >> b;
        if (bit[a] == 0 || bit[b] == 0) {
          bit[a] = 0;
        } else if (bit[a] == -1 || bit[b] == -1) {
          bit[a] = -1;
        } else {
          bit[a] = 1;
        }
      } else {
        assert(false);
      }
    }
    for (int i=31; i>=0; i--) {
      if (bit[i]==-1) cout << '?';
      else cout << bit[i];
    }
    cout << nl;
  }

  return 0;
}

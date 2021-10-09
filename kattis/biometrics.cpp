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
    pol p[2];
    int x, y;
    for (int t=0; t<2; t++) {
      for (int i=0; i<n; i++) {
        cin >> x >> y;
        p[t].emplace_back(x,y);
      }
    }
    bool sim = true;
    pt s = (p[0][1]-p[0][0])/(p[1][1]-p[1][0]);
    for (int i=0; i<n; i++) {
      pt v = (p[1][i]-p[1][0])*s + p[0][0];
      sim &= (abs(v-p[0][i]) < EPS);
    }
    cout << (sim ? "similar" : "dissimilar") << nl;
  }

  return 0;
}

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



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  vector<int> pts = {0};
  for (int i=1; i<n; i++) {
    pts.push_back(rng()%m);
  }

  cerr << "points: "; for (int p : pts) cerr << p << " "; cerr << nl;

  cout << 1 << nl;
  cout << n << nl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      cout << abs(pts[i]-pts[j]) << " ";
    }
  }
  cout << nl;

  return 0;
}

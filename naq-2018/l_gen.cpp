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

bool bad(vector<int> a, vector<int> b) {
  for (int i=0; i<a.size(); i++) {
    if (a[i]==b[i]) return true;
  }
  return false;
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

  int n = 100;
  vector<int> a, b;
  for (int i=1; i<=n; i++) {
    a.push_back(i);
    b.push_back(i);
  }
  while (bad(a,b)) {
    shuffle(a.begin(), a.end(), rng);
    shuffle(b.begin(), b.end(), rng);
  }

  cout << n << " " << 2 << nl;
  for (int it : a) cout << it << " ";
  cout << nl;
  for (int it : b) cout << it << " ";
  cout << nl;

  return 0;
}

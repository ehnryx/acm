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

vector<pii> f;
void farey(int n, pii a, pii b) {
  pii mid(a.first+b.first, a.second+b.second);
  if (mid.first+mid.second > n) return;
  f.push_back(mid);
  farey(n,a,mid);
  farey(n,mid,b);
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

  for (int i = 2; i <= n; i++) {
    f = {pii(0,1), pii(1,1)};
    farey(i,pii(0,1),pii(1,1));
    cout << i << ": " << f.size() << nl;
  }

  return 0;
}

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
  cin >> n;

  int a[n];
  vector<pii> vals;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    vals.push_back(pii(a[i], i));
  }
  sort(vals.begin(), vals.end());

  int colour[n];
  set<pii> upper, lower;
  for (int i = 0; i < n/2; i++) {
    colour[vals[i].second] = 1;
    lower.insert(vals[i]);
  }
  for (int i = n/2; i < n; i++) {
    colour[vals[i].second] = 2;
  }

  int maxc, minc;
  maxc = minc = 0;
  for (int i = 0; i < n; i++) {
    if (colour[i] == 1) {
      minc++;
      lower.erase(pii(a[i], i));
    } else {
      maxc++;
      upper.insert(pii(a[i], i));
    }

    if (maxc > minc+1) {
      pii it = *prev(lower.end());
      pii cur = *upper.begin();
      lower.erase(prev(lower.end()));
      upper.erase(upper.begin());

      colour[cur.second] = 1;
      colour[it.second] = 2;
      minc++;
      maxc--;
    }
  }

  ll maxv, minv;
  maxv = minv = 0;

  for (int i = 0; i < n; i++) {
    if (colour[i] == 1) minv += a[i];
    else maxv += a[i];
  }

  cout << maxv << " " << minv << nl;

  return 0;
}

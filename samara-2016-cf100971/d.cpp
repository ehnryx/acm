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

struct Item {
  int i, x, p;
  bool operator < (const Item& o) const {
    return p < o.p;
  }
};

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

  map<int,Item> big;
  vector<Item> sorted;
  for (int i=1; i<=n; i++) {
    int x, p;
    cin >> x >> p;
    Item cur = { i, x, p };
    big[x] = cur;
    sorted.push_back(cur);
  }
  sort(sorted.begin(), sorted.end());

  int ans[n+1];
  for (const Item& it : sorted) {
    big.erase(it.x);
    if (big.empty()) {
      ans[it.i] = -1;
    } else {
      Item ub = { -1, -1, -1 };
      Item lb = { -1, -1, -1 };
      auto jt = big.upper_bound(it.x);
      if (jt != big.end()) {
        ub = jt->second;
      }
      if (jt != big.begin()) {
        lb = prev(jt)->second;
      }
      if (ub.x == -1) {
        ans[it.i] = lb.i;
      } else if (lb.x == -1) {
        ans[it.i] = ub.i;
      } else {
        if (it.x-lb.x < ub.x-it.x) {
          ans[it.i] = lb.i;
        } else if (it.x-lb.x > ub.x-it.x) {
          ans[it.i] = ub.i;
        } else if (lb.p > ub.p) {
          ans[it.i] = lb.i;
        } else {
          ans[it.i] = ub.i;
        }
      }
    }
  }

  for (int i=1; i<=n; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}

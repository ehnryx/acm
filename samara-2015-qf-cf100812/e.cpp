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

struct Card {
  int id, cost, value;
  bool operator < (const Card& v) const {
    return cost < v.cost;
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

  Card val[n];
  for (int i = 0; i < n; i++) {
    cin >> val[i].cost >> val[i].value;
    val[i].id = i+1;
  }
  sort(val, val+n);

  vector<int> ans;
  int cur = 0;
  int best = 1;
  while (cur < n) {
    int id = -1;
    int nxt = 0;
    while (cur < n && val[cur].cost <= best) {
      if (val[cur].id == n) {
        ans.push_back(n);
        cout << ans.size() << nl;
        for (int it : ans) {
          cout << it << " ";
        }
        cout << nl;
        return 0;
      }

      if (val[cur].value > nxt) {
        nxt = val[cur].value;
        id = val[cur].id;
      }
      cur++;
    }

    if (nxt <= best) {
      id = -1;
    } else {
      best = nxt;
    }

    if (id == -1) {
      cout << "No such luck" << nl;
      return 0;
    }
    else {
      ans.push_back(id);
    }
  }

  assert(false);

  return 0;
}

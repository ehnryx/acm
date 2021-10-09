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

const int N = 10;
int p[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  for(int n, x, y;;) {
    cin >> n;
    if (!n) break;

    for (int i=0; i<n; i++) {
      cin >> p[i];
    }
    cin >> x >> y;

    unordered_set<int> vis;
    vector<int> ans;
    queue<ll> bfs;
    bfs.push(1);
    vis.insert(1);
    while (!bfs.empty()) {
      ll cur = bfs.front();
      bfs.pop();
      if (cur >= x) ans.push_back(cur);
      for (int i=0; i<n; i++) {
        ll nxt = cur*p[i];
        if (!vis.count(nxt) && nxt <= y) {
          bfs.push(nxt);
          vis.insert(nxt);
        }
      }
    }
    if (ans.empty()) {
      cout << "none" << nl;
    } else {
      sort(ans.begin(), ans.end());
      cout << ans[0];
      for (int i=1; i<ans.size(); i++) {
        cout << ',' << ans[i];
      }
      cout << nl;
    }
  }

  return 0;
}

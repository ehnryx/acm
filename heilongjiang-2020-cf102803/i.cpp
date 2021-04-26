#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Event {
  int x, t, y;
  Event(int _x, int _t, int _y): x(_x), t(_t), y(_y) {}
  bool operator < (const Event& o) const {
    return tie(x, t, y) > tie(o.x, o.t, o.y);
  }
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  priority_queue<Event> ev;
  for(int i=0; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    ev.emplace(a, -1, c);
    ev.emplace(b, 1, c);
  }

  int ans = 0;
  int dir = 1;
  int lastx = 0;
  int lasty = 0;

  set<int> active;
  active.insert(INF);
  active.insert(-INF);
  while(!ev.empty()) {
    auto [x, t, y] = ev.top();
    ev.pop();
    int cur = lasty + (x - lastx) * dir;

    bool ok = true;
    if(t == -1) {
      active.insert(y);
    } else if(t == 1) {
      active.erase(y);
    } else if(cur == y && active.count(y)) {
      ans++;
      active.erase(y);
      dir *= -1;
    } else {
      ok = false;
    }

    if(ok) {
      auto it = active.lower_bound(cur);
      if(*it < INF) {
        int nx = (*it - cur) * dir + x;
        if(nx >= x) {
          ev.emplace(nx, 0, *it);
        }
      }
      if(*prev(it) > -INF) {
        int nx = (*prev(it) - cur) * dir + x;
        if(nx >= x) {
          ev.emplace(nx, 0, *prev(it));
        }
      }
    }

    lastx = x;
    lasty = cur;
  }

  cout << ans << nl;

  return 0;
}

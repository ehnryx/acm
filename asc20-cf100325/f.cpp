//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "london"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Point {
  int x, y;
  Point(int _x=0, int _y=0): x(_x), y(_y) {}
  bool operator < (const Point& o) const {
    return tie(x, y) < tie(o.x, o.y);
  }
  bool operator == (const Point& o) const {
    return tie(x, y) == tie(o.x, o.y);
  }
  Point operator - (const Point& o) const {
    return Point(x - o.x, y - o.y);
  }
};

ld abs(const Point& v) {
  return sqrt((ld)v.x*v.x + (ld)v.y*v.y);
}

const int N = 400 + 1;
Point v[N];
vector<int> adj[N];
vector<int> graph[N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    int x, y;
    cin >> x >> y;
    v[i] = Point(x, y);
  }
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  vector<pair<Point,int>> x_order, y_order;
  for(int i=1; i<=n; i++) {
    sort(graph[i].begin(), graph[i].end(), [=](int a, int b) {
      return v[a] - v[i] < v[b] - v[i];
    });
    x_order.emplace_back(v[i], i);
    y_order.emplace_back(v[i], i);
  }
  sort(x_order.begin(), x_order.end());
  sort(y_order.begin(), y_order.end(),
    [](const pair<Point,int>& a, const pair<Point,int>& b) {
      return a.first.y < b.first.y;
    }
  );

  map<Point,vector<pair<int,int>>> shifts;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      if(!(v[i] < v[j])) continue;
      Point d = v[j] - v[i];
      for(int ii=0, jj=0; ii<graph[i].size() && jj<graph[j].size(); ) {
        if(v[graph[i][ii]] - v[i] < v[graph[j][jj]] - v[j]) {
          ii++;
        } else if(v[graph[j][jj]] - v[j] < v[graph[i][ii]] - v[i]) {
          jj++;
        } else {
          shifts[d].emplace_back(i, graph[i][ii]);
          ii++;
          jj++;
        }
      }
    }
  }

  ld ans = 0;
  vector<int> path;
  Point d_ans;
  for(const auto& [d, edges] : shifts) {
    for(int i=1; i<=n; i++) {
      adj[i].clear();
    }
    for(const auto& [a, b] : edges) {
      adj[a].push_back(b);
    }

    {
      vector<ld> dp(n+1), pre(n+1);
      for(const auto& [_, i] : x_order) {
        for(int j : adj[i]) {
          if(v[j].x < v[i].x) {
            ld val = abs(v[i] - v[j]) + dp[j];
            if(val > dp[i]) {
              dp[i] = val;
              pre[i] = j;
            }
          }
        }
      }
      auto it = max_element(dp.begin(), dp.end());
      if(*it > ans) {
        ans = *it;
        d_ans = d;
        path.clear();
        for(int i = it - dp.begin(); i; i = pre[i]) {
          path.push_back(i);
        }
        reverse(path.begin(), path.end());
      }
    }

    {
      vector<ld> dp(n+1), pre(n+1);
      for(const auto& [_, i] : y_order) {
        for(int j : adj[i]) {
          if(v[j].y < v[i].y) {
            ld val = abs(v[i] - v[j]) + dp[j];
            if(val > dp[i]) {
              dp[i] = val;
              pre[i] = j;
            }
          }
        }
      }
      auto it = max_element(dp.begin(), dp.end());
      if(*it > ans) {
        ans = *it;
        d_ans = d;
        path.clear();
        for(int i = it - dp.begin(); i; i = pre[i]) {
          path.push_back(i);
        }
        reverse(path.begin(), path.end());
      }
    }
  }

  cout << ans << nl;
  if(ans > 0) {
    cout << path.size() << nl;
    for(int it : path) {
      cout << it << " ";
    }
    cout << nl;

    int s = 0;
    for(int i=1; i<=n; i++) {
      if(v[i] - v[path[0]] == d_ans) {
        s = i;
        break;
      }
    }
    assert(s);

    vector<int> other = {s};
    for(int i=1; i<path.size(); i++) {
      for(int t : graph[s]) {
        if(v[t] - v[path[i]] == d_ans) {
          s = t;
          break;
        }
      }
      other.push_back(s);
    }

    for(int it : other) {
      cout << it << " " ;
    }
    cout << nl;
  }

  return 0;
}

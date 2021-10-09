#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

struct Segment {
  int l, r, i, t;
  bool operator < (const Segment& o) const {
    return l < o.l;
  }
  bool operator > (const Segment& o) const {
    return r < o.r;
  }
};

const int N = 2e5+1;
int l[N], d[N], vis[N];
vector<int> adj[N];

int minv[2], maxv[2];
bool dfs(int u, int p, int v) {
  vis[u] = v;
  minv[v] = min(minv[v], l[u]);
  maxv[v] = max(maxv[v], l[u]);
  minv[v^1] = min(minv[v^1], d[u]);
  maxv[v^1] = max(maxv[v^1], d[u]);
  for (int x : adj[u]) {
    if (x!=p && vis[x] == -1) {
      if (!dfs(x, u, v^1)) return false;
    } else if (vis[x] == v) {
      return false;
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  vis[0] = -1;

  int T; cin >> T;
  for (int tt = 1; tt <= T; tt++) {
    cout << "Case " << tt << ": ";

    int n, m;
    cin >> n >> m;
    for (int i=1; i<=n; i++) {
      adj[i].clear();
      vis[i] = -1;
    }
    for (int i=0; i<m; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    for (int i=1; i<=n; i++) {
      cin >> l[i] >> d[i];
    }

    vector<Segment> left, right;
    bool bad = false;
    for (int i=1; i<=n; i++) {
      if (vis[i] == -1) {
        minv[0] = minv[1] = INF;
        maxv[0] = maxv[1] = -INF;
        if (!dfs(i,0,0)) {
          bad = true;
          break;
        } else {
          left.push_back({minv[0], maxv[0], i, 0});
          left.push_back({minv[1], maxv[1], i, 1});
          right.push_back({minv[0], maxv[0], i, 0});
          right.push_back({minv[1], maxv[1], i, 1});
        }
      }
    }

    if (bad) {
      cout << "IMPOSSIBLE" << nl;
    }
    else {
      sort(left.begin(), left.end(), less<Segment>());
      sort(right.begin(), right.end(), greater<Segment>());
      m = left.size()/2;

      //cerr << "left" << nl; for (Segment s : left) //cerr << s.l << " " << s.r << " " << s.i << nl;
      //cerr << "right" << nl; for (Segment s : right) //cerr << s.l << " " << s.r << " " << s.i << nl;

      int ans = INF;
      map<int,int> cnt;
      set<pii> active;
      set<pii> dead;
      int j = 0;
      for (int i=0; i<=m; i++) {
        for ( ; j<2*m && cnt.size() < m; j++) {
          if (!dead.count({right[j].i, right[j].t})) {
            active.insert({right[j].i, right[j].t});
            cnt[right[j].i]++;
          }
        }
        if (cnt.size() < m) break;
        //cerr << i << " -> " << j << " : " << max(left[i].r,right[j-1].r)-left[i].l << nl;
        ans = min(ans, max(left[i].r, right[j-1].r) - left[i].l);
        dead.insert({left[i].i, left[i].t});
        if (active.count({left[i].i, left[i].t})) {
          if ((--cnt[left[i].i]) == 0) {
            cnt.erase(left[i].i);
          }
        }
      }
      cout << ans << nl;
    }
  }

  return 0;
}

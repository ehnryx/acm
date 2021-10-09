#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int adj[26][26];
int deg[26];
int dist[26];
int vis[26];
int anc[26];
int par[26];
vector<int> ans;

void init() {
  memset(adj, 0, sizeof adj);
  memset(deg, 0, sizeof deg);
  memset(dist, 0, sizeof dist);
  memset(vis, 0, sizeof vis);
  memset(anc, 0, sizeof anc);
  memset(par, -1, sizeof par);
  ans.clear();
}

bool find_cycle(int cur, int pre = -1) {
  par[cur] = pre;
  vis[cur] = true;
  anc[cur] = true;
  for (int i = 0; i < 26; i++) {
    if (adj[cur][i] == 0) {
      if (!vis[i]) {
        if (find_cycle(i, cur)) return true;
      } else if (anc[i]) {
        for (int x = cur; x != i; x = par[x]) {
          ans.push_back(x);
        }
        ans.push_back(i);
        reverse(ans.begin(), ans.end());
        return true;
      }
    }
  }
  anc[cur] = false;
  return false;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;

    init();

    char a, b;
    for (int i = 0; i < n; i++) {
      cin >> a >> b;
      adj[a-'a'][b-'a'] = 1;
    }

    find_cycle(0);
    if (!ans.empty()) {
      // cycle exists, make 20x20 grid
      int sz = ans.size();
      char grid[20][20];
      for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 20; j++) {
          if (0 <= i-j && i-j < 20) {
            grid[j][i-j] = ans[i % sz] + 'a';
          }
        }
      }
      for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
          cout << grid[i][j];
        }
        cout << nl;
      }
    }

    else {
      // longest path in dag
      queue<int> q;
      for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
          if (adj[i][j] == 0) deg[j]++;
        }
      }
      for (int i = 0; i < 26; i++) {
        if (deg[i] == 0) {
          q.push(i);
          dist[i] = 1;
        }
      }
      while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int i = 0; i < 26; i++) {
          if (adj[cur][i] == 0) {
            if (dist[cur] + 1 > dist[i]) {
              par[i] = cur;
              dist[i] = dist[cur] + 1;
            }
            deg[i]--;
            if (deg[i] == 0) q.push(i);
          }
        }
      }

      int best = 0;
      int last = -1;
      for (int i = 0; i < 26; i++) {
        if (dist[i] > best) {
          best = dist[i];
          last = i;
        }
      }
      if (best > 0) {
        if (best % 2 == 0) best--;
        for (int i = 0; i < best; i++) {
          ans.push_back(last);
          last = par[last];
        }
      }
      reverse(ans.begin(), ans.end());

      int sz = (best+1)/2;
      char grid[20][20];
      for (int i = 0; i < best; i++) {
        for (int j = 0; j < sz; j++) {
          if (0 <= i-j && i-j < sz) {
            grid[j][i-j] = ans[i] + 'a';
          }
        }
      }
      for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
          cout << grid[i][j];
        }
        cout << nl;
      }
    }
  }

  return 0;
}

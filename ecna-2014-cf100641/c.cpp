#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int G = 5, N = 6;

struct pos {
  int x, y;
};
set<pair<int, int>> rem;
vector<pair<pos, pos>> ps;

int score(const vector<int>& cnt, bool& y) {
  for (int i : cnt) {
    if (i == 5) {
      if (y) return 100;
      y = 1;
      return 50;
    }
  }
  for (int i = 1; i+4 <= N; i++) {
    bool shit = 0;
    for (int j = 0; j < 5; j++) {
      if (!cnt[i+j]) {
        shit = 1;
        break;
      }
    }
    if (!shit) {
      return 40;
    }
  }
  for (int i = 1; i+3 <= N; i++) {
    bool shit = 0;
    for (int j = 0; j < 4; j++) {
      if (!cnt[i+j]) {
        shit = 1;
        break;
      }
    }
    if (!shit) {
      return 30;
    }
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      if (cnt[i] == 3 && cnt[j] == 2) return 25;
    }
  }
  for (int i = 1; i <= N; i++) {
    if (cnt[i] == 4) {
      return 4*i;
    }
  }
  for (int i = 1; i <= N; i++) {
    if (cnt[i] == 3) {
      return 3*i;
    }
  }
  return 0;
}

int calc(const vector<vector<int>>& grid) {
  int ans = 0;
  bool y = 0;
  for (int i = 0; i < G; i++) {
    vector<int> cnt(7);
    for (int j = 0; j < G; j++) {
      cnt[grid[i][j]]++;
    }
    ans += score(cnt, y);
  }
  for (int i = 0; i < G; i++) {
    vector<int> cnt(7);
    for (int j = 0; j < G; j++) {
      cnt[grid[j][i]]++;
    }
    ans += score(cnt, y);
  }
  vector<int> cnt(7);
  for (int i = 0; i < G; i++) {
    cnt[grid[i][i]]++;
  }
  ans += score(cnt, y);
  cnt = vector<int>(7);
  for (int i = 0; i < G; i++) {
    cnt[grid[i][G-1-i]]++;
  }
  ans += score(cnt, y);
  return ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int T; cin >> T;
  for (int tt = 1; tt <= T; tt++) {
    rem.clear();
    ps.clear();
    for (int i = 1; i <= N; i++) {
      for (int j = i; j <= N; j++) {
        rem.emplace(i, j);
      }
    }
    vector<vector<int>> grid(G, vector<int>(G));
    for (int i = 0; i < 13; i++) {
      char c; cin >> c;
      if (c == 'V') {
        int a, b; cin >> a >> b;
        rem.erase(make_pair(min(a, b), max(a, b)));
        for (int x = 0; x < G-1; x++) {
          for (int y = 0; y < G; y++) {
            if (!grid[x][y] && !grid[x+1][y]) {
              grid[x][y] = a;
              grid[x+1][y] = b;
              ps.emplace_back(pos{x, y}, pos{x+1, y});
              goto end;
            }
          }
        }
      } else if (c == 'H') {
        int a, b; cin >> a >> b;
        rem.erase(make_pair(min(a, b), max(a, b)));
        for (int x = 0; x < G; x++) {
          for (int y = 0; y < G-1; y++) {
            if (!grid[x][y] && !grid[x][y+1]) {
              grid[x][y] = a;
              grid[x][y+1] = b;
              ps.emplace_back(pos{x, y}, pos{x, y+1});
              goto end;
            }
          }
        }
      } else {
        int a; cin >> a;
        for (int x = 0; x < G; x++) {
          for (int y = 0; y < G; y++) {
            if (!grid[x][y]) {
              grid[x][y] = a;
              goto end;
            }
          }
        }
      }
end:;
    }
    int ans = calc(grid);
    for (const auto& d : rem) {
      for (const auto& p : ps) {
        int a = grid[p.first.x][p.first.y], b = grid[p.second.x][p.second.y];
        grid[p.first.x][p.first.y] = d.first;
        grid[p.second.x][p.second.y] = d.second;
        ans = max(ans, calc(grid));
        swap(grid[p.first.x][p.first.y], grid[p.second.x][p.second.y]);
        ans = max(ans, calc(grid));
        grid[p.first.x][p.first.y] = a;
        grid[p.second.x][p.second.y] = b;
      }
    }
    cout << "Case " << tt << ": " << ans << nl;
  }

  return 0;
}

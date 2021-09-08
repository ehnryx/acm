#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const char nl = '\n';

struct cactus {
  int n, m;
  vector<vector<int>> a;
  cactus(int _n, int _m): n(_n), m(_m), a(n, vector<int>(m)) {}
  void poke() {
    for (vector<int>& row : a) {
      fill(begin(row), end(row), 0);
    }
  }
  void update(int i, int j) {
    a[i][j] = 1;
  }
  void build() {
    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++) {
        a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
      }
    }
  }
  int query(int i, int j, int x, int y) {
    x = min(x, n - 1);
    y = min(y, m - 1);
    return a[x][y] + a[i - 1][j - 1] - a[x][j - 1] - a[i - 1][y];
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, k;
  cin >> n >> m >> k;
  cactus sad(n + 1, m + 1);
  for (int i = 0; i < k; i++) {
    int a, b;
    cin >> a >> b;
    sad.update(a, b);
  }
  sad.build();

  function<int(int, int)> get = [=](int i, int j) {
    return i * (m + 1) + j;
  };
  vector<int> dsu((n + 1) * (m + 1), -1);
  function<int(int)> find = [&](int i) {
    if (dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int, int)> link = [&](int i, int j) {
    i = find(i);
    j = find(j);
    if (i != j) {
      dsu[i] = j;
    }
  };

  cactus eyqs(n + 1, m + 1);

  int l = 0;
  int r = min(n, m);
  while (l < r) {
    int len = (l + r + 1) / 2;

    eyqs.poke();
    for (int i = len; i <= n; i++) {
      for (int j = len; j <= m; j++) {
        if (!sad.query(i - len + 1, j - len + 1, i, j)) {
          eyqs.update(i, j);
        }
      }
    }
    eyqs.build();

    bool ok = true;
    for (int i = 1; i <= n && ok; i++) {
      for (int j = 1; j <= m && ok; j++) {
        if (!sad.query(i, j, i, j)) {
          ok &= (eyqs.query(i, j, i + len - 1, j + len - 1) > 0);
        }
      }
    }

    if (!ok) {
      r = len - 1;
      continue;
    }

    fill(begin(dsu), end(dsu), -1);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (!eyqs.query(i, j, i, j)) continue;
        for (auto [x, y] : { pair(i - 1, j), pair(i, j - 1) }) {
          if (x < 1 || n < x || y < 1 || m < y) continue;
          if (eyqs.query(x, y, x, y)) {
            link(get(i, j), get(x, y));
          }
        }
      }
    }

    int roots = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (!eyqs.query(i, j, i, j)) continue;
        roots += (find(get(i, j)) == get(i, j));
      }
    }

    if (roots > 1) {
      r = len - 1;
    } else {
      l = len;
    }
  }

  cout << r << nl;

  return 0;
}

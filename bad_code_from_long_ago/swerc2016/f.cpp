#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n;
int t[N], id[N], nxt[N], son[N], ed[N], sz[N];
long long bit[N], ans[N];

void addedge(int x, int y, int& m) {
  nxt[++m] = son[x];
  son[x] = m;
  ed[m] = y;
}

void dfs(int x, int& cnt) {
  sz[x] = 1;
  id[x] = ++cnt;
  for (int i = son[x]; i; i = nxt[i]) {
    dfs(ed[i], cnt);
    sz[x] += sz[ed[i]];
  }
}

long long bit_query(int x) {
  long long ans = 0;
  for (; x; x -= x & -x) {
    ans += bit[x];
  }
  return ans;
}

long long bit_query_range(int x, int y) {
  return bit_query(y) - bit_query(x - 1);
}

void bit_insert(int x, int d) {
  for (; x <= n; x += x & -x) {
    bit[x] += d;
  }
}

long long query(int x) {
  return bit_query_range(id[x], id[x] + sz[x] - 1);
}

void insert(int x) {
  bit_insert(id[x], t[x]);
}

int main() {
  scanf("%d", &n);
  int root;
  vector<pair<int, int> > v;
  for (int i = 1, m = 0; i <= n; i++) {
    int x, y;
    scanf("%d%d%d", &x, &y, &t[i]);
    if (x == -1) {
      root = i;
    } else {
      addedge(x, i, m);
    }
    v.push_back(make_pair(y, i));
  }
  int cnt = 0;
  dfs(root, cnt);
  sort(v.begin(), v.end());
  for (int i = 0, j; i < n; i = j) {
    for (j = i; j < n && v[j].first == v[i].first; j++) {
      ans[v[j].second] = query(v[j].second);
    }
    for (int k = i; k < j; k++) {
      insert(v[k].second);
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%I64d\n", ans[i]);
  }
  return 0;
}

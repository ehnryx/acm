#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int b, n, e, sb, sn, se;
int m;
int cc[N];
vector<int> v;

bool cmp(int a, int b) {
  return a > b;
}

bool check(int k) {
  multiset<tuple<int, int, int> > s;
  for (int i = 0; i < m * 2; i++) {
    for (int j = i + 1; j < m * 2; j++) {
      s.insert(make_tuple(v[i] + v[j], i, j));
    }
  }
  for (int i = 1; i <= m; i++) {
    auto it = s.lower_bound(make_tuple(k / cc[i] + (k % cc[i] != 0), -1, -1));
    if (it == s.end()) {
      return false;
    }
    auto tup = *it;
    int a = get<0>(tup), b = get<1>(tup), c = get<2>(tup);
    for (int j = b + 1; j < m * 2; j++) {
      s.erase(make_tuple(v[b] + v[j], b, j));
    }
    for (int j = c + 1; j < m * 2; j++) {
      s.erase(make_tuple(v[c] + v[j], c, j));
    }
    for (int j = 0; j < b; j++) {
      s.erase(make_tuple(v[j] + v[b], j, b));
    }
    for (int j = 0; j < c; j++) {
      s.erase(make_tuple(v[j] + v[c], j, c));
    }
  }
  return true;
}

int main() {
  scanf("%d%d%d", &b, &n, &e);
  scanf("%d%d%d", &sb, &sn, &se);
  for (int i = 0; i < b; i++) {
    v.push_back(sb);
  }
  for (int i = 0; i < n; i++) {
    v.push_back(sn);
  }
  for (int i = 0; i < e; i++) {
    v.push_back(se);
  }
  m = (b + n + e) / 2;
  int ma = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &cc[i]);
    ma = max(ma, cc[i]);
  }
  sort(cc + 1, cc + m + 1, cmp);
  int l = 0, r = ma * se * 2, ans = 0;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}

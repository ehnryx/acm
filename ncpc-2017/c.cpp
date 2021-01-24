#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

const int INF = 0x3f3f3f3f;

int sub(int a, int b) {
  int s = a - b;
  if(s < 0) s += 360;
  return s;
}

tuple<int,int,int> range(const set<pair<int,int>>& s, int v) {
  auto right = next(s.lower_bound(make_pair(v, 0)));
  if(right == s.end()) right = s.begin();
  auto left = prev(s.upper_bound(make_pair(v, INF)));
  if(left == s.begin()) left = prev(s.end());
  else left = prev(left);
  int diff = sub(right->first, v) + sub(v, left->first);
  return make_tuple(diff, left->second, right->second);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  vector<int> r(n), g(n), b(n), id(n);
  set<pair<int,int>> red, green, blue;
  for(int i=0; i<n; i++) {
    cin >> r[i] >> g[i] >> b[i] >> id[i];
    red.insert(make_pair(r[i], i));
    green.insert(make_pair(g[i], i));
    blue.insert(make_pair(b[i], i));
  }

  vector<int> value(n);
  set<tuple<int,int,int>> cards;
  for(int i=0; i<n; i++) {
    value[i] = get<0>(range(red, r[i]))
        + get<0>(range(blue, b[i]))
        + get<0>(range(green, g[i]));
    cards.insert(make_tuple(value[i], -id[i], i));
  }

  vector<int> out;
  while(!cards.empty()) {
    auto [v, cur, i] = *cards.begin();
    cards.erase(cards.begin());
    out.push_back(-cur);

    set<int> update;
    auto [_r, r1, r2] = range(red, r[i]);
    update.insert(r1);
    update.insert(r2);
    auto [_b, b1, b2] = range(blue, b[i]);
    update.insert(b1);
    update.insert(b2);
    auto [_g, g1, g2] = range(green, g[i]);
    update.insert(g1);
    update.insert(g2);

    red.erase(make_pair(r[i], i));
    blue.erase(make_pair(b[i], i));
    green.erase(make_pair(g[i], i));
    update.erase(i);
    for(int j : update) {
      cards.erase(make_tuple(value[j], -id[j], j));
      value[j] = get<0>(range(red, r[j]))
          + get<0>(range(blue, b[j]))
          + get<0>(range(green, g[j]));
      cards.insert(make_tuple(value[j], -id[j], j));
    }
  }

  assert(out.size() == n);
  for(int it : out) {
    cout << it << nl;
  }

  return 0;
}

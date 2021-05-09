#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  static const int inf = 0x3f3f3f3f;
  int value, lazy;
  Node(): value(inf), lazy(inf) {}
  void put(int v) { value = min(value, v); lazy = min(lazy, v); }
  int get() const { return value; }
  void push(Node& a, Node& b) {
    if(lazy != inf) {
      a.put(lazy);
      b.put(lazy);
      lazy = inf;
    }
  }
  void pull(const Node&, const Node&) {}
};

struct Bugs {
  bool have;
  vector<int> all;
  Bugs() = default;
  void put(int v) {
    if(v < 0) all.clear();
    else all.push_back(v);
    have = !all.empty();
  }
  bool contains() const { return have; }
  void push(Bugs&, Bugs&) {}
  void pull(const Bugs& a, const Bugs& b) { have = a.have || b.have; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  map<long long, int> remap;

  vector<int> x(n);
  vector<long long> t(n);
  vector<pair<int, int>> order;
  for(int i=0; i<n; i++) {
    cin >> x[i] >> t[i];
    order.emplace_back(x[i], i);
    remap[x[i]];
  }
  sort(begin(order), end(order));
  vector<int> rank(n);
  for(int i=0; i<n; i++) {
    rank[order[i].second] = i;
  }

  vector<pair<int,int>> bug(m);
  for(int i=0; i<m; i++) {
    cin >> bug[i].first >> bug[i].second;
    remap[bug[i].first];
  }

  int rid = 0;
  for(auto& it : remap) {
    it.second = rid++;
  }

  segment_tree<Node, int> st(rid);
  for(int i=0; i<n; i++) {
    int left = remap[x[i]];
    int right = prev(remap.upper_bound(x[i] + t[i]))->second;
    st.update(left, right, rank[i]);
  }

  segment_tree<Bugs, int> have(rid);
  vector<int> cnt(n);
  for (auto [p, b] : bug) {
    int j = st.query_point(remap[p]);
    if(j == Node::inf) {
      have.update_point(remap[p], b);
    } else {
      j = order[j].second;
      cnt[j]++;
      t[j] += b;
      int left = remap[x[j]];
      int right = prev(remap.upper_bound(x[j] + t[j]))->second;
      int leaf = have.search_left(left, right);
      while (leaf != -1) {
        for(int add : have[leaf + have.length].all) {
          cnt[j]++;
          t[j] += add;
        }
        right = prev(remap.upper_bound(x[j] + t[j]))->second;
        have.update_point(leaf, -1);
        leaf = have.search_left(left, right);
      }
      st.update(left, right, rank[j]);
    }
  }

  for(int i=0; i<n; i++) {
    cout << cnt[i] << " " << t[i] << nl;
  }

  return 0;
}

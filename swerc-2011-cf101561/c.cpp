//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

const int N = 1<<17;

struct SegTree {
  ll st[2*N];
  void clear(int r) {
    int l = 0;
    for(l+=N, r+=N; l<r; l/=2, r/=2) {
      fill(st+l, st+r, INFLL);
    }
  }
  void insert(int i, ll v) {
    st[i+=N] = v;
    for(i/=2; i>0; i/=2) {
      st[i] = min(st[2*i], st[2*i+1]);
    }
  }
  ll query(int l, int r) {
    ll res = INFLL;
    for(l+=N, r+=N; l<r; l/=2, r/=2) {
      if(l&1) res = min(res, st[l++]);
      if(r&1) res = min(res, st[--r]);
    }
    return res;
  }
};

SegTree topleft, botleft, topright, botright;

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  for(int n; cin >> n && n != -1; ) {
    map<int,int> remap;
    vector<pair<int,int>> v;
    for(int i=0; i<n; i++) {
      int x, y;
      cin >> x >> y;
      v.emplace_back(x, y);
      remap[y];
    }

    int rid = 0;
    for(auto& it : remap) {
      it.second = rid++;
    }
    remap[INF] = rid;
    topleft.clear(rid);
    botleft.clear(rid);
    topright.clear(rid);
    botright.clear(rid);

    int m;
    cin >> m;
    vector<tuple<int,int,int>> w;
    for(int i=0; i<m; i++) {
      int x, y;
      cin >> x >> y;
      w.emplace_back(x, y, i);
    }

    sort(v.begin(), v.end());
    sort(w.begin(), w.end());
    vector<int> line(n), last(rid, -1);
    for(int i=n-1; i>=0; i--) {
      auto [x, y] = v[i];
      int ry = remap[y];
      topright.insert(ry, x + y);
      botright.insert(ry, x - y);
      line[i] = last[ry];
      last[ry] = x;
    }

    vector<ll> ans(m, INFLL);
    for(int i=0, j=0; i<m; i++) {
      auto [wx, wy, id] = w[i];
      while(j < n && v[j].first < wx) {
        auto [x, y] = v[j];
        int ry = remap[y];
        topleft.insert(ry, -x + y);
        botleft.insert(ry, -x - y);
        if(line[j] == -1) {
          topright.insert(ry, INFLL);
          botright.insert(ry, INFLL);
        } else {
          x = line[j];
          topright.insert(ry, x + y);
          botright.insert(ry, x - y);
        }
        j++;
      }

      int mid = remap.lower_bound(wy)->second;
      ans[id] = min(ans[id], topleft.query(mid, rid) + wx - wy);
      ans[id] = min(ans[id], botleft.query(0, mid) + wx + wy);
      ans[id] = min(ans[id], topright.query(mid, rid) - wx - wy);
      ans[id] = min(ans[id], botright.query(0, mid) - wx + wy);
    }

    for(int i=0; i<m; i++) {
      cout << ans[i] << nl;
    }
    cout << nl;
  }

  return 0;
}

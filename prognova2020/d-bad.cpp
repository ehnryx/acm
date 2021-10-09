#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
#define int ll
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Item {
  int v, t, i, j;
  bool operator < (const Item& o) const {
    if(v != o.v) return v < o.v;
    else return t < o.t;
  }
};

const int N = 2e5+1;
int val[N], p[N];

#undef int
int main() {
#define int ll
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  unordered_map<string,int> idx;
  for(int i=1; i<=n; i++) {
    string s;
    cin >> s >> val[i];
    if(isdigit(s.back())) {
      if(s.back() == '1') {
        s.pop_back();
        idx[s] = i;
      } else {
        s.pop_back();
        p[i] = idx[s];
      }
    }
  }

  unordered_set<int> skip;
  for(int i=1; i<=n; i++) {
    if(p[i] && val[i] < val[p[i]]) {
      skip.insert(p[i]);
    }
  }
  vector<Item> order;
  for(int i=1; i<=n; i++) {
    if(skip.count(i)) continue;
    if(p[i] && val[i] < val[p[i]]) {
      order.push_back({val[i] + val[p[i]], true, i, p[i]});
    } else {
      order.push_back({2*val[i], false, i});
    }
  }
  sort(order.begin(), order.end());

  function<int(int)> count = [&](int ub) {
    int cnt = 0;
    for(auto [v, t, i, j] : order) {
      if(v < ub) {
        cnt += 1 + t;
      }
    }
    return cnt;
  };

  function<ll(int)> solve = [&](int ub) {
    int rmax = -1;
    ll ans = 0;
    int cnt = 0;
    vector<Item> o;
    unordered_set<int> taken;
    for(auto [v, t, i, j] : order) {
      if(v < ub) {
        ans += v;
        cnt++;
        taken.insert(i);
        rmax = max(rmax, val[i]);
        if(t) {
          ans += v;
          cnt++;
          taken.insert(j);
        } else {
          assert(!p[i] || taken.count(p[i]));
        }
      } else if(v == ub) {
        o.push_back({v, t, i, j});
      }
    }
    assert(ans%2 == 0);
    while(cnt < m-1) {
      rmax = max(rmax, val[o.back().i]);
      if(o.back().t) {
        taken.insert(o.back().i);
        taken.insert(o.back().j);
        o.pop_back();
        ans += 2*ub;
        cnt += 2;
      } else {
        assert(!p[o.back().i] || taken.count(p[o.back().i]));
        taken.insert(o.back().i);
        o.pop_back();
        ans += ub;
        cnt += 1;
      }
    }
    if(cnt < m && !o.front().t) {
      ans += ub;
      cnt += 1;
    }
    if(cnt == m) {
      return ans;
    }

    int minv = 2*INF;
    int left = 0;
    for(int i=1; i<=n; i++) {
      if(!taken.count(i) && (!p[i] || taken.count(p[i]))) {
        minv = min(minv, 2*val[i]);
        left++;
      }
    }
    assert(left == n-(m-1));
    assert(minv != 2*INF);
    ll res = ans + minv;
    if(rmax != -1) {
      res = min(res, ans + 2*ub - rmax);
    }
    return res;
  };

  int l = 0;
  int r = 2*INF;
  while(l<r) {
    int mid = (l+r+1)/2;
    if(count(mid) <= m) {
      l = mid;
    } else {
      r = mid-1;
    }
  }
  ll ans = solve(r);
  assert(ans%2 == 0);
  cout << ans/2 << nl;

  return 0;
}

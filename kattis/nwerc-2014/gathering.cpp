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

pair<ll,ll> revert(ll a, ll b) {
  return make_pair((a - b) / 2, (a + b) / 2);
}

vector<ll> xvals, yvals, px, py;

ll query_x(ll v) {
  if(v%2) return INFLL;
  int n = xvals.size();
  int smaller = lower_bound(xvals.begin(), xvals.end(), v) - xvals.begin();
  assert(0 <= smaller && smaller <= n);
  return (smaller*v - px[smaller]) + (px[n]-px[smaller] - (n-smaller)*v);
}

ll query_y(ll v) {
  if(v%2) return INFLL;
  int n = yvals.size();
  int smaller = lower_bound(yvals.begin(), yvals.end(), v) - yvals.begin();
  assert(0 <= smaller && smaller <= n);
  return (smaller*v - py[smaller]) + (py[n]-py[smaller] - (n-smaller)*v);
}

ll get_x(const pair<ll,ll>& a, const pair<ll,ll>& b, ll y) {
  if(a.second == b.second) return a.first;
  return (b.first - a.first) / (b.second - a.second) * (y - a.second) + a.first;
}

ll get_y(const pair<ll,ll>& a, const pair<ll,ll>& b, ll x) {
  if(a.first == b.first) return a.second;
  return (b.second - a.second) / (b.first - a.first) * (x - a.first) + a.second;
}

ll check_point(const pair<ll,ll>& v) {
  return query_x(v.first) + query_y(v.second);
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  ll top, bot, left, right;
  bot = left = -INFLL;
  top = right = INFLL;
  for(int i=0; i<n; i++) {
    ll a, b;
    cin >> a >> b;
    a *= 2;
    b *= 2;
    xvals.push_back(a);
    yvals.push_back(b);
    left = max(left, a+b);
    right = min(right, a+b);
    bot = max(bot, b-a);
    top = min(top, b-a);
  }

  px.resize(n+1);
  py.resize(n+1);
  sort(xvals.begin(), xvals.end());
  sort(yvals.begin(), yvals.end());
  partial_sum(xvals.begin(), xvals.end(), px.begin() + 1);
  partial_sum(yvals.begin(), yvals.end(), py.begin() + 1);

  ll d;
  cin >> d;
  d *= 2;
  left -= d;
  right += d;
  bot -= d;
  top += d;

  if(left > right || bot > top) {
    cout << "impossible" << nl;
    return 0;
  }

  ll ans = INFLL;

  pair<ll,ll> pleft = revert(left, top);
  pair<ll,ll> pright = revert(right, bot);
  pair<ll,ll> pbot = revert(left, bot);
  pair<ll,ll> ptop = revert(right, top);

  function<pair<ll,ll>(ll)> get_range_x = [&](ll y) {
    ll lb = y < pleft.second ? get_x(pleft, pbot, y) : get_x(pleft, ptop, y);
    ll ub = y < pright.second ? get_x(pright, pbot, y) : get_x(pright, ptop, y);
    return make_pair(lb, ub);
  };

  function<pair<ll,ll>(ll)> get_range_y = [&](ll x) {
    ll lb = x < pbot.first ? get_y(pbot, pleft, x) : get_y(pbot, pright, x);
    ll ub = x < ptop.first ? get_y(ptop, pleft, x) : get_y(ptop, pright, x);
    return make_pair(lb, ub);
  };

  ans = min(ans, check_point(pleft));
  ans = min(ans, check_point(pright));
  ans = min(ans, check_point(ptop));
  ans = min(ans, check_point(pbot));
  if(pleft != ptop) {
    ans = min(ans, check_point(make_pair(pleft.first + 1, pleft.second + 1)));
    ans = min(ans, check_point(make_pair(ptop.first - 1, ptop.second - 1)));
  }
  if(pleft != pbot) {
    ans = min(ans, check_point(make_pair(pleft.first + 1, pleft.second - 1)));
    ans = min(ans, check_point(make_pair(pbot.first - 1, pbot.second + 1)));
  }
  if(pright != ptop) {
    ans = min(ans, check_point(make_pair(pright.first - 1, pright.second + 1)));
    ans = min(ans, check_point(make_pair(ptop.first + 1, ptop.second - 1)));
  }
  if(pright != pbot) {
    ans = min(ans, check_point(make_pair(pright.first - 1, pright.second - 1)));
    ans = min(ans, check_point(make_pair(pbot.first + 1, pbot.second + 1)));
  }

  for(ll x : xvals) {
    if(x < pleft.first || x > pright.first) continue;
    auto [l, r] = get_range_y(x);
    ll y = max(l, min(r, yvals[n/2]));
    ans = min(ans, query_x(x) + query_y(y));
  }

  for(ll y : yvals) {
    if(y < pbot.second || y > ptop.second) continue;
    auto [l, r] = get_range_x(y);
    ll x = max(l, min(r, xvals[n/2]));
    ans = min(ans, query_x(x) + query_y(y));
  }

  if(ans >= INFLL) {
    cout << "impossible" << nl;
  } else {
    cout << ans/2 << nl;
  }

  return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m; ll L;
  cin >> n >> m >> L;

  ll cur = 0;
  int dir = 1;
  vector<ll> f(n+2, L);
  vector<tuple<ll,int,ll>> segs;
  for(int i=1; i<=n+1; i++) {
    if(i <= n) cin >> f[i];
    else f[i] = 0;
    ll len = f[i-1] - f[i];
    ll nxt = cur + dir*len;
    segs.emplace_back(min(cur, nxt), 1, 0);
    segs.emplace_back(max(cur, nxt), -1, min(cur, nxt));
    cur = nxt;
    dir *= -1;
  }

  for(int i=0; i<m; i++) {
    ll x;
    cin >> x;
    segs.emplace_back(x, 0, 0);
  }
  segs.emplace_back(INFLL, 0, 0);
  sort(segs.begin(), segs.end());

  ll have = 0;
  __int128 sum = 0;
  int cnt = 0;
  vector<ll> ans;
  for(auto [x, t, other] : segs) {
    //cerr << "@ " << x << " " << t << " " << other << nl;
    if(t == 0) {
      ans.push_back(have + (__int128)x*cnt - sum);
    } else if(t == 1) {
      sum += x;
      cnt++;
    } else {
      sum -= other;
      cnt--;
      have += x - other;
    }
  }

  vector<ll> out;
  adjacent_difference(ans.begin(), ans.end(), back_inserter(out));
  for(ll it : out) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}

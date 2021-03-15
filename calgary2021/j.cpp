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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int query(ll a, ll b) {
  cout << "q " << a << " " << b << endl;
  int res;
  cin >> res;
  return res;
}

ll midpoint(ll a, ll b) {
  return a + (b-a)/2;
}

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

  ll N = ~(1LL<<63);
  map<pair<ll,ll>,int> cnt;
  cnt[pair(0, N)] = query(0, N);

  vector<pair<ll,ll>> cur;
  if(cnt[pair(0, N)]) {
    cur.emplace_back(0, N);
  }

  vector<ll> ans;
  while(!cur.empty()) {
    vector<pair<ll,ll>> nxt;
    for(auto [a, b] : cur) {
      assert(__builtin_popcountll(b - a + 1) == 1);
      if(a == b) {
        ans.push_back(a);
      } else {
        ll m = midpoint(a, b);
        ll left = query(a, m);
        if(left > 0) {
          nxt.emplace_back(a, m);
          cnt[pair(a, m)] = left;
        }
        if(left < cnt[pair(a, b)]) {
          nxt.emplace_back(m+1, b);
          cnt[pair(m+1, b)] = cnt[pair(a, b)] - left;
        }
      }
    }
    cur = move(nxt);
  }

  sort(ans.begin(), ans.end());
  cout << "a " << ans.size();
  for(ll it : ans) {
    cout << " " << it;
  }
  cout << endl;

  return 0;
}

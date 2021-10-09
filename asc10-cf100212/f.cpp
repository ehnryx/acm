//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "magic"

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

const ld PI = acos((ld)-1);

const int N = 1e3 + 1;
pair<ld,int> top[N], mid[N], bot[N];
int ti[N], bi[N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, r, h;
  cin >> n >> r >> h;

  function<ld(ld,ld)> calc = [=](ld a, ld b) {
    ld d = abs(a-b);
    d = min(d, 2*PI - d);
    return hypot(d*r, (ld)h/2);
  };

  for(int i=0; i<n; i++) {
    cin >> top[i].first;
    if(top[i].first < 0) top[i].first += 2*PI;
    top[i].second = i+1;
  }
  for(int i=0; i<n; i++) {
    cin >> mid[i].first;
    if(mid[i].first < 0) mid[i].first += 2*PI;
    mid[i].second = i+1;
  }
  for(int i=0; i<n; i++) {
    cin >> bot[i].first;
    if(bot[i].first < 0) bot[i].first += 2*PI;
    bot[i].second = i+1;
  }
  sort(top, top+n);
  sort(mid, mid+n);
  sort(bot, bot+n);

  int ts = -1;
  ld tval = INFLL;
  for(int s=0; s<n; s++) {
    ld cur = 0;
    for(int i=0; i<n; i++) {
      cur += calc(mid[i].first, top[(s+i)%n].first);
    }
    if(cur < tval) {
      tval = cur;
      ts = s;
    }
  }

  int bs = -1;
  ld bval = INFLL;
  for(int s=0; s<n; s++) {
    ld cur = 0;
    for(int i=0; i<n; i++) {
      cur += calc(mid[i].first, bot[(s+i)%n].first);
    }
    if(cur < bval) {
      bval = cur;
      bs = s;
    }
  }

  for(int i=0; i<n; i++) {
    ti[i] = top[(ts+i)%n].second;
    bi[i] = bot[(bs+i)%n].second;
  }

  cout << tval + bval << nl;
  for(int i=0; i<n; i++) {
    cout << ti[i] << " " << mid[i].second << " " << bi[i] << nl;
  }

  return 0;
}

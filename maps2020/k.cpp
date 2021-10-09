//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ll> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

ll dp(const pt& a, const pt& b) {
  return real(conj(a) * b);
}

int sgn(const ll& v) {
  return v < 0 ? -1 : v <= 0 ? 0 : 1;
}

bool cmp(const pt& a, const pt& b) {
  return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag());
}

bool seg_x_seg(pt a, pt b, pt c, pt d) {
  int s1 = sgn(cp(a-b, a-c)); int s2 = sgn(cp(a-b, a-d));
  int s3 = sgn(cp(c-d, c-a)); int s4 = sgn(cp(c-d, c-b));
  if(!s1 && !s2 && !s3) {
    assert(!s4);
    if(cmp(b, a)) swap(a, b);
    if(cmp(d, c)) swap(c, d);
    return !cmp(d, a) && !cmp(b, c);
  } else {
    return s1*s2 <= 0 && s3*s4 <= 0;
  }
}

bool pt_in_polygon(const pt& v, const vector<pt>& p) {
  int n = p.size();
  ld res = 0;
  for(int j=n-1, i=0; i<n; j=i++) {
    res += atan2(cp(2LL*p[j]-v, 2LL*p[i]-v), dp(2LL*p[j]-v, 2LL*p[i]-v));
  }
  return abs(res) > 1;
}

const int N = 200 + 1;
ll cost[N][N];
ll memo[N][N];

ll solve(int l, int r) {
  if(memo[l][r] != -1) return memo[l][r];
  if(r-l <= 1) return memo[l][r] = 0;
  ll res = INFLL;
  for(int k=l+1; k<=r-1; k++) {
    if(cost[l][k] >= INFLL || cost[k][r] >= INFLL) continue;
    if(solve(l, k) >=  INFLL || solve(k, r) >= INFLL) continue;
    res = min(res, solve(l, k) + solve(k, r) + cost[l][k] + cost[k][r]);
  }
  //cerr<<"@ "<<l<<" "<<r<<nl;
  //cerr<<"go to "<<l+1<<" "<<r<<" w/ cost "<<cost[l+1][r]<<nl;
  //cerr<<"go to "<<l<<" "<<r-1<<" w/ cost "<<cost[l][r-1]<<nl;
  return memo[l][r] = res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.push_back(pt(x, y));
  }

  for(int i=0; i<n; i++) {
    cost[i][i] = 0;
    for(int j=0; j<i; j++) {
      if(i-j == 1 || i-j == n-1) {
        cost[i][j] = cost[j][i] = 0;
        continue;
      }
      ////cerr<<"TRY "<<i<<" "<<j<<nl;
      bool ok = true;
      for(int t=n-1, s=0; s<n; t=s++) {
        if(s == i || s == j || t == i || t == j) continue;
        if(seg_x_seg(p[i], p[j], p[t], p[s])) {
          ok = false;
          break;
        }
      }
      ////cerr<<"has to be ok ? "<<ok<<nl;
      if(ok && pt_in_polygon(p[i]+p[j], p)) {
        ////cerr<<"inside"<<nl;
        cost[i][j] = cost[j][i] = norm(p[i] - p[j]);
      } else {
        ////cerr<<"outside"<<nl;
        cost[i][j] = cost[j][i] = INFLL;
      }
    }
  }

  memset(memo, -1, sizeof memo);
  ll ans = solve(0, n-1);
  assert(ans < INFLL);
  cout << ans << nl;

  return 0;
}

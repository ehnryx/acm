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

int cc_inter(pt p1, ld r1, pt p2, ld r2, pt &i1, pt &i2) {
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2;
  pt c=(p1+p2)*0.5L + (p2-p1)*rq*0.5L/dq;
  ld dt=2.0*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if(dt < -EPS) return 0; else if(dt < EPS) { i1=i2=c; return 1; }
  dt=sqrt(dt)*0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2;
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

  int n;
  cin >> n;
  vector<int> len(n+1), minr(n+1), maxr(n+1);
  for(int i=1; i<=n; i++) {
    cin >> len[i];
    if(len[i] <= minr[i-1]) {
      minr[i] = minr[i-1] - len[i];
    } else if(len[i] <= maxr[i-1]) {
      minr[i] = 0;
    } else {
      minr[i] = len[i] - maxr[i-1];
    }
    maxr[i] = maxr[i-1] + len[i];
  }
  int x, y;
  cin >> x >> y;
  int dist2 = x*x + y*y;

  pt goal(x, y);
  if(dist2 < minr[n]*minr[n]) {
    if(dist2) {
      goal = goal * (minr[n] / sqrt((ld)dist2));
    } else {
      goal = pt(minr[n], 0);
    }
  } else if(dist2 > maxr[n]*maxr[n]) {
    goal = goal * (maxr[n] / sqrt((ld)dist2));
  }

  vector<pt> ans;
  for(int i=n; i>0; i--) {
    ans.push_back(goal);
    ld d = abs(goal);
    pt dir = d < EPS ? pt(1, 0) : goal / d;
    if(d + len[i] <= maxr[i-1]) {
      goal += dir * (ld)len[i];
    } else if(abs(d - len[i]) >= minr[i-1]) {
      goal -= dir * (ld)len[i];
    } else {
      pt i1, i2;
      assert(cc_inter(goal, len[i], 0, maxr[i-1], i1, i2));
      goal = i1;
      assert(goal == goal);
    }
  }

  reverse(begin(ans), end(ans));
  for(const auto& it : ans) {
    cout << real(it) << " " << imag(it) << nl;
  }

  return 0;
}

#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int cc_inter(pt c1, ld r1, pt c2, ld r2, pt& i1, pt& i2) {
  ld len=abs(c1-c2); if(len>r1+r2+EPS || len<abs(r1-r2)-EPS) return 0;
  ld d = len/2+(r1*r1-r2*r2)/(2*len); pt dir = (c2-c1)/len, f = c1+dir*d;
  if(len>r1+r2-EPS || len<abs(r1-r2)+EPS) { i1=i2=f; return 1; }
  ld h=sqrt(r1*r1-d*d); i1=f+dir*pt(0,h); i2=f-dir*pt(0,h); return 2; }

/*
int cc_inter(pt p1, ld r1, pt p2, ld r2, pt &i1, pt &i2) {
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2;
  pt c=(p1+p2)*(ld)0.5 + (p2-p1)*rq*(ld)0.5/dq;
  ld dt=2.0*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if(dt < -EPS) return 0; else if(dt < EPS) { i1=i2=c; return 1; }
  dt=sqrt(dt)*0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2; }
*/

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<ld> r(n);
  vector<pt> c(n);
  vector<bool> ok(n, true);
  vector<vector<pair<ld,int>>> range(n);
  for(int i=0; i<n; i++) {
    range[i].emplace_back(M_PIl+EPS, 1);
    int x, y;
    cin >> x >> y >> r[i];
    c[i] = pt(x, y);
    for(int j=0; j<i; j++) {
      if(!ok[j]) continue;
      pt a, b;
      if(cc_inter(c[j], r[j], c[i], r[i], a, b) == 2) {
        pt rot = (a-c[j]) / (b-c[j]);
        ld dif = arg(rot);
        if(dif < 0) {
          swap(a, b);
          rot = (a-c[j]) / (b-c[j]);
          dif = arg(rot);
        }
        pt mid = c[j] + (b-c[j]) * sqrt(rot);
        ld s, t;
        if(abs(mid - c[i]) < r[i]) {
          s = arg(b - c[j]);
          t = arg(a - c[j]);
        } else {
          s = arg(a - c[j]);
          t = arg(b - c[j]);
        }
        range[j].emplace_back(s, 1);
        range[j].emplace_back(t, -1);
        if(s > t) {
          range[j].emplace_back(-M_PIl-EPS, 1);
          range[j].emplace_back(M_PIl+EPS, -1);
        }
      } else if(abs(c[i] - c[j]) < r[i] && r[i] >= r[j]) {
        ok[j] = false;
      }
    }
  }

  ld ans = 0;
  for(int i=0; i<n; i++) {
    if(!ok[i]) continue;
    sort(range[i].begin(), range[i].end());
    ld cur = -M_PIl;
    int val = 0;
    ld add = 0;
    for(auto [x, t] : range[i]) {
      //cerr << i << " -> " << x << " " << t << nl;
      if(val == 0) {
        add += (x - cur);
      }
      val += t;
      cur = x;
      assert(val >= 0);
    }
    //cerr << "add " << add << " * " << r[i] << nl;
    ans += add * r[i];
  }
  cout << ans << nl;

  return 0;
}

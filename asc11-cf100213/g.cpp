//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "newyear"

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

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }

int cc_inter(pt p1, ld r1, pt p2, ld r2, pt &i1, pt &i2) {
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2;
  pt c=(p1+p2)*0.5L + (p2-p1)*rq*0.5L/dq;
  ld dt=2.0*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if(dt < -EPS) return 0; else if(dt < EPS) { i1=i2=c; return 1; }
  dt=sqrt(dt)*0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2; }

ld get_area(ld i, ld j, ld k) {
  ld s = (ld) (i+j+k) / 2;
  ld area = sqrt((s-i)*(s-j)*(s-k)*s);
  return area;
}

ld get_radius(ld i, ld j, ld k) {
  ld s = (ld) (i+j+k) / 2;
  ld area = sqrt((s-i)*(s-j)*(s-k)*s);
  ld r = area / s;
  return r;
}

int solve(pt,pt,pt);

vector<pt> get_inter(pt A, pt B, pt C) {
  ld len = abs(A-B);
  if(len > 4) {
    return { A + (ld)2 * (B-A) / len, B + (ld)2 * (A-B) / len };
  }
  pt i1, i2;
  assert(cc_inter(A, 2, B, 2, i1, i2));
  assert(cp(B-A, i1-A) > -EPS);
  if(cp(C-B, i1-B) > -EPS && cp(A-C, i1-C) > -EPS && abs(i1-C) >= 2) {
    return {i1};
  } else {
    return {};
  }
}

int other(pt A, pt B, pt C) {
  auto ab = get_inter(A, B, C);
  auto bc = get_inter(B, C, A);
  auto ca = get_inter(C, A, B);
  if(ab.empty() || bc.empty() || ca.empty()) return 0;
  //cerr << "get intersects of : " << A << " " << B << " " << C << nl;
  //for(auto v : ab) { cerr << v << " "; } cerr << nl;
  //for(auto v : bc) { cerr << v << " "; } cerr << nl;
  //for(auto v : ca) { cerr << v << " "; } cerr << nl;
  //cerr << nl;
  int best = 0;
  for(auto AA : ab) {
    for(auto BB : bc) {
      for(auto CC : ca) {
        best = max(best, solve(AA, BB, CC));
      }
    }
  }
  return best;
}

int solve(pt A, pt B, pt C) {
  if(cp(B-A, C-A) < EPS || cp(C-B, A-B) < EPS || cp(A-C, B-C) < EPS) return 0;
  //cerr << "SOLVE " << A << " " << B << " " << C << nl;
  int cnt = (abs(A-B)>=2-EPS) + (abs(B-C)>=2-EPS) + (abs(C-A)>=2-EPS);
  if(cnt == 0) return 1;
  else if(cnt < 3) return 2;
  else return 3 + other(A, B, C);
}

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

  vector<tuple<int,int,int>> ans[11];
  for(int i=3; i<=10; i++) {
    for(int j=3; j<=i; j++) {
      for(int k=3; k<=j; k++) {
        if(j+k <= i) continue;
        ld r = get_radius(i, j, k);
        if(r < 1-EPS) continue;

        //cerr << "ENTER @ " << i << " " << j << " " << k << nl;

        ld h = get_area(i, j, k) * 2 / i;
        pt A(0, 0);
        pt B(i, 0);
        pt C(sqrt(j*j-h*h), h);
        assert(abs(abs(A-B)-i) < EPS);
        assert(abs(abs(B-C)-k) < EPS);
        assert(abs(abs(C-A)-j) < EPS);

        pt dC = (B-A)/abs(B-A) * pt(0,1);
        pt dA = (C-B)/abs(C-B) * pt(0,1);
        pt dB = (A-C)/abs(A-C) * pt(0,1);
        pt AA = line_inter(A+dC, B+dC, A+dB, C+dB);
        pt BB = line_inter(B+dA, C+dA, B+dC, A+dC);
        pt CC = line_inter(C+dB, A+dB, C+dA, B+dA);

        int cnt = solve(AA, BB, CC);
        //cerr << "cnt : " << cnt << nl;
        //cerr << nl;

        assert(cnt <= 10);
        ans[cnt].emplace_back(i, j, k);
      }
    }
  }

#ifndef ONLINE_JUDGE
  for(int i=0; i<=10; i++) {
    cout << i << " -> " << ans[i].size() << nl;
    for(auto [a, b, c] : ans[i]) {
      cout << a << " " << b << " " << c << " -> " << get_radius(a, b, c) << " " << get_area(a, b, c) << nl;
    }
    cout << nl;
  }
  cout << nl;
#endif

  ans[10].emplace_back(10, 10, 10); // OK
  ans[8].emplace_back(10, 10, 9); // OK
  ans[8].emplace_back(10, 9, 9); // OK
  ans[7].emplace_back(10, 10, 8); // OK
  ans[7].emplace_back(9, 9, 9); // OK
  ans[7].emplace_back(10, 9, 8); // :paul:

  int n, a, b, c;
  cin >> n >> a >> b >> c;
  if(a < b) swap(a, b);
  if(a < c) swap(a, c);
  if(b < c) swap(b, c);
  tuple<int,int,int> tri(a, b, c);

  int best = 0;
  for(int i=1; i<=10; i++) {
    if(find(ans[i].begin(), ans[i].end(), tri) != ans[i].end()) {
      best = i;
    }
  }

  cout << min(n, best) << nl;

  return 0;
}

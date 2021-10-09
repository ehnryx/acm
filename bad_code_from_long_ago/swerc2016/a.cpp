#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-5;

#define pt complex<ldouble>
ostream& operator << (ostream& os, const pii& p) {
  os << "[" << p.first << "," << p.second << "]";
  return os;
}

////////////////////////////////////////////////////////////////////////////////
// Circle-circle intersection (TESTED UVa 453)
////////////////////////////////////////////////////////////////////////////////
// Return number of intersections. Circles must not be identical.
int cc_inter(pt p1, ld r1, pt p2, ld r2, pt &i1, pt &i2) {
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2; pt c=(p1+p2)*0.5L + (p2-p1)*rq*0.5L/dq;
  ld dt=2.0*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if(dt < -EPS) return 0; if(dt < EPS) { i1=i2=c; return 1; }
  dt=sqrt(dt)*0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2; }

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  int arm[n+1];
  for (int i = 0; i < n; i++) {
    cin >> arm[i];
  }
  pt goal;
  ldouble x, y;
  cin >> x >> y;
  goal = pt(x,y);

  pair<ldouble,ldouble> ring[n+1];
  ring[0] = pdd(0,0);
  for (int i = 1; i <= n; i++) {
    if (arm[i-1] > ring[i-1].second)
      ring[i].first = arm[i-1] - ring[i-1].second;
    else if (arm[i-1] < ring[i-1].first)
      ring[i].first = ring[i-1].first - arm[i-1];
    else
      ring[i].first = 0;
    ring[i].second = ring[i-1].second + arm[i-1];
  }

  vector<pt> ans(n);
  ldouble len = abs(goal);
  if (len < ring[n].first) {
    // inside
    if (len <= EPS) {
      goal = pt(0.5,0);
      len = 0.5;
    }
    goal *= (ring[n].first/len);
  } 
  else if (len > ring[n].second) {
    // outside
    goal *= (ring[n].second/len);
  }

  pt i1, i2;
  for (int i = n-1; i >= 0; i--) {
    ans[i] = goal;
    len = abs(goal);
    if (len < EPS)
      goal = pt(arm[i], 0);
    else if (cc_inter(goal, arm[i], pt(0,0), ring[i].first, i1, i2))
      goal = i1;
    else if (cc_inter(goal, arm[i], pt(0,0), ring[i].second, i1, i2))
      goal = i1;
    else if (len > ring[i].second)
      goal *= ((len - arm[i]) / len);
    else
      goal *= ((len + arm[i]) / len);
  }

  // output answer
  for (int i = 0; i < n; i++) {
    cout << real(ans[i]) << " " << imag(ans[i]) << nl;
  }

  return 0;
}

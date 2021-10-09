#include <bits/stdc++.h>
using namespace std;
//#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble double
typedef double ld;
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ld EPS = 1e-8;
const ld PI = 3.1415926535897932384626;

typedef complex<ldouble> pt;
typedef vector<pt> pol;
ld cp(const pt &a, const pt &b) {return imag(conj(a)*b);}
ld dp(const pt &a, const pt &b) {return real(conj(a)*b);}
bool cmp_lex(const pt &a, const pt &b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
pt base; bool cmp_base(const pt &a, const pt &b) {return cp(a-base, b-base) > 0.0 || cp(a-base, b-base) == 0 && abs(a-base) < abs(b-base);}
void prep_graham(pol& p) {
  sort(p.begin(), p.end(), cmp_lex); p.push_back(base = p[0]);
  sort(p.begin()+1, p.end()-1, cmp_base);
}
pol graham(pol p) { pol hull; prep_graham(p);
  for (int i = 0; i < p.size()-1;) {hull.push_back(p[i++]);
    while (hull.size() > 1 && cp(hull.back() - hull[hull.size()-2], p[i] - hull.back()) <= 0) hull.pop_back();
  } return hull; }
inline void perturb(const pt &a, pol &pts) {
  pts.push_back(a);
//  pts.push_back(a+pt(1e-10, 1e-10));
//  pts.push_back(a+pt(1e-10, -1e-10));
//  pts.push_back(a-pt(1e-10, 1e-10));
//  pts.push_back(a-pt(1e-10, -1e-10));
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n; cin >> n;
  string s; cin >> s;
  pol pts;
  for (int i = 0; i < s.size(); i++) {
    switch (s[i]) {
      case 'T': perturb(pt(i, 0), pts);
            perturb(pt(i+1, 0), pts);
            perturb(pt((2*i+1)/2.0, sqrt(3) / 2), pts);
            break;
      case 'S': perturb(pt(i, 0), pts);
            perturb(pt(i+1, 0), pts);
            perturb(pt(i+1, 1), pts);
            perturb(pt(i, 1), pts);
            break;
      case 'C': for (int j = 0; j < 20000; j++) {
            pts.push_back(pt((2*i+1)/2.0, 0.5) + 0.5*exp(pt(0, 2 * PI * j / 20000)));
            }
            break;
    }
  }
  pol chull = graham(pts);
  ld ans = 0;
  for (int i = 0; i < chull.size()-1; i++)
    ans += abs(chull[i] - chull[i+1]);
  ans += abs(chull.back() - chull[0]);
  cout << fixed << setprecision(10) << ans << endl;

  return 0;
}

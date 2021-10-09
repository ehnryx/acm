#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

pt solve(int n, int m) {
  if (n == 1) return pt(1,1);

  int quarter = n*n/4;
  if (m <= quarter) {
    pt res = solve(n/2, m);
    res = pt(n/2-res.real()+1, res.imag())*pt(0,-1) + pt(0,n/2+1);
    return res;
  }
  else if (m <= 2*quarter) {
    pt res = solve(n/2, m-quarter);
    return res + pt(0,n/2);
  }
  else if (m <= 3*quarter) {
    pt res = solve(n/2, m-2*quarter);
    return res + pt(n/2,n/2);
  }
  else {
    pt res = solve(n/2, m-3*quarter);
    res = pt(n/2-res.real()+1, res.imag())*pt(0,1) + pt(n/2+1,0);
    return res + pt(n/2,0);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  pt ans = solve(n, m);
  cout << llround(ans.real()) << " " << llround(ans.imag()) << nl;

  return 0;
}

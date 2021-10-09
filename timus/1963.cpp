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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  const int n = 4;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.push_back(pt(x, y));
  }

  int ans = 0;
  for(int j=n-1, i=0; i<n; j=i++) {
    int k = (i+2) % n;
    pt dir = (p[i]-p[k]) * pt(0,1);
    pt mid = (p[i]+p[j]) / (ld)2;
    pt perp = (p[i]-p[j]) * pt(0,1);
    bool ok = true;
    bool ko = true;
    for(int t=0; t<n; t++) {
      {
        pt it = line_inter(p[i], p[k], p[t], p[t] + dir);
        pt ref = (ld)2*it - p[t];
        bool good = false;
        for(int w=0; w<n; w++) {
          good |= (abs(ref-p[w]) < EPS);
        }
        ok &= good;
      }
      {
        pt it = line_inter(mid, mid+perp, p[t], p[t] + p[i]-p[j]);
        pt ref = (ld)2*it - p[t];
        bool good = false;
        for(int w=0; w<n; w++) {
          good |= (abs(ref-p[w]) < EPS);
        }
        ko &= good;
      }
    }
    ans += ok;
    ans += ko;
  }
  cout << ans << nl;

  return 0;
}

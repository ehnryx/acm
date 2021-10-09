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

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  ld lower, upper;
  lower = 0;
  upper = 1;

  int a[n], b[n];
  for (int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
    if (a[i] < b[i]) swap(a[i], b[i]);
    if (i > 0) {
      if (a[i] == a[i-1] && b[i] == b[i-1]) continue;
      if (a[i] == a[i-1] && b[i] > b[i-1]) lower = 1;
      if (a[i] > a[i-1] && b[i] == b[i-1]) upper = 0;
      if (a[i] > a[i-1] && b[i] > b[i-1]) lower = INF;
    }
  }

  for (int i=1; i<n; i++) {
    if (a[i]-b[i] == a[i-1]-b[i-1]) continue;

    ld yval = line_inter(pt(i,a[i]), pt(i-1,a[i-1]), pt(i,b[i]), pt(i-1,b[i-1])).imag();
    if (a[i]-b[i] > a[i-1]-b[i-1]) {
      upper = min(upper, (yval-b[i])/(a[i]-b[i]));
    } else {
      lower = max(lower, (yval-b[i-1])/(a[i-1]-b[i-1]));
    }
  }

  if (lower < upper+EPS) cout << "YES" << nl;
  else cout << "NO" << nl;

  return 0;
}

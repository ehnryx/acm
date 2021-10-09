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
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
bool pt_in_polygon(const pt &p, const pol &v) {
  ld res = 0; for(int i = v.size() - 1, j = 0; j < v.size(); i = j++)
    res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p));
  return abs(res) > 1;
}

vector<pt> p;
ld get(int n, bool t) {
  ld left = 0;
  ld right = 1e7;
  while (right-left > EPS) {
    ld mid = (left+right)/2;
    vector<pt> b;
    for (int i=0; i<n; i++) {
      b.push_back(mid*exp(pt(0,2*M_PIl*i/n)));
    }
    bool ok = true;
    for (const pt& it : p) {
      if (pt_in_polygon(it,b) != t) {
        ok = false; break;
      }
    }
    if (ok) {
      (t ? right : left) = mid;
    } else {
      (t ? left : right) = mid;
    }
  }
  return (left+right)/2;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, x, y;
  cin >> n;

  for (int i=0; i<n; i++) {
    cin >> x >> y;
    p.push_back(pt(x,y));
  }

  ld best = -1;
  int ans = -1;

  for (int k=3; k<=8; k++) {
    ld in = get(k,false);
    ld out = get(k,true);
    ld cur = (in/out)*(in/out);
    if (cur > best) {
      best = cur;
      ans = k;
    }
  }

  cout << ans << " " << best << nl;

  return 0;
}

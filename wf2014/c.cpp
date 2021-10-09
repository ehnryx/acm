#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long long ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const ll INF = 1e18L;
const ld EPS = 1e-14;

struct Frac {
  ll n, d;
  Frac(ll a, ll b) {
    ll g = abs(__gcd(a,b));
    a /= g; b /= g;
    if (b < 0) { a=-a; b=-b; }
    n = a; d = b;
  }
  bool operator < (const Frac& o) const {
    return n*o.d < d*o.n;
  }
  ll floor() const {
    return n/d;
  }
  ll ceil() const {
    return (n+d-1)/d;
  }
};

ostream& operator << (ostream& os, const Frac& v) {
  return os << v.n << "/" << v.d;
}

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

ld sgn(const ld& x) { return x<0 ? -1 : 1; }

ll area(const pol& v) {
  ld s=0; int n=v.size();
  for (int i=n-1,j=0; j<n; i=j++) s += cp(v[i],v[j]);
  return llround(s);
}

ll centroid(const pol& v) {
  pt res; ld A=0; int n=v.size();
  for (int i=n-1,j=0; j<n; i=j++) {
    A += cp(v[i],v[j]);
    res += (v[i]+v[j])*cp(v[i],v[j]);
  }
  return llround(res.real()*sgn(A));
}

Frac solve(ll x, const pol& p) {
  ll v = llround(p[0].real());
  ll a = abs(area(p));
  ll g = centroid(p);
  return Frac(3*a*x-g, 6*(v-x));
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(0);
  cerr << fixed << setprecision(17);

  int n;
  cin >> n;

  ld minv = INF;
  ld maxv = -INF;

  pol p;
  for (int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    p.push_back(pt(a,b));
    if (b == 0) {
      minv = min(minv, (ld)a);
      maxv = max(maxv, (ld)a);
    }
  }

  if (area(p) < 0) {
    reverse(p.begin(), p.end());
    auto move = p.back();
    p.pop_back();
    p.insert(p.begin(), move);
  }

  if (p[0].real() <= minv) {
    minv = -minv;
    maxv = -maxv;
    for (int i=0; i<n; i++) {
      p[i] = pt(-p[i].real(), p[i].imag());
    }
  }

  Frac left = solve(minv, p);
  Frac right = solve(maxv, p);
  if (right < left) swap(left,right);
  cerr << left << " " << right << nl;
  if (right < Frac(0,1)) {
    cout << "unstable" << nl;
  } else if (right.d == 0) {
    cout << max((ll)0,left.floor()) << " .. " << "inf" << nl;
  } else {
    cout << max((ll)0,left.floor()) << " .. " << right.ceil() << nl;
  }

  return 0;
}

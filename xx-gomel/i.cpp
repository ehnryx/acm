#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'

const int INF = 0x3f3f3f3f;

using pt = complex<ll>;
using pol = vector<pt>;

ll cp(const pt& a, const pt& b) {
  return imag(conj(a)*b);
}

bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag() < b.imag() || (a.imag() == b.imag() && a.real() < b.real());
}

pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1;
  pol ch(2*p.size());
  for(int i=0, d=1; i<p.size() && i>=0; i+=d) {
    while(top>bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) < 0) top--;
    ch[top++] = p[i]; if(i == p.size()-1) d=-1, bot=top;
  } ch.resize(max(1, top-1));
  return ch;
}

ll area(const pol& v) {
  ll s = 0; int n = v.size();
  for(int i=n-1, j=0; j<n; i=j++) {
    s += cp(v[i], v[j]);
  }
  return abs(s);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<pt> p;
    for(int i=0; i<n; i++) {
      int x, y;
      cin >> x >> y;
      p.push_back(pt(x,y));
    }
    vector<pt> h = chull(p);
    ll A = area(h);
    if(A == 0) {
      if(n == 1) {
        cout << 1 << nl;
      } else {
        ll minx, miny, maxx, maxy;
        minx = miny = INF;
        maxx = maxy = -INF;
        for(const pt& it : p) {
          minx = min(minx, it.real());
          maxx = max(maxx, it.real());
          miny = min(miny, it.imag());
          maxy = max(maxy, it.imag());
        }
        ll g = abs(__gcd(minx-maxx, miny-maxy));
        if(n == g+1) {
          cout << 1 << nl;
        } else {
          cout << 0 << nl;
        }
      }
    } else {
      int m = h.size();
      if(2*(n-m) + m - 2 == A) {
        cout << 1 << nl;
      } else {
        cout << 0 << nl;
      }
    }
  }

  return 0;
}

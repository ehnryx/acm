//#pragma GCC optimize("O3")
//#pragma GCC optimize("fast-math")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "wall"

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

const ld PI = acos((ld)-1);

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag() < b.imag() - EPS || (a.imag() <= b.imag() + EPS && a.real() < b.real() - EPS);
}

vector<pt> chull(vector<pt> p) {
  sort(p.begin(), p.end(), cmp_lex_i);
  int top = 0, bot = 1, n = p.size();
  vector<pt> ch(2*n);
  for(int i=0, d=1; i<n && i>=0; i+=d) {
    while(top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i];
    if(i == n-1) d = -1, bot = top;
  }
  ch.resize(max(1, top-1));
  return ch;
}

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

bool valid(const vector<pt>& v, const pt& p, const ld& ang) {
  const pt dir = exp(pt(0, ang));
  for(const pt& it : v) {
    if(cp(dir, it-p) < -EPS) {
      return false;
    }
  }
  return true;
}

ld get_area(const pt& it, const pt& a, const pt& b, const pt& c, const ld& ang) {
  const pt dir = exp(pt(0, ang));
  const pt ac = line_inter(it, a, c, c+dir);
  const pt bc = line_inter(it, b, c, c+dir);
  ld res = cp(ac-it, bc-it);
  return abs(res) / 2;
}

vector<pt> get_triangle(const pt& it, const pt& a, const pt& b, const pt& c, const ld& ang) {
  const pt dir = exp(pt(0, ang));
  const pt ac = line_inter(it, a, c, c+dir);
  const pt bc = line_inter(it, b, c, c+dir);
  return {it, ac, bc};
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  int n;
  cin >> n;
  vector<pt> v;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    v.emplace_back(x, y);
  }
  v = chull(v);
  n = v.size();

  ld best = INFLL;
  vector<pt> ans;

  for(int i=0; i<n; i++) {
    int ni = (i+1) % n;
    for(int j=0; j<i; j++) {
      int nj = (j+1) % n;
      pt it = line_inter(v[i], v[ni], v[j], v[nj]);
      if(abs(it) > INFLL) continue; // fails -ffast-math

      int s = i;
      int t = j;
      if(abs(v[t]-it) < EPS || cp(v[s]-it, v[t]-it) < 0) swap(s, t);
      int ns = (s+1) % n;

      for(int k=t; k!=s; k=(k+n-1)%n) {
        int nk = (k+1) % n;
        int pk = (k+n-1) % n;

        ld l = cp(v[t] - it, v[k] - v[pk]) > 0 ? arg(v[k] - v[pk]) : arg(v[t] - it);
        ld r = cp(v[ns] - it, v[nk] - v[k]) > 0 ? arg(v[nk] - v[k]) : arg(it - v[ns]);
        if(l > r + EPS) r += 2*PI;
        if(!valid(v, v[k], (l+r)/2)) continue;

        while(r-l > EPS) {
          ld lm = (9*l + 8*r) / 17;
          ld rm = (8*l + 9*r) / 17;
          ld larea = get_area(it, v[ns], v[t], v[k], lm);
          ld rarea = get_area(it, v[ns], v[t], v[k], rm);
          if(larea < rarea) {
            r = rm;
          } else {
            l = lm;
          }
        }

        ld cur = get_area(it, v[ns], v[t], v[k], (l+r)/2);
        if(cur < best) {
          best = cur;
          ans = get_triangle(it, v[ns], v[t], v[k], (l+r)/2);
        }
      }
    }
  }

  for(const auto& p : ans) {
    cout << p.real() << " " << p.imag() << nl;
  }

  return 0;
}

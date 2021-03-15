#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
//#pragma GCC optimize("cx-limited-range")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-7L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << "( " << v.first << " , " << v.second << " )";
}

constexpr ld PI = M_PIl;

int sgn(ld x) {
  return x < -EPS ? -1 : x > EPS ? 1 : 0;
}

ld cp(const pt& a, const pt& b) { return real(a)*imag(b) - real(b)*imag(a); }
ld dp(const pt& a, const pt& b) { return real(a)*real(b) + imag(a)*imag(b); }
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

int solve(ld L, const pt& a, const pt& b, const vector<vector<pt>>& rects) {
  if(abs(a - b) < EPS || abs(a - b) > L + EPS) return 0;

  vector<ld> ev;
  int base = 0;
  for(const auto& r : rects) {
    bool match = false;
    for(const auto& v : r) {
      match |= (abs(v - a) < EPS || abs(v - b) < EPS);
    }
    if(match) {
      base++;
      continue;
    }

    int s = 0;
    ld dist = INF;
    for(int i=3, j=0; j<4; i=j++) {
      int s1 = sgn(cp(b - a, r[i] - a) / abs(a - b));
      int s2 = sgn(cp(b - a, r[j] - a) / abs(a - b));
      if(s1 * s2 <= 0 && abs(s1) + abs(s2)) {
        pt it = line_inter(a, b, r[i], r[j]);
        dist = min(dist, abs(it - a));
        if(s) assert(s == sgn(dp(b-a, it-a)));
        s = sgn(dp(b - a, it - a));
      }
    }
    if(s) {
      ev.push_back(s * dist);
    }
  }
  sort(ev.begin(), ev.end());

  int ans = base;
  for(int i=0; i<ev.size(); i++) {
    for(int j=0; j<=i; j++) {
      ld neg = min((ld)0, ev[j]);
      ld pos = max(abs(a - b), ev[i]);
      if(pos - neg <= L + EPS) {
        ans = max(ans, base + i - j + 1);
      }
    }
  }

  return ans;
}

ld length(const ld& x, const pt& a, const pt& b, const pt& c) {
  if(abs(a.real() - b.real()) < EPS) {
    return (a.real() - c.real()) / cos(x);
  } else {
    return (a.imag() - c.imag()) / sin(x);
  }
}

ld calc(const ld& x, const pair<pt,pt>& u, const pair<pt,pt>& v, const pt& c) {
  return abs(length(x, u.first, u.second, c)) + abs(length(x, v.first, v.second, c));
}

void fix(ld& s, ld& t) {
  if(s > t) {
    s -= 2*PI;
  }
  while(s < 0) {
    s += 2*PI;
    t += 2*PI;
  }
}

pair<pt,pt> search(ld l, ld r, ld L, const pair<pt,pt>& u, const pair<pt,pt>& v, const pt& pivot) {
  for(int bs=0; bs<42; bs++) {
    ld m = (l + r) / 2;
    if(calc(m, u, v, pivot) < L) {
      l = m;
    } else {
      r = m;
    }
  }

  if(abs(calc(r, u, v, pivot) - L) > EPS) {
    return pair(pivot, pivot);
  } else {
    return pair(pivot, pivot + exp(pt(0, r)));
  }
}

vector<pair<pt,pt>> find_line(ld L, const pt& pivot, const pair<pt,pt>& u, const pair<pt,pt>& v) {
  ld us = arg(u.first - pivot);
  ld ut = arg(u.second - pivot);
  ld vs = arg(v.first - pivot);
  ld vt = arg(v.second - pivot);
  vs = (vs < 0 ? vs + PI : vs - PI);
  vt = (vt < 0 ? vt + PI : vt - PI);
  fix(us, ut);
  fix(vs, vt);

  ld l = max(us, vs);
  ld r = min(ut, vt);
  if(l > r) {
    return {};
  }

  for(int bs=0; bs<42; bs++) {
    ld lm = (5*l + 4*r) / 9;
    ld rm = (4*l + 5*r) / 9;
    ld lval = calc(lm, u, v, pivot);
    ld rval = calc(rm, u, v, pivot);
    if(lval < rval) {
      r = rm;
    } else {
      l = lm;
    }
  }

  ld m = (l + r) / 2;
  l = max(us, vs);
  r = min(ut, vt);

  vector<pair<pt,pt>> out = {
    search(m, l, L, u, v, pivot),
    search(m, r, L, u, v, pivot),
  };
  return out;
}

pt find_perp(const pt& a, const pair<pt,pt>& m) {
  auto [u, v] = m;
  if(abs(u.real() - v.real()) < EPS) {
    ld s = min(u.imag(), v.imag());
    ld t = max(u.imag(), v.imag());
    if(s <= a.imag() && a.imag() <= t) {
      return pt(u.real(), a.imag());
    }
  } else {
    ld s = min(u.real(), v.real());
    ld t = max(u.real(), v.real());
    if(s <= a.real() && a.real() <= t) {
      return pt(a.real(), u.imag());
    }
  }
  return a;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, L;
  cin >> n >> L;
  vector<vector<pt>> rects;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    vector<pt> cur;
    cur.emplace_back(a, b);
    cur.emplace_back(x, b);
    cur.emplace_back(x, y);
    cur.emplace_back(a, y);
    rects.push_back(move(cur));
  }

  int ans = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<=i; j++) {
      for(const auto& a : rects[i]) {
        for(const auto& b : rects[j]) {
          ans = max(ans, solve(L, a, b, rects));
        }
      }
    }
  }
  for(const auto& r : rects) {
    for(const auto& pivot : r) {
      vector<pair<pt,pt>> segs;
      for(const auto& o : rects) {
        for(int j=3, k=0; k<4; j=k++) {
          if(sgn(cp(pivot - o[j], o[k] - o[j])) <= 0) continue;
          segs.emplace_back(o[k], o[j]);
        }
      }
      for(int i=0; i<segs.size(); i++) {
        ans = max(ans, solve(L, pivot, find_perp(pivot, segs[i]), rects));
        for(int j=0; j<i; j++) {
          for(auto [a, b] : find_line(L, pivot, segs[i], segs[j])) {
            ans = max(ans, solve(L, a, b, rects));
          }
        }
      }
    }
  }
  cout << ans << nl;

  return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-11L;
random_device _rd; mt19937 rng(_rd());

namespace std {
  bool operator < (const pt& a, const pt& b) {
    return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag());
  }
}

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

ld dp(const pt& a, const pt& b) {
  return real(conj(a) * b);
}

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

struct Line {
	mutable ld m, b, p;
	bool operator<(const Line& o) const { return m < o.m; }
	bool operator<(ld x) const { return p < x; }
  tuple<ld,ld,ld> tup() const { return make_tuple(m, b, p); }
};

struct LineContainer : multiset<Line, less<>> {
	const ld inf = (ld)1/(ld)0;
	ld div(ld a, ld b) { return a / b; }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
		else x->p = div(y->b - x->b, x->m - y->m);
		return x->p >= y->p;
	}
	void add(ld m, ld b) {
		auto z = insert({m, b, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ld query(ld x) {
		auto l = *lower_bound(x);
		return l.m * x + l.b;
	}
};

ld area(vector<pair<pt,pt>> lines) {
  static const pt rot = polar((ld)1, (ld)1.789);
  for(auto& [a, b] : lines) {
    a *= rot;
    b *= rot;
  }

  LineContainer lower, upper;
  for(auto [a, v] : lines) {
    ld m = (a.imag() - v.imag()) / (a.real() - v.real());
    ld b = a.imag() - a.real() * m;
    if(a.real() < v.real()) {
      lower.add(m, b);
    } else {
      upper.add(-m, -b);
    }
  }

  static const ld big = 1e5;

  ld l = -big;
  ld r = big;
  for(int bs=0; bs<99; bs++) {
    ld lm = (5*l + 4*r) / 9;
    ld rm = (5*r + 4*l) / 9;
    if(-upper.query(lm) - lower.query(lm) > -upper.query(rm) - lower.query(rm)) {
      r = rm;
    } else {
      l = lm;
    }
  }
  ld mid = (l+r)/2;

  l = -big;
  r = mid;
  for(int bs=0; bs<99; bs++) {
    ld m = (l+r) / 2;
    if(-upper.query(m) - lower.query(m) > 0) {
      r = m;
    } else {
      l = m;
    }
  }
  ld left = r;

  l = mid;
  r = big;
  for(int bs=0; bs<99; bs++) {
    ld m = (l+r) / 2;
    if(-upper.query(m) - lower.query(m) > 0) {
      l = m;
    } else {
      r = m;
    }
  }
  ld right = l;

  ld m, b, _;
  vector<pt> v;
  v.push_back(pt(left, lower.query(left)));
  for(auto it = next(lower.begin()); it != lower.end(); it++) {
    tie(m, b, _) = prev(it)->tup();
    pt add = line_inter(pt(0, it->b), pt(1, it->m + it->b), pt(0, b), pt(1, m + b));
    if(left <= add.real() && add.real() <= right) {
      v.push_back(add);
    }
  }
  v.push_back(pt(right, lower.query(right)));

  vector<pt> top;
  for(auto it = next(upper.begin()); it != upper.end(); it++) {
    tie(m, b, _) = prev(it)->tup();
    pt add = line_inter(pt(0, -it->b), pt(1, -it->m + -it->b), pt(0, -b), pt(1, -m + -b));
    if(left <= add.real() && add.real() <= right) {
      top.push_back(add);
    }
  }
  reverse(begin(top), end(top));
  v.insert(end(v), begin(top), end(top));

  ld res = 0;
  for(int i=(int)v.size()-1, j=0; j<v.size(); i=j++) {
    res += cp(v[i], v[j]);
  }
  assert(res == res);
  return res / 2;
}

void solve() {
  int nn, mm, n, m;
  cin >> nn >> mm >> n >> m;
  n -= nn;
  m -= mm;

  int a, b, x, y;
  cin >> a >> b >> x >> y;
  pt A(a-nn, b-mm), B(x-nn, y-mm);
  cin >> a >> b >> x >> y;
  pt C(a-nn, b-mm), D(x-nn, y-mm);

  //cerr << n << " " << m << " " << A << " " << B << " " << C << " " << D << nl;

  if(cp(A-B, C-D) == 0) {
    if(cp(A-B, C-B) != 0) {
      cout << 0 << nl;
      return; // disjoint
    }
    if(B < A) swap(A, B);
    if(D < C) swap(C, D);
    pt L = max(A, C);
    pt R = min(B, D);
    if(R < L || R == L) {
      cout << 0 << nl;
      return;
    }

    pt dir = R - L;
    vector<pair<pt,pt>> env;
    if (A != C) env.emplace_back(L, L + dir * pt(0, -1));
    if (B != D) env.emplace_back(R, R + dir * pt(0, 1));
    env.emplace_back(pt(0, 0), pt(n, 0));
    env.emplace_back(pt(n, 0), pt(n, m));
    env.emplace_back(pt(n, m), pt(0, m));
    env.emplace_back(pt(0, m), pt(0, 0));
    cout << area(env) << nl;
    return;
  }

  if (A == C) {
  } else if(A == D) {
    swap(C, D);
  } else if(B == C) {
    swap(A, B);
  } else if(B == D) {
    swap(A, B);
    swap(C, D);
  } else {
    cout << 0 << nl;
    return;
  }

  if(cp(B-A, D-A) < 0) swap(B, D);
  vector<pair<pt,pt>> env = { { A, A + (D-A) * pt(0, 1) }, { A, A + (B-A) * pt(0, 1) } };
  env.emplace_back(pt(0, 0), pt(n, 0));
  env.emplace_back(pt(n, 0), pt(n, m));
  env.emplace_back(pt(n, m), pt(0, m));
  env.emplace_back(pt(0, m), pt(0, 0));
  cout << area(env) << nl;
  return;
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

  int T;
  cin >> T;
  while(T--) {
    solve();
  }

  return 0;
}

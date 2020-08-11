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
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS
    ||  (a.imag()<=b.imag()+EPS && a.real()<b.real()-EPS); }

pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1;
  pol ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top>bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2])<=0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch;
}

ld lp_dist(const pt &a, const pt &b, const pt &p) {
  return cp(b - a, p - a) / abs(b - a);
}

pt circumcenter(const pt& a, const pt& b, const pt& c) {
	ld A = abs(b-c);
	ld B = abs(c-a);
	ld C = abs(a-b);
	ld fa = A*A * (B*B + C*C - A*A);
	ld fb = B*B * (C*C + A*A - B*B);
	ld fc = C*C * (A*A + B*B - C*C);
	return (fa*a + fb*b + fc*c) / (fa+fb+fc);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(0);

	int n;
	cin >> n;
	vector<pt> p;
	for(int i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;
		p.push_back(pt(x, y));
	}
	vector<pt> h = chull(p);
	pt a = h[0], b = h[1];

	vector<pair<ld,int>> order;
	for(int i=0; i<n; i++) {
		if(abs(p[i]-a) < EPS || abs(p[i]-b) < EPS) continue;
		pt c = circumcenter(a, b, p[i]);
		ld d = lp_dist(a, b, c);
		order.push_back(make_pair(d, i));
	}
	sort(order.begin(), order.end());

	pt s = p[order[order.size()/2].second];
	cout << a.real() << " " << a.imag() << nl;
	cout << b.real() << " " << b.imag() << nl;
	cout << s.real() << " " << s.imag() << nl;

	return 0;
}

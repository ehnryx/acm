#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }

inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}

pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch;
} // pts returned in ccw order.

// Does NOT include points on the ends of the segment.
inline bool on_segment(const pt &a, const pt &b, const pt &p) {
  return abs(cp(b-a, p-a)) < EPS && dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0; }

// Checks if p lies on the boundary of a polygon v.
inline bool on_boundary(const pol &v, const pt &p) { bool res = false;
  for(int i=v.size()-1,j=0;j<v.size();i=j++)
    res |= on_segment(v[i], v[j], p) | (abs(p-v[i]) < EPS); return res; }

bool pt_in_poly(const pt& p, const vector<pt>& v) {
	if (on_boundary(v, p)) return false;
	int n = v.size();
	ld res = 0;
	for (int i=n-1,j=0; j<n; i=j++) {
		res += atan2(cp(v[i]-p, v[j]-p), dp(v[i]-p, v[j]-p));
	}
	return abs(res) > 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	for (int tt=1; tt<=T; tt++) {
		if (tt > 1) cout << nl;

		int n, m;
		cin >> n >> m;
		vector<pt> p;
		for (int i=0; i<n; i++) {
			int x, y;
			cin >> x >> y;
			p.push_back(pt(x,y));
		}
		p = chull(p);

		cout << "Case " << tt << nl;

		int first = 0;
		n = p.size();
		for (int i=0; i<n; i++) {
			if (llround(p[i].real()) < llround(p[first].real())) {
				first = i;
			} else if (llround(p[i].real()) == llround(p[first].real())) {
				if (llround(p[i].imag()) < llround(p[first].imag())) {
					first = i;
				}
			}
		}
		for (int i=0; i<=n; i++) {
			cout << llround(p[(i+first)%n].real()) << " " << llround(p[(i+first)%n].imag()) << nl;
		}

		for (int i=0; i<m; i++) {
			int x, y;
			cin >> x >> y;
			cout << x << " " << y << " is ";
			if (pt_in_poly(pt(x,y), p)) {
				cout << "unsafe!" << nl;
			} else {
				cout << "safe!" << nl;
			}
		}
	}

	return 0;
}


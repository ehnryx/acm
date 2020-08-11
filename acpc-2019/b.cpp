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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
//typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T> struct cplx {
  T x, y; cplx() {x = 0.0; y = 0.0;}
  cplx(T nx, T ny=0) {x = nx; y = ny;}
  cplx operator+(const cplx &c) const {return {x + c.x, y + c.y};}
  cplx operator-(const cplx &c) const {return {x - c.x, y - c.y};}
  cplx operator*(const cplx &c) const {return {x*c.x - y*c.y, x*c.y + y*c.x};}
  cplx& operator*=(const cplx &c) { return *this={x*c.x-y*c.y, x*c.y+y*c.x}; }
  // Only supports right scalar multiplication like p*c
  template<class U> cplx operator*(const U &c) const {return {x*c,y*c};}
  template<class U> cplx operator/(const U &c) const {return {x/c,y/c};} };
typedef cplx<ld> pt;
inline ld abs(const pt &a) {return sqrt(a.x*a.x + a.y*a.y);}

ld sqr(ld x) { return x*x; }

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,r;
	cin >> n >> r;

	vector<pt> p;
	for (int i=0;i<n;i++) {
		int x,y;
		cin >> x >> y;
		p.push_back(pt(x,y));
	}

	int check = 0;
	for (int i=0;i<n;i++) {
		for (int j=0;j<i;j++) {
			if(abs(p[i]-p[j]) < EPS) continue;
			check++;
			ld d = abs(p[i]-p[j]);
			ld h2 = sqr(2*r) - sqr(d/2);
			if(h2 < 0) continue;
			ld h = sqrt(h2);
			pt m = (p[i]+p[j]) / (ld)2;
			pt perp = (p[i]-p[j])*pt(0,1) / abs(p[i]-p[j]);
			pt c1 = m + perp*h;
			pt c2 = m - perp*h;

			int cnt1 = 0;
			int cnt2 = 0;
			for (int k=0;k<n;k++) {
				if(abs(p[k]-c1) < 2*r+EPS) cnt1++;
				if(abs(p[k]-c2) < 2*r+EPS) cnt2++;
			}
			if(cnt1 == n || cnt2 == n) {
				cout << "possible" << nl;
				return 0;
			}
		}
	}

	if(check) cout << "impossible" << nl;
	else cout << "possible" << nl;

	return 0;
}

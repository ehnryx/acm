#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
//typedef long double ld;
typedef double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
const ld PI = M_PIl;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

////////////////////////////////////////////////////////////////////////////////
// Arbitrary-Dimension Minimum Enclosing Ball   TESTED UVa 10005(2D), 10095(3D)
////////////////////////////////////////////////////////////////////////////////
//!adapted from http://www.inf.ethz.ch/personal/gaertner/miniball.html
// Usage:
// 0. pray your soul remains intact after using black magic
// 1. create pt p(D) and set values in p[i] - DON'T FORGET THE D IN pt p(D)
// 2. add pt to Miniball mb with mb.add(p)
// 3. after adding all pts call mb.build() - WARNING: CALL THIS ONLY ONCE
// 4. coordinates of centre are in mb.c_c[d]
// 5. *SQUARED* radius of circle/ball/thing is in mb.c_r2
//*!
const int D = 2;
typedef vector<ld> ndpt;
typedef list<ndpt>::iterator It;
struct Miniball { list<ndpt> L; int m; vector<vector<ld> > v, a; vector<ndpt> c;
	ndpt q0; vector<ld> r2, z, f; It end; ndpt c_c; ld c_r2;
	Miniball() : m(0),v(D+1,vector<ld>(D)),a(D+1,vector<ld>(D)),c(D+1,ndpt(D,0)),
		q0(D), r2(D+1), z(D+1), f(D+1), end(L.begin()), c_c(c[0]), c_r2(-1.L) {}
	void add(ndpt &p) { L.push_back(p); }
	void move_to_front(It i) { m--; if (end==i) end++; L.splice(L.begin(),L,i); }
	void mtf_mb(It i) { end=L.begin(); if (m==D+1) return;
		for (It k=L.begin(),j;(j=k++)!=i;) { ld e = get_e(j);
			if (e > 0 && push(*j)) mtf_mb(j), move_to_front(j); } }
	void pivot_mb(It i) {
		It t=++L.begin(), pivot; mtf_mb(t); ld max_e, old_r2=-1;
		do { if((max_e=max_excess(t,i,pivot)) > 0) {
			if ((t=end)==pivot) ++t;
			old_r2=c_r2; push(*pivot); mtf_mb(end); move_to_front(pivot); }
		} while (max_e > 0 && c_r2 > old_r2); }
	ld max_excess(It j,It i,It& pivot) { ld max_e=0,e;
		for (; j!=i;++j) if ((e=get_e(j)) > max_e) max_e=e,pivot=j; return max_e; }
	ld get_e(It j) { ld e=-c_r2; for (int i=0;i<D;++i) e+=pow((*j)[i]-c_c[i], 2);
		return e; }
	bool push(const ndpt& p) { int i, j; if (!m) c[0]=q0=p, r2[0]=0; else {
			for (i=0;i<D;++i) v[m][i]=p[i]-q0[i];
			for (i=1;i<m;++i) { a[m][i]=0;
				for (j=0;j<D;++j) a[m][i]+=v[i][j]*v[m][j];
				a[m][i]*=(2/z[i]); }
			for (i=1;i<m;++i) for (j=0;j<D;++j) v[m][j]-=a[m][i]*v[i][j];
			z[m]=0; for (j=0;j<D;++j) z[m]+=2*pow(v[m][j], 2);
			if (z[m] < c_r2*EPS) return false;
			ld e=-r2[m-1]; for (i=0;i<D;++i) e+=pow(p[i]-c[m-1][i], 2);
			f[m]=e/z[m];
			for (i=0;i<D;++i) c[m][i]=c[m-1][i]+f[m]*v[m][i];
			r2[m]=r2[m-1]+e*f[m]/2;
		} c_c=c[m]; c_r2=r2[m]; m++; return true; }
	void build(){ pivot_mb(L.end()); }
};

////////////////////////////////////////////////////////////////////////////////
// Circles tangents (TESTED Chicago2012-H)
////////////////////////////////////////////////////////////////////////////////
pair<pt, pt> circle_tangent(ld r1, ld r2, ld d, int k) { // use the fcn below
  ld dr = (k & 2) ? (-r1-r2) : (r2-r1); ld t = asin(dr / d);
  pt p1=polar(r1, PI/2+t), p2=polar(r2, PI/2+t); if(k&2) p2*=-1; p2+=pt(d,0);
  if(k&1){ p1=pt(p1.real(),-p1.imag()); p2=pt(p2.real(),-p2.imag()); }
  return make_pair(p1, p2); }
// tested 2008wf conveyor; tangent of 2 circles; CAUTION: INTERSECTION IS BAD
// k=0 top-top, k=1 bot-bot, k=2 top-bot, k=3 bot-top. Also works for points.
pair<pt, pt> circle_tangent(pt p1, ld r1, pt p2, ld r2, int k) {
  // translate/rotate so c1 at (0,0), c2 at x-axis
  pt d = p2-p1; pair<pt, pt> p = circle_tangent(r1, r2, abs(d), k); d /= abs(d);
  p.first *= d; p.second *= d; p.first += p1; p.second += p1; return p;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(2);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, k, x, y;
	cin >> n >> k;

	vector<pt> p;
	for (int i=0; i<n; i++) {
		cin >> x >> y;
		p.emplace_back(x,y);
	}

	if (n<=5000) {
		ld dist[n+1][n+1];
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				dist[i][j] = abs(p[i]-p[j]);
			}
		}

		ld ans = INF;
		for (int i=0; i<n; i++) {
			ld left = 0;
			ld right = ans;
			while (right-left > 1e-6) {
				ld mid = (left+right)/2;
				vector<pair<ld,int>> segs;
				ld offset = 1+rng()%7;
				for (int j=0; j<n; j++) {
					if (i!=j && dist[i][j] <= mid) {
						pt out = p[i] + (p[j]-p[i])/dist[i][j]*mid*mid;
						auto first = circle_tangent(p[i], mid, out, 0, 0);
						auto second = circle_tangent(p[i], mid, out, 0, 1);
						ld s = arg((first.first-p[i])*exp(pt(0,offset)));
						ld t = arg((second.first-p[i])*exp(pt(0,offset)));
						segs.push_back({s, -1});
						segs.push_back({t+2*PI, 1});
						if (s <= t) {
							segs.push_back({s+2*PI, -1});
							segs.push_back({t, 1});
						}
					}
				}
				int cnt = -1;
				int res = 1;
				sort(segs.begin(), segs.end());
				cerr << nl << " DO " << mid << " @ " << i << nl;
				for (const pair<ld,int>& it : segs) {
					cnt += it.second;
					res = max(res, -cnt);
					cerr << it.first << " " << it.second << nl;
				}
				(res<k ? left : right) = mid;
			}
			ans = min(ans, left);
			cerr << "set ans to " << ans << " @ " << i << nl;
		}
		cout << ans/2 << nl;
	}

	else {
		auto cmpx = [](const pt& a, const pt& b) { return a.real() < b.real(); };
		auto cmpy = [](const pt& a, const pt& b) { return a.imag() < b.imag(); };
		sort(p.begin(), p.end(), cmpx);
		set<pt, decltype(cmpy)> cur(cmpy);
		int ptr = 0;
		ld ans = INF;
		for (const auto& it : p) {
		}
	}

	return 0;
}

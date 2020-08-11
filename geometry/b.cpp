#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long double ld;
typedef complex<ld> pt;

// define an epsilon for floating point comparisons
const ld EPS = 1e-11;

namespace CodeArchive {
	typedef vector<pt> pol;

	// cross product
	ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

	// comparator for complex numbers. first sorts by imaginary, then by real
	inline bool cmp_lex_i(const pt& a, const pt& b) {
		return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}

	// line point distance
	// SIGNED distance. Pt on the right of vector (a -> b) will be NEGATIVE.
	inline ld lp_dist(const pt &a, const pt &b, const pt &p) {
		return cp(b - a, p - a) / abs(b - a); }

	////////////////////////////////////////////////////////////////////////////////
	// 2D convex hull (TESTED SPOJ BSHEEP, UVA 11096)
	////////////////////////////////////////////////////////////////////////////////
	// Assumes nondegenerate, i.e. CH is not a line.
	pol chull(pol p) {
		sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
		for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
		// If there are no duplicates, can change <= 0 to < 0 to keep redundant points
			while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
			ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
		} ch.resize(max(1, top-1)); return ch; } // pts returned in ccw order.
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	// output exactly 12 digits after the decimal point
	cout << fixed << setprecision(12);

	int n;
	cin >> n;

	// we use complex numbers to represent 2D points
	vector<pt> points;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		points.push_back(pt(x, y));
	}

	// chull is the monotone chain algorithm for finding the convex hull
	vector<pt> hull = CodeArchive::chull(points);
	n = hull.size();  // number of points on hull != number of points in input

	// Don't forget to check  whether the solution works for edges cases
	// such as when all the points are on a line, or when there is only one point.
	// This solution fails when there is only one point, so deal with it here
	if (n == 1) {
		cout << 0 << nl;
		return 0;
	}

	// We do rotating calipers to find the farthest point from each edge,
	// and the minimum of these point to line distances would be our answer.

	// initialize ans to something larger than the largest possible result
	ld ans = 1e20;
	for (int i = 0, farthest = 1; i < n; i++) {
		int j = (i + 1) % n;  // get the other endpoint of the edge
		// find the farthest point from the current edge by moving the farthest pointer
		ld distToFarthest = abs(CodeArchive::lp_dist(hull[i], hull[j], hull[farthest]));
		ld distToNext = abs(CodeArchive::lp_dist(hull[i], hull[j], hull[(farthest + 1) % n]));
		while (distToNext > distToFarthest) {
			farthest = (farthest + 1) % n;
			distToFarthest = distToNext;
			distToNext = abs(CodeArchive::lp_dist(hull[i], hull[j], hull[(farthest + 1) % n]));
		}
		// update the answer
		ans = min(ans, distToFarthest);
	}

	cout << ans << nl;

	return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ld PI = acos(-1.L);
const ld EPS = 1e-10;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
auto random_dir = bind(uniform_real_distribution<ld>(0, 2*PI), rng);

ld sqr(ld x) { return x*x; }

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}
ld lp_dist(const pt& a, const pt& b, const pt& p) {
	return cp(b-a, p-a) / abs(b-a);
}

pt cur(0,0);
vector<int> memo;
vector<pt> pts;
vector<ld> dir, dist;

int query(ld d) {
	dir.push_back(d);
	cout << 180*d/PI << endl;

	string s;
	getline(cin, s);
	if (s == "Gotcha!") exit(0);
	if (s[0] == 'T') for(;;);

	istringstream ss(s);
	ld dd; int pp;
	ss >> dd >> pp;

	dist.push_back(dd);
	memo.push_back(pp);
	cur += exp(pt(0,PI*d/180)) * dd;
	pts.push_back(cur);
	return pp;
}

void circle(const pt& a, const pt& b, const pt& c, const pt& d) {
	cerr << "GOTO CIRCLE" << endl;
	pt mab = (a+b)/2.L;
	pt mcd = (c+d)/2.L;
	pt it = line_inter(mab, mab+(a-b)*pt(0,1), mcd, mcd+(c-d)*pt(0,1));
	ld ang = arg(it-cur);
	while (ang >= 2*PI) ang -= 2*PI;
	while (ang < 0) ang += 2*PI;
	for(;;) {
		query(ang);
	}
}

void closed(const pt& d, const pt& a, const pt& b, int k) {
	cerr << "GOTO GULAG" << endl;
	pt m = (a+b)/2.L;
	pt perp = m + (a-b)*pt(0,1);
	ld left = abs(a-b)/2/k;
	ld right = 100;
	for (int bs=0; bs<100; bs++) {
		ld r = (left+right)/2;
		ld h1 = abs(lp_dist(a, b, d));
		ld h2 = sqrt(sqr((k-1)*r) - sqr(lp_dist(m, perp, d)));
		if (sqr(k*r) - sqr(abs(a-b)/2) < sqr(h1+h2)) {
			right = r;
		} else {
			left = r;
		}
	}
	pt pdir = (perp-m)/abs(perp-m);
	pt it = pdir * sqrt(sqr(k*(left+right)/2) - sqr(abs(a-b)/2));
	ld ang = arg(it-cur);
	while (ang >= 2*PI) ang -= 2*PI;
	while (ang < 0) ang += 2*PI;
	for(;;) {
		query(ang);
	}
}

void solve(int k) {
	ld ang = PI - asin(dist.back()/2/k/100)/2 + dir.back();
	while (ang >= 2*PI) ang -= 2*PI;
	while (ang < 0) ang += 2*PI;
	int paws = query(ang);
	if (paws == k) {
		int n = pts.size();
		circle(pts[n-1], pts[n-2], pts[n-2], pts[n-3]);
	} else {
		assert(paws == k-1);
		int n = pts.size();
		closed(pts[n-1], pts[n-2], pts[n-3], k);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(16);

	pts.push_back(pt(0,0));

	// first direction arbitrary
	int paws = query(random_dir());
	//int paws = query(PI*269.4370269070402844L/180);

	if (dist.back() == 0) {
		paws = query(2*PI - dir.back());
	}

	if (paws == 3) {
		solve(3);
	} else {
		assert(paws == 2);
		paws = query(dir.back());
		if (paws == 2) {
			solve(2);
		} else {
			assert(paws == 1);
			paws = query(dir.back());
			assert(paws == 1);
			solve(1);
		}
	}

	assert(false);

	return 0;
}

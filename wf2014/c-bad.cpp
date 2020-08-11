#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const ld INF = 1e12;
const ld EPS = 1e-14;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

ld area(const pol& v) {
	ld s=0; int n=v.size();
	for (int i=n-1,j=0; j<n; i=j++) s += cp(v[i],v[j]);
	return s/2;
}

pt centroid(const pol& v) {
	pt res; ld A=0; int n=v.size();
	for (int i=n-1,j=0; j<n; i=j++) {
		A += cp(v[i],v[j]);
		res += (v[i]+v[j])*cp(v[i],v[j]);
	}
	return abs(A)<EPS ? res : res/3.L/A;
}

ld search(int goal, const pol& p) {
	ld a = abs(area(p));
	pt g = centroid(p);
	ld left = -1;
	ld right = INF;
	for (int bs=0; bs<420; bs++) {
		ld mid = (left+right)/2;
		pt c = (a*g + mid*p[0])/(a+mid);
		(c.real() < goal ? left : right) = mid;
	}
	return left;
}

ld search2(int goal, const pol& p) {
	ld a = abs(area(p));
	pt g = centroid(p);
	ld left = -1;
	ld right = INF;
	for (int bs=0; bs<420; bs++) {
		ld mid = (left+right)/2;
		pt c = (a*g + mid*p[0])/(a+mid);
		(c.real() > goal ? left : right) = mid;
	}
	return left;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(0);
	cerr << fixed << setprecision(17);

	int n;
	cin >> n;

	ld minv = INF;
	ld maxv = -INF;

	pol p;
	for (int i=0; i<n; i++) {
		int a, b;
		cin >> a >> b;
		p.push_back(pt(a,b));
		if (b == 0) {
			minv = min(minv, (ld)a);
			maxv = max(maxv, (ld)a);
		}
	}

	ld left = search(minv, p);
	ld right = search(maxv, p);
	if (left > INF-1) {
		left = search2(maxv, p);
		right = search2(minv, p);
	}
	cerr << "left: " << left << "   right: " << right << nl;
	if (right < -EPS) {
		cout << "unstable" << nl;
	} else if (right > INF-1) {
		cout << max((ld)0,floor(left*(1+EPS))) << " .. " << "inf" << nl;
	} else {
		cout << max((ld)0,floor(left*(1+EPS))) << " .. " << max((ld)0,ceil(right*(1-EPS))) << nl;
	}

	return 0;
}

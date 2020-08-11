#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const ll INF = 1e18L;
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

ll search1(int goal, const pol& p) {
	ld a = abs(area(p));
	pt g = centroid(p);
	ll left = -1;
	ll right = INF;
	while (left < right) {
		ll mid = llround(ceil((ld)(left+right)/2));
		pt c = (a*g + (-EPS+mid*(1-EPS))*p[0])/(a+(-EPS+mid*(1-EPS)));
		if (c.real() < goal) {
			left = mid;
		} else {
			right = mid-1;
		}
	}
	return left;
}

ll search2(int goal, const pol& p) {
	ld a = abs(area(p));
	pt g = centroid(p);
	ll left = -1;
	ll right = INF;
	while (left < right) {
		ll mid = llround(floor((ld)(left+right)/2));
		pt c = (a*g + (EPS+mid*(1+EPS))*p[0])/(a+(EPS+mid*(1+EPS)));
		if (c.real() > goal) {
			right = mid;
		} else {
			left = mid+1;
		}
	}
	return left;
}

ll search3(int goal, const pol& p) {
	ld a = abs(area(p));
	pt g = centroid(p);
	ll left = -1;
	ll right = INF;
	while (left < right) {
		ll mid = llround(ceil((ld)(left+right)/2));
		pt c = (a*g + (-EPS+mid*(1-EPS))*p[0])/(a+(-EPS+mid*(1-EPS)));
		if (c.real() > goal) {
			left = mid;
		} else {
			right = mid-1;
		}
	}
	return left;
}

ll search4(int goal, const pol& p) {
	ld a = abs(area(p));
	pt g = centroid(p);
	ll left = -1;
	ll right = INF;
	while (left < right) {
		ll mid = llround(floor((ld)(left+right)/2));
		pt c = (a*g + (EPS+mid*(1+EPS))*p[0])/(a+(EPS+mid*(1+EPS)));
		if (c.real() < goal) {
			right = mid;
		} else {
			left = mid+1;
		}
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

	ll left = search1(minv, p);
	ll right = search2(maxv, p);
	if (left == INF) {
		left = search3(maxv, p);
		right = search4(minv, p);
	}
	cerr << left << " " << right << nl;
	//if (right < 0 || left == INF) {
	if (right < 0) {
		cout << "unstable" << nl;
	} else if (right == INF) {
		cout << max((ll)0,left) << " .. " << "inf" << nl;
	} else {
		cout << max((ll)0,left) << " .. " << right << nl;
	}

	return 0;
}

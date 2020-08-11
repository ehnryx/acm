#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define ll long long
#define ld long double
#define pt complex<ld>
#define pol vector<pt>
#define pii pair<int,int>
#define pdd pair<ld,ld>
#define nl '\n'

const ld EPS = 1e-2;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
	return a.imag()<b.imag()-EPS || (a.imag()<b.imag()+EPS && a.real()<b.real()-EPS);
}
inline ld angle(const pt& a, const pt& b) {
	if (abs(b) < EPS) for(;;);
	return dp(a,b)/abs(b);
}

pol chull(pol p) {
	sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
	for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
		while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
		ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
	} ch.resize(max(1, top-1)); return ch;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, k;
	cin >> n >> k;

	vector<pt> good, all;
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		all.push_back(pt(x,y));
		if (i < k) good.push_back(pt(x,y));
	}
	vector<pt> inner = chull(good);
	vector<pt> outer = chull(all);

	//cerr << "inner hull: "; for (pt p : inner) 
		//cerr << p << " "; 
	//cerr << nl;
	//cerr << "outer hull: "; for (pt p : outer) 
		//cerr << p << " "; 
	//cerr << nl;
	//cerr << nl;

	int m = inner.size();
	ld shoe[2*m+1];
	shoe[0] = 0;
	for (int i = 1; i <= 2*m; i++) {
		shoe[i] = shoe[i-1] + cp(inner[(i-1)%m], inner[i%m]);
	}

	int left, right;
	left = right = -1;
	ld minangle = -INF;
	ld maxangle = INF;
	ld tempangle;
	pt base = outer[1] - outer[0];
	for (int i = 0; i < m; i++) {
		if (inner[i] == outer[0]) {
			continue;
		}
		tempangle = angle(base, inner[i]-outer[0]);
		if (tempangle > minangle) {
			minangle = tempangle;
			right = i;
		}
		if (tempangle < maxangle) {
			maxangle = tempangle;
			left = i;
		}
	}
	if (left == -1 || right == -1) for(;;);
	//cerr << "initial left: " << left << " " << inner[left] << nl;
	//cerr << "initial right: " << right << " " << inner[right] << nl;
	//cerr << nl;

	ld orig = abs(shoe[m])/2;
	ld ans = orig;
	n = outer.size();
	for (int i = 0; i < n; i++) {
		base = outer[(i+1)%n] - outer[i];
		if (inner[right] == outer[i]) right = (right+1)%m;
		minangle = angle(base, inner[right]-outer[i]);
		tempangle = -INF;
		while (inner[right] == outer[i] || inner[(right+1)%m] == outer[i] 
				|| (tempangle = angle(base, inner[(right+1)%m]-outer[i])) > minangle) {
			minangle = tempangle;
			tempangle = -INF;
			right = (right+1)%m;
		}
		if (inner[left] == outer[i]) left = (left+1)%m;
		maxangle = angle(base, inner[left]-outer[i]);
		while (inner[(left+1)%m] != outer[i] 
				&& (tempangle = angle(base, inner[(left+1)%m]-outer[i])) < maxangle) {
			maxangle = tempangle;
			left = (left+1)%m;
		}
		if (abs(minangle) == INF || abs(maxangle) == INF) for(;;);
		//cerr << "try adding point " << i << ": " << outer[i] << nl;
		//cerr << "left caliper: " << left << " " << inner[left] << nl;
		//cerr << "right caliper: " << right << " " << inner[right] << nl;

		left %= m; right %= m;
		ld more = cp(inner[right], outer[i]) + cp(outer[i], inner[left]);
		if (right > left) more += shoe[right] - shoe[left];
		else more += shoe[right+m] - shoe[left];
		ans = max(ans, orig + abs(more)/2);
		//cerr << "updated ans " << ans << nl;
		//cerr << nl;
	}

	cout << fixed << setprecision(1) << ans << nl;

	return 0;
}

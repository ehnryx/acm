#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos(-1.L);

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }

inline pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); 
}

// Area of a polygon (convex or concave). Always non-negative.
ld area(const pol &v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]); return abs(s)/2;
}

// Left of the vector (a -> b) will be cut off. Convex polygons tested UVa 10117
// Simple polygon tested KTH Challenge 2013 G
pol cut_polygon(const pol &v, const pt &a, const pt &b) { pol out;
  for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    if(cp(b-a, v[i]-a) < EPS) out.push_back(v[i]);
    if(sgn(cp(b-a, v[i]-a)) * sgn(cp(b-a, v[j]-a)) < 0) {
      pt p = line_inter(a, b, v[i], v[j]);
      if(!out.size() || abs(out.back() - p) > EPS) out.push_back(p); } }
  while(out.size() && abs(out[0] - out.back()) < EPS) out.pop_back();
  return out; 
}

const int N = 11;
map<ld,pdd> dp[1<<N];

pdd solve(const ld total, const vector<ld>& vals, int left, ld first, ld second) {
	if (!left) return pdd(first,second);
	if (dp[left].count(first)) return dp[left][first];

	int turn = (first < second + EPS);
	pdd ans = turn ? pdd(0,total) : pdd(total,0);
	for (int i = 0; i < vals.size(); i++) {
		if (left & 1<<i) {
			if (turn) {
				pdd cur = solve(total, vals, left ^ 1<<i, first + vals[i], second);
				if (cur.first > ans.first) ans = cur;
			} else {
				pdd cur = solve(total, vals, left ^ 1<<i, first, second + vals[i]);
				if (cur.second > ans.second) ans = cur;
			}
		}
	}
	return dp[left][first] = ans;
}

#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("vs.in", "r", stdin);
	freopen("vs.out", "w", stdout);
#endif

	int n, r;
	cin >> n >> r;

	vector<pol> pieces[2];
	pol circle;
	for (int i = 0; i < 1e5; i++) {
		circle.push_back((ld)r*exp(pt(0,2*PI*i/1e5)));
	}
	pieces[0].push_back(circle);


	int cur = 0;
	int a, b, c;
	for (int i=0; i<n; i++) {
		cin >> a >> b >> c;

		pt x, y;
		if (b == 0) {
			x = pt((ld)-c/a, 0);
			y = pt((ld)-c/a, 1);
		}
		else {
			x = pt(0, (ld)-c/b);
			y = pt(1, (ld)(-c-a)/b);
		}

		pieces[cur^1].clear();
		for (const pol& p : pieces[cur]) {
			pol left = cut_polygon(p, x, y);
			pol right = cut_polygon(p, y, x);
			if (!left.empty()) pieces[cur^1].push_back(left);
			if (!right.empty()) pieces[cur^1].push_back(right);
		}
		cur ^= 1;
	}

	vector<ld> vals;
	ld total = 0;
	for (const pol& p : pieces[cur]) {
		vals.push_back(area(p));
		total += vals.back();
	}

	pdd ans = solve(total, vals, (1<<vals.size())-1, 0, 0);
	cout << ans.first << " " << ans.second << nl;

	return 0;
}

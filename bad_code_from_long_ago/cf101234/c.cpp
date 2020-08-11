#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ll> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
//const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;



#define RIGHT 	0
#define UP 		1
#define LEFT 	2
#define DOWN 	3

inline ll area(const pt& a, const pt& b, const pt& c) {
	return (a.real()*b.imag() + b.real()*c.imag() + c.real()*a.imag())
		- (a.imag()*b.real() + b.imag()*c.real() + c.imag()*a.real());
}
inline ll sgn(ll x) { return (x == 0) ? 0 : x/abs(x); }
inline bool seg_x_seg(pair<pt,pt> a, pair<pt,pt> b) {
	ll a1 = sgn(area(a.first, a.second, b.first));
	ll a2 = sgn(area(a.first, a.second, b.second));
	ll b1 = sgn(area(b.first, b.second, a.first));
	ll b2 = sgn(area(b.first, b.second, a.second));
	return a1*a2 <= 0 && b1*b2 <= 0;
}
////////////////////////////////////////////////////////////////////////////////

const int lim = 2000;
int grid[lim+1][lim+1];
pair<pt,pt> edges[lim+1][lim+1][4];

inline void init() {
	memset(grid, 0, sizeof grid);
	for (int i = 1; i <= lim; i++) {
		for (int j = 1; j <= lim; j++) {
			edges[i][j][RIGHT] = pair<pt,pt>(pt(i,j), pt(i,j-1));
			edges[i][j][UP] = pair<pt,pt>(pt(i,j), pt(i-1,j));
			edges[i][j][LEFT] = pair<pt,pt>(pt(i-1, j-1), pt(i-1, j));
			edges[i][j][DOWN] = pair<pt,pt>(pt(i-1, j-1), pt(i, j-1));
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	init();

	int n;
	cin >> n;

	int c, d;
	int a, b, x, y;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> x >> y;
		pt start(a,b);
		pt end(x,y);
		pair<pt,pt> seg(start, end);

		if (x > a && y > b) {
			pt cur = pt(a+1, b+1);
			while (cur.real() <= x && cur.imag() <= y) {
				grid[cur.real()][cur.imag()] = 1;
				c = seg_x_seg(edges[cur.real()][cur.imag()][UP], seg);
				d = seg_x_seg(edges[cur.real()][cur.imag()][RIGHT], seg);
				if (c && d) {
					cur += pt(1,1);
				} else if (c) {
					cur += pt(0,1);
				} else if (d) {
					cur += pt(1,0);
				} else {
					break;
				}
			}
		}

		else if (x < a && y < b) {
			pt cur = pt(a, b);
			while (cur.real() > x && cur.imag() > y) {
				grid[cur.real()][cur.imag()] = 1;
				c = seg_x_seg(edges[cur.real()][cur.imag()][DOWN], seg);
				d = seg_x_seg(edges[cur.real()][cur.imag()][LEFT], seg);
				if (c && d) {
					cur += pt(-1,-1);
				} else if (c) {
					cur += pt(0,-1);
				} else if (d) {
					cur += pt(-1,0);
				} else {
					break;
				}
			}
		}

		else if (x > a && y < b) {
			pt cur = pt(a+1, b);
			while (cur.real() <= x && cur.imag() > y) {
				grid[cur.real()][cur.imag()] = 1;
				c = seg_x_seg(edges[cur.real()][cur.imag()][DOWN], seg);
				d = seg_x_seg(edges[cur.real()][cur.imag()][RIGHT], seg);
				if (c && d) {
					cur += pt(1,-1);
				} else if (c) {
					cur += pt(0,-1);
				} else if (d) {
					cur += pt(1,0);
				} else {
					break;
				}
			}
		}

		else if (x < a && y > b) {
			pt cur = pt(a, b+1);
			while (cur.real() > x && cur.imag() <= y) {
				grid[cur.real()][cur.imag()] = 1;
				c = seg_x_seg(edges[cur.real()][cur.imag()][UP], seg);
				d = seg_x_seg(edges[cur.real()][cur.imag()][LEFT], seg);
				if (c && d) {
					cur += pt(-1,1);
				} else if (c) {
					cur += pt(0,1);
				} else if (d) {
					cur += pt(-1,0);
				} else {
					break;
				}
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= 2000; i++) {
		for (int j = 1; j <= 2000; j++) {
			ans += grid[i][j];
		}
	}
	cout << ans << nl;

	return 0;
}

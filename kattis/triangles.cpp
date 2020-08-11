#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

////////////////////////////////////////////////////////////////////////////////
// General 3D geometry
////////////////////////////////////////////////////////////////////////////////
struct p3d{ ld x,y,z; friend ostream& operator<< (ostream& os, const p3d& p) {
  return os << "(" << p.x << "," << p.y << "," << p.z << ")"; } };
ld abs(const p3d &v){ return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
p3d operator+(const p3d&a,const p3d&b){ return {a.x+b.x,a.y+b.y,a.z+b.z}; }
p3d operator-(const p3d&a,const p3d&b){ return {a.x-b.x,a.y-b.y,a.z-b.z}; }
p3d operator*(const ld &s, const p3d &v){ return {s*v.x, s*v.y, s*v.z}; }
p3d operator/(const p3d&v, const ld &s){ return {v.x/s, v.y/s, v.z/s}; }
inline ld dot(const p3d &a, const p3d &b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
inline p3d cross(const p3d &a, const p3d &b){
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; }
inline ld dist(const p3d &s, const p3d &p) {
  return (p.x-s.x)*(p.x-s.x) + (p.y-s.y)*(p.y-s.y) + (p.z-s.z)*(p.z-s.z); }
// plane/line intersection. p - pt on plane, n - normal, a1 -> a2 : line
inline p3d pl_inter(const p3d &p, const p3d &n, const p3d &a1, const p3d &a2){
  return a1 + dot(p - a1, n)/dot(n, a2 - a1)*(a2 - a1);
}
////////////////////////////////////////////////////////////////////////////////

bool pt_in_polygon(const p3d& p, const vector<p3d>& v, const p3d& n) {
	ld res = 0;
	for (int i=v.size()-1,j=0; j<v.size(); i=j++) {
		res += atan2(dot(n,cross(v[i]-p,v[j]-p)), dot(v[i]-p,v[j]-p));
	}
	return abs(res) > 1;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int T;
	cin >> T;
	while (T--) {
		vector<p3d> p[2];
		p3d normal[2];
		for (int t=0; t<2; t++) {
			for (int i=0; i<3; i++) {
				int x,y,z;
				cin >> x >> y >> z;
				p[t].push_back({x,y,z});
			}
			normal[t] = cross(p[t][1]-p[t][0], p[t][2]-p[t][0]);
			normal[t] = normal[t] / abs(normal[t]);
		}
		int cnt = 0;
		for (int i=0; i<3; i++) {
			int j = (i+1<3 ? i+1 : 0);
			if (abs(dot(p[0][i]-p[0][j], normal[1])) > EPS) {
				p3d it = pl_inter(p[1][0], normal[1], p[0][i], p[0][j]);
				if (abs(it-p[0][i]) + abs(it-p[0][j]) < abs(p[0][i]-p[0][j])+EPS) {
					cnt += pt_in_polygon(it, p[1], normal[1]);
				}
			}
		}
		cout << (cnt%2==1 ? "YES" : "NO") << nl;
	}

	return 0;
}

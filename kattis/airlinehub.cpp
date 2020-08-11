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
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct p3d{ ld x,y,z; friend ostream& operator<< (ostream& os, const p3d& p) {
	return os << "(" << p.x << "," << p.y << "," << p.z << ")"; } };
ld abs(const p3d &v){ return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
p3d operator+(const p3d&a,const p3d&b){ return {a.x+b.x,a.y+b.y,a.z+b.z}; }
p3d operator-(const p3d&a,const p3d&b){ return {a.x-b.x,a.y-b.y,a.z-b.z}; }
p3d operator*(const ld &s, const p3d &v){ return {s*v.x, s*v.y, s*v.z}; }
inline ld dot(const p3d &a, const p3d &b){ return a.x*b.x + a.y*b.y + a.z*b.z; }

const int N = 1e3+1;
ld lon[N],lat[N],dist[N];
p3d p[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(2);

	for(int n;cin>>n;) {
		for(int i=0;i<n;i++) {
			cin>>lat[i]>>lon[i];
			p[i].x = cos(lat[i]*M_PI/180) * cos(lon[i]*M_PI/180);
			p[i].y = cos(lat[i]*M_PI/180) * sin(lon[i]*M_PI/180);
			p[i].z = sin(lat[i]*M_PI/180);
		}
		ld best = INF;
		int ans = -1;
		for(int i=0;i<n;i++) {
			ld cur = 0;
			for(int j=0;j<n;j++) {
				cur = max(cur, acos(dot(p[i],p[j])));
			}
			if(cur < best+EPS) {
				best = cur;
				ans = i;
			}
		}
		assert(ans!=-1);
		cout<<lat[ans]<<" "<<lon[ans]<<nl;
	}

	return 0;
}

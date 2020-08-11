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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct p3d { ld x,y,z; };
p3d operator - (const p3d& a, const p3d& b) {
	return {a.x-b.x, a.y-b.y, a.z-b.z};
}
p3d operator / (const p3d& a, const ld& b) {
	return {a.x/b, a.y/b, a.z/b};
}
p3d rotate(const p3d& p, const p3d& u, const ld& angle) {
	ld c = cos(angle), s = sin(angle); ld t = 1-c; return {
		p.x*(t*u.x*u.x + c) + p.y*(t*u.x*u.y - s*u.z) + p.z*(t*u.x*u.z + s*u.y),
		p.x*(t*u.x*u.y + s*u.z) + p.y*(t*u.y*u.y + c) + p.z*(t*u.y*u.z - s*u.x),
		p.x*(t*u.x*u.z - s*u.y) + p.y*(t*u.y*u.z + s*u.x) + p.z*(t*u.z*u.z + c),
	};
}
ld abs(const p3d& p) {
	return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
}

const ld ang = 2*acos((ld)-1)/3;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(6);

	freopen("jupiter.in", "r", stdin);

	int T;
	cin>>T;
	while(T--) {
		int nx,ny,nz,ax,ay,az,_,H;
		cin>>nx>>ny>>nz>>ax>>ay>>az>>_>>H;
		p3d n = {nx,ny,nz};
		n = n / abs(n);
		p3d a = {ax,ay,az};
		p3d b = rotate(a,n,ang);
		p3d c = rotate(b,n,ang);
		p3d h = {0,0,-H};
		cout<<abs(a-h)<<" "<<abs(b-h)<<" "<<abs(c-h)<<nl;
	}

	return 0;
}

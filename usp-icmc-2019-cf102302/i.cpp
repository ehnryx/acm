#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Point {
	int x,y;
	bool operator < (const Point& o) const {
		if(x!=o.x) return x<o.x;
		else return y>o.y;
	}
};

bool ccw(Point a, Point b, Point c) {
	ll x1 = a.x-b.x;
	ll y1 = a.y-b.y;
	ll x2 = c.x-b.x;
	ll y2 = c.y-b.y;
	return x1*y2-x2*y1 > 0;
}

set<Point> s;
void insert(Point p) {
	s.insert(p);
	auto it = s.find(p);
	if(next(it)!=s.end()) {
		if(p.x<next(it)->x&&p.y<next(it)->y) {
			s.erase(p);
			return;
		}
		if(it!=s.begin()) {
			if(ccw(*next(it),*it,*prev(it))) {
				s.erase(p);
				return;
			}
		}
	}
	for(auto jt=it;jt!=s.begin();) {
		if(prev(jt)->x<p.x&&prev(jt)->y<p.y) {
			jt = s.erase(prev(jt));
		} else if(prev(jt)!=s.begin() && ccw(*jt,*prev(jt),*prev(prev(jt)))) {
			jt = s.erase(prev(jt));
		} else {
			break;
		}
	}
	assert(it->x==p.x&&it->y==p.y);
	if(next(it)!=s.end()) {
		for(auto jt=next(it);next(jt)!=s.end();) {
			if(ccw(*next(jt),*jt,*it)) {
				jt = s.erase(jt);
			} else {
				break;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	int a[n],b[n];
	for(int i=0;i<n;i++) {
		cin>>a[i]>>b[i];
		insert({a[i],b[i]});
		cout<<i+1-s.size()<<nl;
		//cerr<<"vals: "<<nl; for(Point j:s) {
		//cerr<<j.x<<','<<j.y<<nl; }
		//cerr<<nl;
	}

	return 0;
}

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

/*
struct Frac {
	ll n, d;
	Frac(ll a=0, ll b=1) {
		ll g = abs(__gcd(a,b));
		n = a/g; d = b/g;
		if(d==0) { n = abs(n); }
		if(d<0) { n=-n; d=-d; }
	}
	bool operator < (const Frac& o) const { return n*o.d < d*o.n; }
	bool operator <= (const Frac& o) const { return n*o.d <= d*o.n; }
	bool operator == (const Frac& o) const { return n*o.d == d*o.n; }
	Frac operator + (const Frac& o) const { return Frac(n*o.d + d*o.n, d*o.d); }
	Frac operator - (const Frac& o) const { return Frac(n*o.d - d*o.n, d*o.d); }
	Frac operator * (const Frac& o) const { return Frac(n*o.n, d*o.d); }
	Frac operator / (const Frac& o) const { return Frac(n*o.d, d*o.n); }
	friend ostream& operator << (ostream& os, const Frac& v) {
		return os<<v.n<<"/"<<v.d;
	}
};
*/

typedef long double Frac;

struct Point {
	Frac x,y;
	Point(int _x=0, int _y=0): x(_x), y(_y) {}
	Point(const Frac& _x, const Frac& _y): x(_x), y(_y) {}
	Frac dist() const {
		return x*x + y*y;
	}
	friend ostream& operator << (ostream& os, const Point& v) {
		return os<<"("<<v.x<<","<<v.y<<")";
	}
};

struct Wall {
	Point a,b; int i,v;
	Wall(int c, int d, int x, int y, int _i): a(c,d), b(x,y), i(_i), v(0) {}
	Wall(const Point& _a, const Point& _b, int _i, int _v):
		a(_a), b(_b), i(_i), v(_v) {}
	bool operator < (const Wall& o) const { return i<o.i; }
	Wall reflect(const Wall& w, int nv) const {
		return Wall(reflect(w.a), reflect(w.b), w.i, nv);
	}
	Point reflect(const Point& p) const {
		if(a.x==b.x) return Point(a.x-p.x+a.x, p.y);
		else return Point(p.x, a.y-p.y+a.y);
	}
	bool block(const Point& p) const {
		Point it = intersect(p);
		/*
		if(a.x==b.x) return min(a.y,b.y)<=it.y+EPS && it.y<=max(a.y,b.y)+EPS
			&& min(Frac(0),p.x)<=a.x+EPS && a.x<=max(Frac(0),p.x)+EPS;
		else return min(a.x,b.x)<=it.x+EPS && it.x<=max(a.x,b.x)+EPS
			&& min(Frac(0),p.y)<=a.y+EPS && a.y<=max(Frac(0),p.y)+EPS;
		*/
		if(a.x==b.x) return min(a.y,b.y)<=it.y && it.y<=max(a.y,b.y)
			&& min(Frac(0),p.x)<=a.x && a.x<=max(Frac(0),p.x);
		else return min(a.x,b.x)<=it.x && it.x<=max(a.x,b.x)
			&& min(Frac(0),p.y)<=a.y && a.y<=max(Frac(0),p.y);
	}
	Point intersect(const Point& p) const {
		if(a.x==b.x) return Point(a.x,p.y/p.x*a.x);
		else return Point(p.x/p.y*a.y,a.y);
	}
	friend ostream& operator << (ostream& os, const Wall& v) {
		return os<<"[ "<<v.a<<" , "<<v.b<<" ]: "<<v.i<<" "<<v.v;
	}
};

int solve(int m, vector<Wall> w, Point h) {
	//cerr<<nl;
	//cerr<<"solving "<<m<<" w/ "<<nl; for(const Wall& it:w) //cerr<<it<<nl;
	int n = w.size();
	vector<Wall> all = w;
	w.push_back(Wall(h,h,-1,0));
	for(int i=0;i<m;i++) {
		for(int j=i+1;j<n;j++) {
			w[j] = w[i].reflect(w[j],i+1);
			all.push_back(w[j]);
		}
		h = w[i].reflect(h);
	}
	//cerr<<"goal: "<<h<<nl;

	vector<pair<Frac,Wall>> inters;
	for(const Wall& it:all) {
		if(it.block(h)) {
			//cerr<<" intersect w/ "<<it<<" @ "<<it.intersect(h)<<nl;
			inters.push_back(make_pair(it.intersect(h).dist(),it));
		}
	}
	inters.push_back(make_pair(h.dist(),Wall(h,h,-1,m)));
	w[m] = Wall(h,h,-1,m);
	sort(inters.begin(),inters.end());

	int version = 0;
	for(const auto& it:inters) {
		if(it.second.v == version) {
			//cerr<<"hit wall "<<it.second<<"  @  "<<it.first<<nl;
			if(it.second.i != w[version].i) return -1;
			if(version==m) {
				//cerr<<"good!"<<endl;
				return m;
			}
			version++;
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;

	int x,y;
	cin>>x>>y;
	Point hole(x,y);

	vector<Wall> walls;
	for(int i=0;i<n;i++) {
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		walls.push_back(Wall(a,b,c,d,i));
	}

	int ans = solve(0,walls,hole);
	unordered_set<int> seen;
	do {
		for(int i=1;i<=n;i++) {
			int cur = 0;
			for(int j=0;j<i;j++) {
				cur = cur<<4|(walls[j].i+1);
			}
			if(!seen.count(cur)) {
				seen.insert(cur);
				ans = max(ans, solve(i,walls,hole));
			}
		}
	} while(next_permutation(walls.begin(),walls.end()));

	if(ans<0) cout<<"impossible"<<nl;
	else cout<<ans<<nl;

	return 0;
}

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <random>
#include <chrono>
#include <utility>
using namespace std;

typedef long long ll;
typedef long double ld;

const char nl = '\n';
const ll MOD = 1e9+7;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	os<<"[ "; for(T it:v) { os<<it<<", "; }
	return os<<"]";
}

/*
ll __gcd(ll a, ll b) {
	if(b==0) return a;
	return __gcd(b,a%b);
}
*/

struct Frac {
	ll n, d;
	Frac(ll a=0, ll b=1) {
		ll g = abs(__gcd(a,b));
		n = a/g; d = b/g;
	}
	bool operator == (const Frac& o) const {
		return n*o.d == o.n*d;
	}
	bool operator < (const Frac& o) const {
		return n*o.d < o.n*d;
	}
	bool operator <= (const Frac& o) const {
		return n*o.d <= o.n*d;
	}
	Frac operator + (const Frac& o) const {
		return Frac(n*o.d + o.n*d, d*o.d);
	}
	Frac operator - (const Frac& o) const {
		return Frac(n*o.d - o.n*d, d*o.d);
	}
	Frac operator / (const Frac& o) const {
		return Frac(n*o.d, d*o.n);
	}
	friend ostream& operator << (ostream& os, const Frac& v) {
		return os<<v.n<<" / "<<v.d;
	}
};

bool solve(int a, int b) {
	set<Frac> s;
	for(int i=0;i<a;i++) {
		s.insert(Frac(i,a));
	}
	Frac offset(1,2*a);
	for(int i=0;i<b;i++) {
		Frac cur = offset + Frac(i,b);
		if(Frac(1) <= cur) {
			cur = cur - Frac(1);
		}
		if(s.count(cur)) return false;
		s.insert(cur);
	}

	Frac minv(1);
	Frac maxv(0);
	for(auto it=s.begin();next(it)!=s.end();it++) {
		minv = min(minv, *next(it)-*it);
		maxv = max(maxv, *next(it)-*it);
	}
	cout<<maxv-minv<<nl;
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout<<fixed<<setprecision(13);

	int a,b;
	cin>>a>>b;
	if(solve(a,b));
	else assert(solve(b,a));

	return 0;
}

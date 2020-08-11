#include <bits/stdc++.h>
using namespace std;
#define FILENAME "distribution"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

ll power(ll n, int e) {
	ll res = 1;
	for(int i=0; i<e; i++) {
		res *= n;
	}
	return res;
}

vector<ll> solve(ll n, ll ua, ll ub, bool& ok) {
	//cerr<<"solve "<<n<<" "<<ua<<" "<<ub<<nl;
	if(n == 0) {
		ok = true;
		return {};
	}

	ll f = 1;
	while(n%2 == 0) {
		f *= 2;
		n /= 2;
		ua /= 2;
	}
	while(n%3 == 0) {
		f *= 3;
		n /= 3;
		ub /= 3;
	}
	if(n == 1) {
		if(ua>0 && ub>0) {
			ok = true;
			return {f};
		} else {
			ok = false;
			return {};
		}
	}

	while (ua > n) ua /= 2;
	while (ub > n) ub /= 3;
	if(ua == ub || ua == 0 || ub == 0) {
		ok = false;
		return {};
	}

/*
	if(ua+ub <= n && (n-ua-ub) % 6 == 0) {
		bool nxt = false;
		vector<ll> out = solve(n-ua-ub, ua/2, ub/3, nxt);
		if(nxt) {
			out.push_back(ua);
			out.push_back(ub);
			for(ll& it : out) {
				it *= f;
			}
			ok = true;
			return out;
		}
	}

	if(ua/2+ub <= n && (n-ua/2-ub) % 6 == 0) {
		bool nxt = false;
		vector<ll> out = solve(n-ua/2-ub, ua/2/2, ub/3, nxt);
		if(nxt) {
			out.push_back(ua/2);
			out.push_back(ub);
			for(ll& it : out) {
				it *= f;
			}
			ok = true;
			return out;
		}
	}

	if(ua+ub/3 <= n && (n-ua-ub/3) % 6 == 0) {
		bool nxt = false;
		vector<ll> out = solve(n-ua-ub/3, ua/2, ub/3/3, nxt);
		if(nxt) {
			out.push_back(ua);
			out.push_back(ub/3);
			for(ll& it : out) {
				it *= f;
			}
			ok = true;
			return out;
		}
	}

	if(ua/2+ub/3 <= n && (n-ua/2-ub/3) % 6 == 0) {
		bool nxt = false;
		vector<ll> out = solve(n-ua/2-ub/3, ua/2/2, ub/3/3, nxt);
		if(nxt) {
			out.push_back(ua/2);
			out.push_back(ub/3);
			for(ll& it : out) {
				it *= f;
			}
			ok = true;
			return out;
		}
	}
*/

	const int M = 6;
	for(int cnt=0; cnt<M; cnt++) {
		for(int ac=0; ac<=cnt; ac++) {
			for(int bc=0; ac+bc<=cnt; bc++) {
				ll a = ua;
				ll b = ub;
				for(int i=0; i<ac; i++) a /= 2;
				for(int i=0; i<bc; i++) b /= 3;
				if(a>1 && b>1 && a+b <= n && (n-a-b) % 6 == 0) {
					bool nxt = false;
					vector<ll> out = solve(n-a-b, a/2, b/3, nxt);
					if(nxt) {
						out.push_back(a);
						out.push_back(b);
						for(ll& it : out) {
							it *= f;
						}
						ok = true;
						return out;
					}
				}
			}
		}
	}

	ok = false;
	return {};

	/*
	auto [a, b] = ab;
	vector<ll> out = solve(n-a-b);
	out.push_back(a);
	out.push_back(b);
	for(ll& it : out) {
		it *= f;
	}
	return out;
	*/
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);

	int T;
	cin >> T;
	while(T--) {
		ll n;
		cin >> n;
		bool ok = false;
		vector<ll> res = solve(n, power(2, 59), power(3, 37), ok);
		ll sum = 0;
		assert(ok);
		cout << res.size() << nl;
		for(ll it : res) {
			sum += it;
			cout << it << " ";
		}
		cout << nl;
		//cerr<<endl;
		assert(sum == n);
		for(ll i:res) {
			for(ll j:res) {
				assert(i==j || (i%j != 0 && j%i != 0));
			}
		}
	}

	return 0;
}

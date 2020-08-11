#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll LIM = 2e6;

ll k;
inline ll solve(ll _n, ll _m, ll ind) {
	//cerr << n << " " << m << " " << k << " " << ind << nl;
	stack<ll> kills, inds;
	kills.push(0);
	inds.push(ind);
	ll nx = -1;
	while (!kills.empty()) {
		ll totkill = kills.top();
		ll n = _n - totkill;
		ll m = _m - totkill;
		ind = inds.top();
		ind %= n;
		ll kll = 1 + (n - ind - 1) / k;
		if (kll >= m) {
			nx = ind + (m-1) * k;
			kills.pop(); inds.pop();
			break;
		}
		ll lastkll = ind + k * (kll - 1);
		kills.push(totkill + kll);
		inds.push(k - (n - 1 - lastkll) - 1);
	}
	assert(nx != -1);
	while (!kills.empty()) {
		ll totkill = kills.top(); kills.pop();
		ll n = _n - totkill;
		//ll m = _n - totkill;
		ind = inds.top(); inds.pop();
		ind %= n;
		if (nx >= ind) nx += (nx-ind)/(k-1) + 1;
		/*
		ll l = 0, r = n-1, ans = -1;
		while (l <= r) {
			ll mid = (l+r)/2;
			ll klled = mid < ind ? 0 : 1 + (mid - ind) / k;
			//cerr << mid << " " << klled << nl;
			if (mid - klled >= nx) {
				ans = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		nx = ans;*/
	}
	return nx;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int TT; cin >> TT;
	for (int tt = 1; tt <= TT; tt++) {
		cout << "Case #" << tt << ": ";
		ll n, m; cin >> n >> m >> k;
		cout << solve(n, m, (k-1)%n) + 1 << nl;
	}

	return 0;
}

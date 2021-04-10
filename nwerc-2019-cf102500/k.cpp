#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 507 * 507 * 4;
ll ans[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	ll s, d, t;
	cin >> s >> d >> t;

	function<int(int,int)> water = [=](int l, int r) {
		ll res = r-l;
		res = min(res, (ll)(r-l+d-1)/d * t);
		res = min(res, (ll)(r-l)/d * t + (r-l)%d);
		return res;
	};

	int rid = 0;
	map<int,int> remap;
	remap[0] = rid++;

	int n;
	cin >> n;

	set<pair<int,int>> land;
	for(int i=0; i<n; i++) {
		int l, r;
		cin >> l >> r;
		land.insert(make_pair(l, r));
	}
	land.insert(make_pair(s, s));

	memset(ans, 0x3f, sizeof ans);
	ans[remap[0]] = 0;
	while(!remap.empty()) {
		auto [x, i] = *remap.begin();
		if(x == s) break;
		remap.erase(remap.begin());
		ll cur = ans[i];
		auto [l, r] = *land.lower_bound(make_pair(x, -1));
		//cerr<<"@ "<<x<<" w/ "<<cur<<nl;

		// jump to l
		if(l > x) {
			if(!remap.count(l)) remap[l] = rid++;
			int left = remap[l];
			ans[left] = min(ans[left], cur + water(x, l));
			//cerr<<" -> "<<l<<" w/ cost "<<water(x,l)<<nl;
		}

		// jump to r
		if(r > x) {
			if(!remap.count(r)) remap[r] = rid++;
			int right = remap[r];
			ans[right] = min(ans[right], cur + water(x, max((ll)x, r-d)) + t);
			//cerr<<" -> "<<r<<" w/ cost "<<water(x,max((ll)x,r-d))<<" + "<<t<<nl;
		}

		// jump over island
		int len = (l+1-x + d-1) / d * d;
		int y = x + len;
		if(y > r) {
			auto it = land.lower_bound(make_pair(y, -1));
			if(it != land.begin() && y < prev(it)->second) {
				y = prev(it)->first;
			}
			if(y > x) {
				if(!remap.count(y)) remap[y] = rid++;
				int over = remap[y];
				ans[over] = min(ans[over], cur + (ll)len/d * t);
				//cerr<<" -> "<<y<<" w/ cost "<<(ll)len/d*t<<nl;
			}
		}
	}

	cout << ans[remap[s]] << nl;

	return 0;
}

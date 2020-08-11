#include <bits/stdc++.h>
using namespace std;
#define FILENAME "binary"

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

bool good(int x) {
	ll rem = 0;
	ll mul = 1;
	ll mod = 1;
	for (int i = x; i; i /= 2) {
		mod *= 2;
	}
	for (int i = x; i; i /= 2) {
		if (i%2) rem += mul;//, rem %= mod;
		mul *= 10;//, mul %= mod;
	}
	cerr << bitset<32>(x) << " " << bitset<32>(rem) << " " << (x == rem % mod ? "!" : "") << nl;
	return x == rem % mod;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif

	int n; cin >> n;
	int cnt = 0;
	//for (int i = 1; cnt < n; i++) {
	for (int i = 1; i < 500; i++) {
		if (good(i)) {
			cnt++;
			if (cnt == n) {
				string ans;
				while (i) {
					ans.push_back(i%2 + '0');
					i /= 2;
				}
				reverse(ans.begin(), ans.end());
				cout << ans << nl;
				return 0;
			}
		}
	}

	return 0;
}

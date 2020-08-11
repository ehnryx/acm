#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
const int N = 1 << 17;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll segt[2*N];
void build() {
	for (int i = N-1; i > 0; i--) {
		segt[i] = __gcd(segt[2*i], segt[2*i+1]);
	}
}
ll query(int l, int r) {
	ll ans = 0;
	for (l += N, r += N; l < r; l /= 2, r /= 2) {
		if (l%2) ans = __gcd(ans, segt[l++]);
		if (r%2) ans = __gcd(ans, segt[--r]);
	}
	return ans;
}
int next(ll cur, int l) {
	int oldl = l;
	for (l += N+1; l > 1; l /= 2) {
		if (l%2) {
			if (segt[l] % cur) {
				break;
			}
			l++;
		}
	}
	//cerr << cur << " " << l << endl;
	if (l == 1) return INF;
	while (l < N) {
		if (segt[2*l] % cur) {
			l = 2*l;
		} else l = 2*l+1;
	}
	//cerr << l-N << endl;
	assert(l-N > oldl);
	return l-N;
}
	

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T; cin >> T;
	while (T--) {
		memset(segt, 0, sizeof segt);
		int n; cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> segt[i+N];
		}
		build();
		ll ans = 0;
		for (int i = 0; i < n; i++) {
			ll cur = segt[i+N], curi = i;
			while (curi < INF) {
				curi = next(cur, curi);
				if (curi >= n) {
					ans = max(ans, cur * (n - i));
					break;
				}
				ans = max(ans, cur * (curi - i));
				cur = __gcd(cur, segt[curi+N]);
			}
		}
		cout << ans << nl;
	}

	return 0;
}

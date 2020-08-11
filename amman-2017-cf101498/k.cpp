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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+2;
ll arr[N];
ll pref[N], suff[N];
ll p_min[N], p_max[N], s_min[N], s_max[N];
ll cur_min[2], cur_max[2];

ll get_pref_min(int i, bool ismin=true) {
	ll a = -(pref[i] - cur_max[1]);
	ll b = -(pref[i] - cur_min[1]);
	ll c = pref[i] - cur_max[0];
	ll d = pref[i] - cur_min[0];
	if (ismin) return min(min(a,b),min(c,d));
	else return max(max(a,b),max(c,d));
}

void update_pref(int i) {
	cur_min[i%2] = min(cur_min[i%2], pref[i]);
	cur_max[i%2] = max(cur_max[i%2], pref[i]);
}

ll get_suff_min(int i, bool ismin=true) {
	ll a = suff[i] - cur_min[i%2];
	ll b = suff[i] - cur_max[i%2];
	ll c = suff[i] + cur_min[(i%2)^1];
	ll d = suff[i] + cur_max[(i%2)^1];
	if (ismin) return min(min(a,b),min(c,d));
	else return max(max(a,b),max(c,d));
}

void update_suff(int i) {
	cur_min[i%2] = min(cur_min[i%2], suff[i]);
	cur_max[i%2] = max(cur_max[i%2], suff[i]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;

		pref[0] = suff[n] = 0;
		for (int i=1; i<=n; i++) {
			cin >> arr[i];
			if (i%2 == 1) pref[i] = pref[i-1] + arr[i];
			else pref[i] = pref[i-1] - arr[i];
		}
		for (int i=n; i>0; i--) {
			suff[i-1] = arr[i] - suff[i];
		}

		memset(cur_min, 0, sizeof cur_min);
		memset(cur_max, 0, sizeof cur_max);
		p_min[1] = p_max[1] = arr[1];
		cur_min[1] = cur_max[1] = arr[1];
		for (int i = 2; i <= n; i++) {
			p_min[i] = min(p_min[i-1], get_pref_min(i));
			p_max[i] = max(p_max[i-1], get_pref_min(i, false));
			update_pref(i);
		}

		memset(cur_min, 0, sizeof cur_min);
		memset(cur_max, 0, sizeof cur_max);
		s_min[n-1] = s_max[n-1] = arr[n];
		cur_min[(n-1)%2] = cur_max[(n-1)%2] = arr[n];
		for (int i = n-2; i >= 0; i--) {
			s_min[i] = min(s_min[i+1], get_suff_min(i));
			s_max[i] = max(s_max[i+1], get_suff_min(i, false));
			update_suff(i);
		}

		ll ans = 0;
		for (int i = 1; i < n; i++) {
			ans = max(ans, abs(p_max[i]-s_min[i]));
			ans = max(ans, abs(p_min[i]-s_max[i]));
		}
		cout << ans << nl;
	}

	return 0;
}

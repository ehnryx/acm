#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const ll N = 1e12, K = 1010;

vector<ll> smallps, bigps;
bool prime(ll x) {
	for (ll i = 2; i*i <= x; i++) {
		if (!(x%i)) return 0;
	}
	return 1;
}

int dp[K][7];
vector<int> ans[K][7];
void pre() {
	vector<bool> isp(K, 1);
	for (int i = 2; i*i < K; i++) {
		if (isp[i]) {
			for (int j = i*i; j < K; j += i) {
				isp[j] = 0;
			}
		}
	}
	for (int i = 2; i < K; i++) {
		if (isp[i]) smallps.push_back(i);
	}
	for (ll i = 2; i < N; i *= 2) {
		for (ll j = i;; j++) {
			if (prime(j)) {
				bigps.push_back(j);
				break;
			}
		}
	}
	reverse(bigps.begin(), bigps.end());
	memset(dp, -1, sizeof dp);
}

bool solve(int n, int cnt) {
	if (n < 0) return 0;
	if (!cnt) return n == 0;
	if (dp[n][cnt] != -1) return dp[n][cnt];
	for (int p : smallps) {
		if (solve(n - p, cnt-1)) {
			for (int i : ans[n-p][cnt-1]) {
				ans[n][cnt].push_back(i);
			}
			ans[n][cnt].push_back(p);
			return dp[n][cnt] = 1;
		}
	}
	return dp[n][cnt] = 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	pre();
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case " << tt << ": ";
		ll n; cin >> n;
		if (n < K) {
			if (!solve(n, 6)) {
				cout << "IMPOSSIBLE\n";
				goto end;
			}
			for (int i : ans[n][6]) {
				cout << i << " ";
			}
			cout << nl;
		} else {
			for (ll i = 500;; i++) {
				if (prime(n - i)) {
					cout << n - i << " ";
					n = i;
					break;
				}
			}
			solve(n, 5);
			assert(solve(n, 5));
			for (int i : ans[n][5]) {
				cout << i << " ";
			}
			cout << nl;
		}
		end:;
	}

	return 0;
}

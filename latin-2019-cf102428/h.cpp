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

const int M = 75;
const int N = M+7;
const int T = 421;
ld dp[N][N][N];
char ans[N][N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int s=M+M; s>=0; s--) {
		for(int it=0; it<T; it++) {
			for(int i=0; i<M; i++) {
				int j = s-i;
				if(j<0 || j>=M) continue;
				for(int k=M-i; k>=0; k--) {
					if(i+k == M) {
						dp[i][j][k] = 1;
						ans[i][j][k] = 'H';
					} else {
						ld hold = 1 - dp[j][i+k][0];
						ld roll = 1 - dp[j][i][0];
						for(int r=2; r<=6; r++) {
							if(i+k+r > M) roll += 1 - dp[j][i][0];
							else roll += dp[i][j][k+r];
						}
						roll /= 6;
						dp[i][j][k] = max(hold, roll);
						ans[i][j][k] = (hold > roll ? 'H' : 'C');
					}
				}
			}
		}
	}

	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int c, h, x;
		cin >> c >> h >> x;
		cout << ans[c][h][x] << nl;
	}

	return 0;
}

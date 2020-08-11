#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

const int N = 5000 + 5, C = 1000 + 5;

int w[N], h[N];
pair<int, int> dp[N][C];

int main() {
	int n, c;
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &w[i], &h[i]);
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= c; j++) {
			dp[i][j] = make_pair(-1, -1);
		}
	}
	int best = h[1];
	dp[1][w[1]] = make_pair(h[1], h[1]);
	for (int i = 2; i <= n; i++) {
		dp[i][w[i]] = make_pair(best + h[i], h[i]);
		best += h[i];
		for (int j = w[i]; j <= c; j++) {
			if (dp[i - 1][j - w[i]].first > -1) {
				int original_max = dp[i - 1][j - w[i]].second;
				int new_max = max(original_max, h[i]);
				pair<int, int> new_val = make_pair(dp[i - 1][j - w[i]].first - original_max + new_max, new_max);
				if (dp[i][j].first == -1 || new_val < dp[i][j]) {
					dp[i][j] = new_val;
				}
			}
			if (dp[i][j].first > -1 && dp[i][j].first < best) {
				best = dp[i][j].first;
			}
		}
	}
	printf("%d\n", best);
	return 0;
}

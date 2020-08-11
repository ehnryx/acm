#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int height[2001];
int length[4001];
void init() {
	memset(height, 0, sizeof(height));
	memset(length, 0, sizeof(length));
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int len;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> len;
		height[len]++;
	}

	for (int i = 1; i <= 2000; i++) {
		for (int j = i; j <= 2000; j++) {
			if (i == j) {
				length[i+j] += height[i]/2;
			} else {
				length[i+j] += min(height[i], height[j]);
			}
		}
	}

	int ans = 0;
	int diffs = 0;
	for (int i = 0; i <= 4000; i++) {
		if (length[i] > ans) {
			ans = length[i];
			diffs = 0;
		}
		if (length[i] == ans) {
			diffs++;
		}
	}
	cout << ans << " " << diffs << nl;

	return 0;
}

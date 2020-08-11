#include <bits/stdc++.h>
using namespace std;
#define FILENAME "easy"

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int HARD = 50;


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif

	int n, k; cin >> n >> k;
	vector<vector<int>> ps(n);
	for (int i = 0; i < n; i++) {
		int p; cin >> p;
		ps[i].resize(p);
		for (int j = 0; j < p; j++) {
			cin >> ps[i][j];
		}
		//sort(ps[i].begin(), ps[i].end());
	}
	vector<int> ptr(n);
	int cur = 0, selected = 0;
	int ans = 0;
	int judge = 0;
	while (1) {
		int score = ptr[judge] >= ps[judge].size() ? HARD : ps[judge][ptr[judge]];
		if (score >= cur || score == HARD) {
			//cerr << score << nl;
			ans += score;
			selected++;
			cur += score;
			if (selected == k) break;
		}
		ptr[judge]++;
		judge = (judge+1)%n;
	}
	cout << ans << nl;

	return 0;
}

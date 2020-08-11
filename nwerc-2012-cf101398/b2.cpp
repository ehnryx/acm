#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int n, k;
int no[5];
map<int, ld> dp[51][51][51][51];

ld solve(int pub) {
	if (dp[no[0]][no[1]][no[2]][no[3]].count(no[4])) {
		return dp[no[0]][no[1]][no[2]][no[3]][no[4]];
	}
	int krem = k;
	for (int i : no) {
		krem -= i;
	}
	if (krem == 0) {
		vector<int> best; int nbest = -1;
		for (int i = 0; i < 5; i++) {
			if (no[i] > nbest) {
				nbest = no[i];
				best = {i};
			} else if (no[i] == nbest) {
				best.push_back(i);
			}
		}
		for (int i : best) {
			if (i == pub) {
				return dp[no[0]][no[1]][no[2]][no[3]][no[4]] = 1.0 / best.size();
			}
		}
		return dp[no[0]][no[1]][no[2]][no[3]][no[4]] = 0;
	}
	int tot = k - krem;
	ld ans = 0;
	for (int i = 0; i < 5; i++) {
		ld prob = (ld) no[i] / tot;
		if (prob > 0) {
			no[i]++;
			ans += prob * solve(pub);
			no[i]--;
		}
	}
	return dp[no[0]][no[1]][no[2]][no[3]][no[4]] = ans;
}

void init() {
	for (auto& v : dp) {
		for (auto& vv : v) {
			for (auto& vvv : vv) {
				for (auto& d : vvv) {
					d.clear();
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	while (cin >> n >> k) {
		memset(no, 0, sizeof no);
		for (int i = 0; i < n; i++) {
			cin >> no[i];
		}
		for (int i = 0; i < n; i++) {
			init();
			cout << fixed << setprecision(2) << "pub " << i+1 << ": " << solve(i) * 100 << " %" << endl;
		}
	}

	return 0;
}

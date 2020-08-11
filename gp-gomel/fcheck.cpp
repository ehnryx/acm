#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using pii = pair<int,int>;
using ll = long long;
using ld = long double;
const char nl = '\n';

const int N = 100100;

int n, m;
vector<int> pref[N];
int amt[N*2];
int votes[N];
int nvotes[N];


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i=1; i<=n; ++i) {
		int k;
		cin >> k;
		pref[i].resize(k);
		for (auto& x : pref[i]) {
			cin >> x;
		}
	}
	int p = 0;
	while (true) {
		++p;
		bool diff = false;
		for (int i=1; i<=n; ++i) {
			pii best(-1, 1);
			for (int j=0; j<pref[i].size(); ++j) {
				best = max(best, pii(amt[pref[i][j]], -j));
			}
			nvotes[i] = pref[i][-best.second];
			diff |= (nvotes[i] != votes[i]);
			votes[i] = nvotes[i];
		}
		memset(amt, 0, sizeof amt);
		for (int i=1; i<=n; ++i) {
			amt[votes[i]]++;
			cerr << " " << votes[i];
		}
		cerr << endl;
		if (!diff) break;
	}

	cout << p << endl;

	return 0;
}

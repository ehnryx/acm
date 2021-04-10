#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

struct Score {
	ll m, b;
	ll tl;
	ll eval(ll t) {
		return b+m*(t-tl);
	}
};

struct Comp {
	ll score, last_eval;
};

const int N = 300300;

Score score[N];
Comp comp[N];
ll ans[N];
int n, w;
vector<int> weeks[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> w;
	vector<pair<ll, ll>> order;
	for (int i=0; i<N; ++i) {
		score[i].m = 1;
	}

	for (int i=1; i<=w; ++i) {
		int k;
		cin >> k;
		weeks[i].resize(k);
		for (auto& x : weeks[i]) {
			cin >> x;
		}
	}
	for (int i=1; i<=n; ++i) {
		weeks[w+1].push_back(i);
	}

	for (int wk=1; wk<=w+1; ++wk) {
		order.clear();
		for (auto& x : weeks[wk]) {
			order.emplace_back(comp[x].score, x);
		}
		sort(order.rbegin(), order.rend());
		for (auto& pp : order) {
			int ck = pp.second;
			int sc = comp[ck].score;

			ans[ck] += score[sc].eval(wk)-comp[ck].last_eval;
			//cerr << " wk " << wk << " ck " << ck << " CK adding " << score[sc].eval(wk)-comp[ck].last_eval << " LE " << comp[ck].last_eval << endl;
			comp[ck].last_eval = score[sc+1].eval(wk);
		}

		for (auto& pp : order) {
			int ck = pp.second;
			int sc = comp[ck].score;

			score[sc].b = score[sc].eval(wk);
			score[sc].tl = wk;
			score[sc].m++;
			comp[ck].score ++;
		}
	}

	cout << fixed << setprecision(10);
	for (int i=1; i<=n; ++i) {
		cout << ((ld) ans[i]-1)/w << "\n";
	}

	return 0;
}

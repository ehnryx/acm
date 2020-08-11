#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define nl '\n'

const int N = 77;
const int L = 30*30;
int dp[N][L];
int t[N], h[N];
vector<int> avail[L];
int h2[L];
int sum;
int n;

int gen() {
	memset(dp, 0, sizeof dp);
	dp[0][0] = N;
	int lmax = 0;
	for (int i=1; i<=n; ++i) {
		////cerr << " :: i=  "<< i << endl;
		int nxt_lmax = 0;
		for (int j=0; j<=lmax && j+t[i]<L; ++j) {
			dp[i][j] = dp[i-1][j];
		}
		for (int j=0; j<=lmax && j+t[i]<L; ++j) {
			if (!dp[i-1][j]) continue;
			if (dp[i][j+t[i]]) continue;
			//cerr << " UPD dp " << i << " " << j+t[i] << " W " << t[i] << "\n";
			nxt_lmax = max(nxt_lmax, j+t[i]);
			dp[i][j+t[i]] = i;
		}
		lmax = nxt_lmax;
	}

	lmax = min(lmax, L-1);
	int av[N];
	for (int j=1; j<=lmax; ++j) {
		avail[j].clear();
		if (dp[n][j] == 0) continue;
		for (int k=0; k<N; ++k) {
			av[k] = 1;
		}
		int q = j;
		while (q) {
			assert(dp[n][q]);
			av[dp[n][q]] = 0;
			q -= t[dp[n][q]];
		}
		h2[j] = 0;
		for (int k=1; k<=n; ++k) {
			if (av[k]) {
				avail[j].push_back(k);
				h2[j] = max(h2[j], h[k]);
			}
		}
	}
	avail[0].clear();
	for (int i=1; i<=n; ++i) {
		avail[0].push_back(i);
	}
	return lmax;
}

int dp2[N][L];

ll gen2(const vector<int>& inds, int t1, int h1, int mh2) { // return minimum length
	memset(dp2, 0, sizeof dp2);
	dp2[0][0] = N;
	int lmax = 0;
	int lasti = 0;
	int mysum = 0;
	for (auto& i : inds) {
		//cerr << "    SOL " << i << endl;
		mysum += t[i];
		int nxt_lmax = 0;
		for (int j=0; j<=lmax && j+t[i]<L; ++j) {
			dp2[i][j] = dp2[lasti][j];
		}
		for (int j=0; j<=lmax && j+t[i]<L; ++j) {
			if (!dp2[lasti][j]) continue;
			if (dp2[i][j+t[i]]) continue;
			nxt_lmax = max(nxt_lmax, j+t[i]);
			dp2[i][j+t[i]] = i;
			//cerr << "    DP2 " << i << " " << j+t[i] << " = " << i << endl;
		}
		lmax = nxt_lmax;
		lasti = i;
	}

	ll ans = 1e18;
	int av[N];
	for (int j=1; j<=lmax; ++j) {
		if (dp2[lasti][j] == 0) continue;
		for (int i=0; i<N; ++i) {
			av[i] = 0;
		}
		//cerr << "  INDS ";
		for (auto& q : inds) {
			av[q] = 1;
			//cerr << " " << q;
		}
		//cerr << endl;
		int q = j;
		while (q) {
			assert(dp2[lasti][q]);
			av[dp2[lasti][q]] = 0;
			//cerr << " TAKE " << dp2[lasti][q] << " :: " << t[dp2[lasti][q]] << " :: " << q << " :: " << lasti << "," << q << endl;
			q -= t[dp2[lasti][q]];
		}
		int h3 = 0;
		for (int k=1; k<=n; ++k) {
			if (av[k]) {
				//cerr << "  :: " << k << " -> " << h[k] << endl;
				h3 = max(h3, h[k]);
			}
		}
		int t2 = j;
		int t3 = mysum-j;
		if (t1 == 0 || t2 == 0 || t3 == 0) continue;
		//cerr << " t1 " << t1 << " t2 " << t2 << " t3 " << t3 << " H1 " << h1 << " h2 " << mh2 << " h3 " << h3 << " -> " << max(max(t3, t2), t1)*(h1+mh2+h3) << endl;
		ans = min(ans, max(max(t3, t2), t1)*(ll) (h1+mh2+h3));
	}

	return ans;
}


struct book {
	int i, t, h;
	bool operator< (const book& o) const {
		return t < o.t;
	}
};

void solve() {
	cin >> n;
	vector<pii> v;
	sum = 0;
	for (int i=1; i<=n; ++i) {
		int th, tt;
		cin >> th >> tt;
		sum += tt;
		v.emplace_back(th, tt);
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	for (int i=0; i<v.size(); ++i) {
		////cerr << " " << i+1 << " :: " << v[i].first << " " << v[i].second << endl;
		h[i+1] = v[i].first;
		t[i+1] = v[i].second;
	}

	int med = sum/3;
	int lo = max(0, med-60);
	int hi = min(L-1, med+60);

	ll ans = 1e18;
	int lmax = gen();
	for (int l=lo; l<=hi; ++l) {
		if (dp[n][l]) {
			//cerr << " L = " << l << endl;
			int tsum = 0;
			for (auto& q : avail[l]) {
				tsum += t[q];
			}
			ll mxv = gen2(avail[l], l, h[1], h2[l]);
			ans = min(ans, mxv);
		}
	}
	cout << ans << "\n";
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T;
	cin >> T;
	while(T--) {
		solve();
	}

	return 0;
}

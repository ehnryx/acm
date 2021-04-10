#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());


const int MAXN=11;
int T, n, m;
int c[MAXN];
int d[MAXN];
int C[MAXN][4]; //projects 
int D[MAXN][3]; //specializations 

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	cin >> T;
	for(int it = 1; it<=T;it++) {
		cin >> n >> m;
		vector<vector<int>> bms(n);
		for(int i=0;i<n;i++) {
			cin >> c[i];
			for(int j=0;j<c[i];j++) {
				cin >> C[i][j];
			}
		}
		for(int i=0;i<m;i++) {
			cin >> d[i];
			for(int j=0;j<d[i];j++) {
				cin >> D[i][j];
			}
		}
		auto f = [&](set<int> s, int bm) {
			for(int k=0;k<n;k++) {
				bool pos = true;
				for(int h=0;h<c[k];h++) {
					if (!s.count(C[k][h])) pos = false;
				}
				if (pos) {
					 //cerr << "ADDING " << bitset<10>(bm) << " " << k <<endl;
					 bms[k].push_back(bm);
				}
			}
		};
		for(int i=0;i<m;i++) {
			// singleton
			int bm = (1<<i);
			set<int> first;
			for(int j=0;j<d[i];j++) {
				first.insert(D[i][j]);
			}
			//cerr << i << " has "; for(int j: first) cerr << j << " "; cerr <<endl;
			f(first, bm);
			for(int j=i+1;j<m;j++) {
				set<int> second = first;
				for(int h=0;h<d[j];h++) {
					second.insert(D[j][h]);
				}
				//cerr << i << j << " has "; for(int h: second) cerr << h << " "; cerr <<endl;
				bm ^= (1<<j);
				f(second, bm);
				for(int k=j+1;k<m;k++) {
					set<int> third = second;
					for(int h=0;h<d[k];h++) {
						third.insert(D[k][h]);
					}
					bm ^= (1<<k);
					f(third, bm);
					bm ^= (1<<k);
				}
				bm ^= (1<<j);
			}
		}
		int dp[MAXN][1<<11];
		int maxbm = (1<<m)-1;
		memset(dp, 0, sizeof dp);
		/*
		for(int i=0;i<n;i++) {
			cerr << "BITMASKS FOR " << i <<endl;
			for(int bm: bms[i]) {
				cerr << bitset<10>(bm) << endl;
			}
		}
		*/
		for(int i=0;i<n;i++) {
			for(int curbm=0;curbm<=maxbm;curbm++) {
				dp[i+1][curbm] = dp[i][curbm];
			}
			for(int curbm=0;curbm<=maxbm;curbm++) {
//				if (dp[i][curbm]) cerr << i << " " << bitset<10>(curbm) << " " << dp[i][curbm] <<endl;
				for(int bm: bms[i]) {
					if (bm & curbm) continue;
					dp[i+1][bm | curbm] = max(dp[i+1][bm|curbm], 1+dp[i][curbm]);
				}
			}
		}
		int ans = 0;
		for(int i=0;i<=maxbm;i++) {
//			if (dp[n][i]) cerr << n << " " << bitset<10>(i) << " " << dp[n][i] <<endl;
			ans = max(ans, dp[n][i]);
		}

		cout << "Case #" << it << ": " << ans <<endl;
	}
	

	return 0;
}

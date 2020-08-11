#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	int a[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i] %= m;
	}

	int block_sz = max(1, (int)(sqrt(n) / exp(1)));
	int block_num = (n-1) / block_sz + 1;
	int pref[block_num][block_sz+1][m];
	int suff[block_num][block_sz+1][m];
	int group[block_num][block_num][m];
	int cur[n], other[n];

	for (int i = 0; i < block_num; i++) {
		int start = i * block_sz;
		memset(cur, 0, sizeof cur);
		memset(other, 0, sizeof other);
		cur[0] = 1;
		other[0] = 1;

		int end = min(block_sz, n-start);
		for (int j = 0; j < end; j++) {
			for (int k = 0; k < m; k++) {
				pref[i][j][(k+a[start+j])%m] = (cur[(k+a[start+j])%m] + cur[k]) % MOD;
			}
			for (int k = 0; k < m; k++) {
				suff[i][j][(k+a[start+end-1-j])%m] = (other[(k+a[start+end-1-j])%m] + other[k]) % MOD;
			}
			for (int k = 0; k < m; k++) {
				cur[k] = pref[i][j][k];
				other[k] = suff[i][j][k];
			}
		}
	}

	for (int i = 0; i < block_num; i++) {
		memset(cur, 0, sizeof cur);
		cur[0] = 1;
		for (int j = i; j < block_num; j++) {
			memset(group[i][j], 0, sizeof group[i][j]);
			int end = min(block_sz, n - j*block_sz);
			for (int x = 0; x < m; x++) {
				for (int y = 0; y < m; y++) {
					group[i][j][(x+y)%m] = (group[i][j][(x+y)%m] + (ll) cur[x] * pref[j][end-1][y] % MOD) % MOD;
				}
			}
			for (int k = 0; k < m; k++) {
				cur[k] = group[i][j][k];
			}
		}
	}

#ifdef DEBUG
	cout << "--- SIZES ---" << endl;
	cout << "block_num: " << block_num << endl;
	cout << "block_sz: " << block_sz << endl;
	cout << endl;

	cout << "------- pref[block_num][block_sz][m]" << endl;
	for (int i = 0; i < block_num; i++) {
		for (int j = 0; j < block_sz; j++) {
			cout << i << ',' << j << ": ";
			for (int k = 0; k < m; k++) {
				cout << pref[i][j][k] << " ";
			}
			cout << endl;
		}
	}
	cout << endl;

	cout << "------- suff[block_num][block_sz][m]" << endl;
	for (int i = 0; i < block_num; i++) {
		for (int j = 0; j < block_sz; j++) {
			cout << i << ',' << j << ": ";
			for (int k = 0; k < m; k++) {
				cout << suff[i][j][k] << " ";
			}
			cout << endl;
		}
	}
	cout << endl;

	cout << "------- group[block_num][block_num][m]" << endl;
	for (int i = 0; i < block_num; i++) {
		for (int j = i; j < block_num; j++) {
			cout << i << ',' << j << ": ";
			for (int k = 0; k < m; k++) {
				cout << group[i][j][k] << " ";
			}
			cout << endl;
		}
	}
	cout << endl;
#endif

	int queries, left, right;
	cin >> queries;
	for (int i = 0; i < queries; i++) {
		memset(cur, 0, sizeof cur);
		cur[0] = 1;
		cin >> left >> right;
		left--; right--;
		int shift;
		int start = left / block_sz;
		int end = right / block_sz;
		//cerr << "start: " << start << "  end: " << end << endl;

		if (start != end) {
			//cerr << "LARGE" << endl;
			if (start + 1 <= end - 1) {
				//cerr << "Get group " << start+1 << " " << end-1 << endl;
				for (int k = 0; k < m; k++) {
					cur[k] = group[start+1][end-1][k];
				}
			}

			memset(other, 0, sizeof other);
			shift = (start+1) * block_sz - left - 1;
			//cerr << "get suff " << start << " " << shift << endl;
			for (int x = 0; x < m; x++) {
				for (int y = 0; y < m; y++) {
					other[(x+y)%m] = (other[(x+y)%m] + (ll) cur[x] * suff[start][shift][y] % MOD) % MOD;
				}
			}
			for (int k = 0; k < m; k++) {
				cur[k] = other[k];
			}

			memset(other, 0, sizeof other);
			shift = right - (end * block_sz);
			//cerr << "get pref " << end << " " << shift << endl;
			for (int x = 0; x < m; x++) {
				for (int y = 0; y < m; y++) {
					other[(x+y)%m] = (other[(x+y)%m] + (ll) cur[x] * pref[end][shift][y] % MOD) % MOD;
				}
			}
			for (int k = 0; k < m; k++) {
				cur[k] = other[k];
			}
		}

		else {
			//cerr << "SMALL" << endl;
			for (int i = left; i <= right; i++) {
				for (int k = 0; k < m; k++) {
					other[(k+a[i])%m] = (cur[(k+a[i])%m] + cur[k]) % MOD;
				}
				for (int k = 0; k < m; k++) {
					cur[k] = other[k];
				}
			}
		}

		cout << cur[0] << nl;
		//cerr << endl;
	}

	return 0;
}

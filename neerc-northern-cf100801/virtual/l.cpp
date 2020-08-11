#include <bits/stdc++.h>
using namespace std;
#define FILENAME "lucky"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 110;

int r, c;
int grid[N][N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);

  cin >> r >> c;
	for (int i=1; i<=r; ++i) {
		for (int j=1; j<=c; ++j) {
			cin >> grid[i][j];
		}
	}

  int ans = 0;
	for (int i=1; i<=r; ++i) {
		for (int j=1; j<=c; ++j) {
			int amt = 4;
			for (int k=1; k<i; ++k) {
				if (grid[k][j] >= grid[i][j]) {
					amt--;
					break;
				}
			}
			for (int k=r; k>i; --k) {
				if (grid[k][j] >= grid[i][j]) {
					amt--;
					break;
				}
			}
			for (int k=1; k<j; ++k) {
				if (grid[i][k] >= grid[i][j]) {
					amt--;
					break;
				}
			}
			for (int k=c; k>j; --k) {
				if (grid[i][k] >= grid[i][j]) {
					amt--;
					break;
				}
			}
      ans += amt;
		}
	}
	cout << ans << endl;


	return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 503;
int dp[N][N][N];
void init() {
	memset(dp, -1, sizeof dp);
}

int diff[7];
vector<int> idx;

int solve(int a, int b, int c) {
	if (dp[a][b][c] != -1) return dp[a][b][c];
	if (!a && !b && !c) return 0;

	int remainder = (a*idx[0] + b*idx[1] + c*idx[2]) % 7;
	int res = 0;
	if (a>0) res = max(res, solve(a-1, b, c));
	if (b>0) res = max(res, solve(a, b-1, c));
	if (c>0) res = max(res, solve(a, b, c-1));
	return dp[a][b][c] = res + !remainder;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int n;
	cin >> n;

	vector<int> shift;
	shift.push_back(0);
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		if (stoi(s) % 1111111 != 0) {
			string best = s;
			int id = 0;
			for (int j = 0; j < 7; j++) {
				if (s > best) {
					best = s;
					id = j;
				}
				rotate(s.begin(), s.begin()+1, s.end());
			}
			shift.push_back(id);
		}
	}
	shift.push_back(0);

	memset(diff, 0, sizeof diff);
	for (int i = 1; i < shift.size(); i++) {
		int id = shift[i]-shift[i-1];
		if (id < 0) id += 7;
		diff[id]++;
	}

	int ans = 0;
	diff[0] = 0;
	for (int i = 1; i <= 3; i++) {
		int d = min(diff[i], diff[7-i]);
		ans += d;
		diff[i] -= d;
		diff[7-i] -= d;
		idx.push_back(diff[i] ? i : 7-i);
	}

	int sum = diff[idx[0]] + diff[idx[1]] + diff[idx[2]];
	int groups = solve(diff[idx[0]], diff[idx[1]], diff[idx[2]]);
	cout << ans + sum - groups << nl;

	return 0;
}

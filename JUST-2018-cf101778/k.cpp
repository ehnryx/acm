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

struct Submission {
	int problem, team, ac, t;
	Submission() {
		t = INF;
		team = -1;
	}
	Submission(int x, int y, int z, int s): 
		problem(x), team(y), ac(z), t(s) {}
	bool operator < (const Submission& v) const { 
		return t < v.t; 
	}
};

const int N = 31;
Submission ITMO, UBC;
Submission first_solve[N];
int tries[N][N];
bool solve[N][N];

void init() {
	memset(tries, 0, sizeof tries);
	memset(solve, 0, sizeof solve);
	fill(first_solve, first_solve+N, Submission());
	ITMO = UBC = Submission();
	UBC.t = -INF;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		init();
		int n, m, k;
		cin >> n >> m >> k;

		string t;
		int x, y, z;
		for (int i = 1; i <= k; i++) {
			cin >> x >> y >> z >> t;
			Submission cur(x, y, z, 100*stoi(t.substr(0,3)) + stoi(t.substr(4,2)));
			if (cur.ac) {
				ITMO = min(ITMO, cur);
				UBC = max(UBC, cur);
				first_solve[cur.problem] = min(first_solve[cur.problem], cur);
				solve[cur.team][cur.problem] = true;
			} else {
				tries[cur.team][cur.problem]++;
			}
		}

		int paul = -1;
		int ThePaul = -1;
		int jason = -1;
		int TheJason = -1;
		for (int i = 1; i <= m; i++) {
			int one_shot = 0;
			for (int j = 1; j <= n; j++) {
				if (solve[i][j]) {
					if (tries[i][j] == 0) {
						one_shot++;
					}
					if (tries[i][j] > paul) {
						paul = tries[i][j];
						ThePaul = i;
					}
				}
			}
			if (one_shot > jason) {
				jason = one_shot;
				TheJason = i;
			}
		}

		for (int i = 1; i <= n; i++) {
			cout << first_solve[i].team << " ";
		}
		cout << nl;

		assert(ITMO.team > 0);
		assert(UBC.team > 0);
		assert(TheJason > 0);
		assert(ThePaul > 0);

		cout << ITMO.team << " ";
		cout << UBC.team << " ";
		cout << TheJason << " ";
		cout << ThePaul << " ";
		cout << nl;
	}

	return 0;
}

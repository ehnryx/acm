#include <bits/stdc++.h>
using namespace std;
#define problem_name "java2016"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(problem_name ".in", "r", stdin);
	freopen(problem_name ".out", "w", stdout);
#endif

	int n;
	cin >> n;

	if (n == 0) {
		cout << "? / ? / ?" << nl;
	}

	else {
		cout << "i = ? max ?" << nl;
		for (char c = 'i'+1; c <= 'z'; c++) {
			cout << (char)c << " = " << (char)(c-1) << " max " << (char)(c-1) << nl;
		}
		cout << "a = (z max z) / z" << nl;
		cout << "b = a + a" << nl;
		for (char c = 'a'+2; c <= 'h'; c++) {
			cout << (char)c << " = b * " << (char)(c-1) << nl;
		}
		vector<char> ans;
		for (int i=0; i<8; i++) {
			if (1<<i & n) {
				ans.push_back((char)(i+'a'));
			}
		}
		for (int i=0; i<ans.size(); i++) {
			cout << ans[i] << "+\n"[i+1==ans.size()];
		}
	}

	return 0;
}

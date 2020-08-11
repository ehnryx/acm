#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const ll INF = 0x3f3f3f3f;

const vector<string> ans = {
	"Typically Otaku",
	"Eye-opener",
	"Young Traveller",
	"Excellent Traveller",
	"Contemporary Xu Xiake"};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T; cin >> T;
	while (T--) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		int k = (bool) a + (bool) b + (bool) c + (bool) d;
		cout << ans[k] << nl;
	}

	return 0;
}

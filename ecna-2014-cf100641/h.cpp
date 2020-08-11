#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const ll K = 12*60*60;
const int MAGIC = 3960/2;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T; cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		int a, b; string k; cin >> a >> k >> b;
		if (k[0] == 't') {
			b--;
		}
		ll target = K*(a + (360 / 12) * (b%12)), t2 = K*(a - 360 + (360 / 12) * (b%12));
		int h, m, s;
		bool shit = 1;
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				if (!i && !j && k[0] != 't') continue;
				ll score = (360*12*60 - 360*60) * i + (360*12 - 360) * j;
				if (abs(score - target) <= MAGIC || abs(score - t2) <= MAGIC) {
					h = b;
					m = i;
					s = j;
					shit = 0;
					break;
				}
			}
		}
		if (!shit) goto out;
		if (k[0] == 't') {
			b = (b+11)%12;
		} else {
			b = (b+1)%12;
		}
		//cerr << a << " " << b << endl;
		target = K*(a + (360 / 12) * (b%12)); t2 = K*(a - 360 + (360 / 12) * (b%12));
		//cerr << target << endl;
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				ll score = (360*12*60 - 360*60) * i + (360*12 - 360) * j;
				if (abs(score - target) <= MAGIC || abs(score - t2) <= MAGIC) {
					h = b;
					m = i;
					s = j;
					shit = 0;
					break;
				}
			}
		}
out:
		cout << "Case " << tt << ": " << (h ? h : 12) << ":" << setw(2) << setfill('0') << m << ":" << setw(2) << setfill('0') << s << '\n';
	}

	return 0;
}

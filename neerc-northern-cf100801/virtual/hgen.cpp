#include <bits/stdc++.h>
using namespace std;
#define FILENAME REPLACE

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 3003000;

map<int, int> mp;

string s[N];

int pw[3000];
void setup() {
	pw[0] = 1;
	for (int i=1; i<3000; ++i) {
		pw[i] = pw[i-1]*31;
	}
}

int hsh(const string& s, int start=0) {
	int ans = 0;
	int k = s.size();
	for (int i=start, j=0; j<s.size(); ++i, ++j) {
			ans += s[k-1-j]*pw[i];
	}
	return ans;
}

inline char rchr() {
	int x = rand()%52;
	if (x < 26) {
		return x+'a';
	}
	return x+'A'-26;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	setup();
	/*
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
	*/
	
	for (int i=1; i<N; ++i) {
		string z;
		for (int j=0; j<9; ++j) {
			z += rchr();
		}
		int ha = hsh(z);
		if (mp.count(ha)) {
			cerr << " hash collision " << ha << " " << z << " : " << s[mp[ha]]<< endl;
			continue;
		}

		s[i] = z;
		mp[ha] = i;

		int hb = hsh(z, 9);
		int need = -hb;
		if (mp.count(need)) {
			cout << " ! " << z + s[mp[need]] << endl;
		}
	}

	return 0;
}

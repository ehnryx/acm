#include <bits/stdc++.h>
using namespace std;

inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}

#define ll long long

struct Wall {
	vector<int> wallheight; // height of wall
	ll volume; // answer
	set<int> left; // index
	set<int> right; // -index
	int maxheight; // maximum height of water
	Wall(int n) {
		wallheight.resize(n+1);
	}
	void clear(int len) {
		volume = 0;
		maxheight = 0;
		left.clear();
		right.clear();
		memset(&wallheight[1], 0, len*sizeof(wallheight[0]));
		left.insert(1);
		right.insert(-len);
	}

	void grow(int i, int change) {
		int prev;
		int oldwall = wallheight[i];
		wallheight[i] += change;
		auto leftend = left.end(); leftend--;
		auto rightend = right.end(); rightend--;
		if (i < (*leftend)) {
			// left side
			auto it = left.lower_bound(i);
			if ((*it) == i) {
				it = left.erase(it);
				prev = oldwall;
			}
			else {
				it--;
				prev = wallheight[*it];
				it++;
			}
			if (wallheight[i] <= prev) {
				volume -= change;
			}
			else {
				volume -= prev-oldwall;
				while (it != left.end()) {
					volume += 1LL * (min(wallheight[i], wallheight[*it])-prev) * ((*it)-i-1);
					if (wallheight[*it] > wallheight[i])
						break;
					prev = wallheight[*it];
					it = left.erase(it);
				}
				left.insert(i);
				if (wallheight[i] > maxheight) {
					maxheight = wallheight[i];
					right.insert(-i);
				}
			}
		}
		else if (i > -(*rightend)) {
			// right side
			auto it = right.lower_bound(-i);
			if ((*it) == -i) {
				it = right.erase(it);
				prev = oldwall;
			}
			else {
				it--;
				prev = wallheight[-(*it)];
				it++;
			}
			if (wallheight[i] <= prev) {
				volume -= change;
			}
			else {
				volume -= prev-oldwall;
				while (it != right.end()) {
					volume += 1LL * (min(wallheight[i], wallheight[-(*it)])-prev) * (i+(*it)-1);
					if (wallheight[-(*it)] > wallheight[i])
						break;
					prev = wallheight[-(*it)];
					it = right.erase(it);
				}
				right.insert(-i);
				if (wallheight[i] > maxheight) {
					maxheight = wallheight[i];
					left.insert(i);
				}
			}
		}
		else {
			// center
			if (wallheight[i] <= maxheight) {
				volume -= change;
			}
			else {
				volume -= (maxheight-oldwall);
				left.insert(i);
				right.insert(-i);
				maxheight = wallheight[i];
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	Wall weed(100000);
	int n, queries;
	int index, change;
	char type;
	int T;
	//cin >> T;
	read(T);
	while (T--) {
		//cin >> n >> queries;
		read(n); read(queries);
		weed.clear(n);
		for (int i = 1; i <= n; i++) {
			//cin >> change;
			read(change);
			weed.grow(i, change);
		}
		for (int i = 0; i < queries; i++) {
			//cin >> type;
			while ((type = get()) != 'U' && type != 'P');
			if (type == 'P') {
				cout << weed.volume << '\n';
			}
			else {
				//cin >> index >> change;
				read(index); read(change);
				weed.grow(index, change);
			}
		}
	}

	return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int BIG = 65;
const map<string, int> m = {
	{"Russia", 0},
	{"Sweden", 1},
	{"Finland", 2},
	{"NA", 3}
};

struct team {
	int id;
	int val[5];
	set<int> won;
	team() { memset(val, 0, sizeof val); }
};

int two(const team& a, const team& b) {
	if (a.id == 0) {
		return a.won.count(b.id) ? 1 : 2;
	} else return a.won.count(b.id) ? 2 : 1;
}

int three(vector<team> teams, bool b) {
	for (int i = 0; i < 5; i++) {
		sort(teams.begin(), teams.end(), [&](const team& a, const team& b) {
			return a.val[i] > b.val[i];
		});
		while (teams[b].val[i] != teams.back().val[i]) {
			team t = teams.back(); teams.pop_back();
			if (t.id == 0) return 2;
		}
		if (teams.size() <= 1+b) return 1;
		if (teams.size() == 2) {
			if (teams[0].val[i] != teams[1].val[i]) {
				return teams[0].id == 0 ? 1 : 2;
			} else return two(teams[0], teams[1]);
		}
		if (teams[0].val[i] != teams[1].val[i]) {
			if (teams[0].id == 0) return 1;
			if (b) return two(teams[1], teams[2]);
			else return 2;
		}
	}
	return 3;
}

int calc(vector<team> teams) {
	for (int i = 0; i < 5; i++) {
		sort(teams.begin(), teams.end(), [&](const team& a, const team& b) {
			return a.val[i] > b.val[i];
		});
		while (teams[1].val[i] != teams.back().val[i]) {
			team t = teams.back(); teams.pop_back();
			if (t.id == 0) return 2;
		}
		if (teams.size() <= 2) return 1;
		if (teams.size() == 3) {
			if (teams[0].val[i] != teams[1].val[i]) {
				return teams[0].id == 0 ? 1 : two(teams[1], teams[2]);
			} else return three(teams, 1);
		}
		if (teams[0].val[i] != teams[1].val[i]) {
			if (teams[0].id == 0) {
				return 1;
			} else {
				teams.erase(teams.begin());
				return three(teams, 0);
			}
		}
	}
	return 3;
}

void upd(team& a, team& b, int ga, int gb, bool ot) {
	for (int t = 0; t < 2; t++) {
		if (ga > gb) {
			a.val[0] += 2;
			a.val[1]++;
			if (!ot) a.val[2]++;
			a.won.insert(b.id);
		} else {
			if (ot) a.val[0]++;
		}
		a.val[3] += ga - gb;
		a.val[4] += ga;
		swap(a, b);
		swap(ga, gb);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<team> teams(4);
	for (int i = 0; i < 4; i++) {
		teams[i].id = i;
	}

	string s;
	for (int i = 0; i < 5; i++) {
		getline(cin, s);
		istringstream in(s);
		string ta, tb;
		int ga, gb;
		in >> ta >> tb >> ga >> gb;
		bool ot = bool(in >> s);
		team& a = teams[m.at(ta)];
		team& b = teams[m.at(tb)];
		upd(a, b, ga, gb, ot);
	}

	/*
	for (int i = 0; i < 4; i++) {
		const team& t = teams[i];
		cerr << teams[i].id << " " << teams[i].score() << " " << teams[i].wins << " " << teams[i].pwins << " " << teams[i].gdiff << " " << teams[i].goals << nl;
	}*/
	string ta, tb; cin >> ta >> tb;
	int x = m.at(ta), y = m.at(tb);

	bool can = 0, cannot = 0;
	for (int ga = 0; ga < BIG; ga++) {
		for (int gb = 0; gb < BIG; gb++) {
			if (ga == gb) continue;
			for (int ot = 0; ot < 2; ot++) {
				if (ot && abs(ga-gb) != 1) break;
				vector<team> res = teams;
				team& a = res[x];
				team& b = res[y];
				upd(a, b, ga, gb, ot);
				int ans = calc(res);
				can |= ans & 1;
				cannot |= ans & 2;
			}
		}
	}
	assert(can || cannot);
	if (can && !cannot) {
		puts("Already in playoff!");
	} else if (!can && cannot) {
		puts("No chance");
	} else puts("Believe in playoff!");

	return 0;
}

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
	int wins, pwins, gdiff, goals, otl;
	set<int> won;
	int score() const {
		return 2*wins + otl;
	}
};

bool by_score(const team& a, const team& b) {
	return a.score() > b.score();
}
bool by_wins(const team& a, const team& b) {
	return a.wins > b.wins;
}
bool by_pwins(const team& a, const team& b) {
	return a.pwins > b.pwins;
}
bool by_gdiff(const team& a, const team& b) {
	return a.gdiff > b.gdiff;
}
bool by_goals(const team& a, const team& b) {
	return a.goals > b.goals;
}

int two(const team& a, const team& b) {
	if (a.id == 0) {
		return a.won.count(b.id) ? 1 : 2;
	} else return a.won.count(b.id) ? 2 : 1;
}

int three(vector<team> teams, bool b) {
	sort(teams.begin(), teams.end(), by_score);
	while (teams.back().score() != teams[b].score()) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 1+b) return 1;
	if (!b && teams.size() == 2) return two(teams[0], teams[1]);
	if (teams[0].score() != teams[1].score()) return b ? two(teams[1], teams[2]) : 2;

	sort(teams.begin(), teams.end(), by_wins);
	while (teams.back().wins != teams[b].wins) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 1+b) return 1;
	if (!b && teams.size() == 2) return two(teams[0], teams[1]);
	if (teams[0].wins != teams[1].wins) return b ? two(teams[1], teams[2]) : 2;

	sort(teams.begin(), teams.end(), by_pwins);
	while (teams.back().pwins != teams[b].pwins) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 1+b) return 1;
	if (!b && teams.size() == 2) return two(teams[0], teams[1]);
	if (teams[0].pwins != teams[1].pwins) return b ? two(teams[1], teams[2]) : 2;

	sort(teams.begin(), teams.end(), by_gdiff);
	while (teams.back().gdiff != teams[b].gdiff) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 1+b) return 1;
	if (!b && teams.size() == 2) return two(teams[0], teams[1]);
	if (teams[0].gdiff != teams[1].gdiff) return b ? two(teams[1], teams[2]) : 2;

	sort(teams.begin(), teams.end(), by_goals);
	while (teams.back().goals != teams[b].goals) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 1+b) return 1;
	if (!b && teams.size() == 2) return two(teams[0], teams[1]);
	if (teams[0].goals != teams[1].goals) return b ? two(teams[1], teams[2]) : 2;

	return 3;
}

int calc(vector<team> teams) {
	sort(teams.begin(), teams.end(), by_score);
	while (teams.back().score() != teams[1].score()) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 2) return 1;
	if (teams.size() == 3) return three(teams, 1);
	assert(teams.size() == 4);
	if (teams[0].score() != teams[1].score()) {
		teams.erase(teams.begin());
		return three(teams, 0);
	}
	sort(teams.begin(), teams.end(), by_wins);
	while (teams[1].wins != teams.back().wins) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 2) return 1;
	if (teams.size() == 3) return three(teams, 1);
	if (teams[0].wins != teams[1].wins) {
		teams.erase(teams.begin());
		return three(teams, 0);
	}
	sort(teams.begin(), teams.end(), by_pwins);
	while (teams[1].pwins != teams.back().pwins) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 2) return 1;
	if (teams.size() == 3) return three(teams, 1);
	if (teams[0].pwins != teams[1].pwins) {
		teams.erase(teams.begin());
		return three(teams, 0);
	}
	sort(teams.begin(), teams.end(), by_gdiff);
	while (teams[1].gdiff != teams.back().gdiff) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 2) return 1;
	if (teams.size() == 3) return three(teams, 1);
	if (teams[0].gdiff != teams[1].gdiff) {
		teams.erase(teams.begin());
		return three(teams, 0);
	}
	sort(teams.begin(), teams.end(), by_goals);
	while (teams[1].goals != teams.back().goals) {
		team t = teams.back(); teams.pop_back();
		if (t.id == 0) return 2;
	}
	if (teams.size() <= 2) return 1;
	if (teams.size() == 3) return three(teams, 1);
	if (teams[0].goals != teams[1].goals) {
		teams.erase(teams.begin());
		return three(teams, 0);
	}
	return 3;
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
		for (int t = 0; t < 2; t++) {
			if (ga > gb) {
				a.wins++;
				a.won.insert(b.id);
				if (!ot) a.pwins++;
			} else {
				if (ot) a.otl++;
			}
			a.gdiff += ga - gb;
			a.goals += ga;
			swap(a, b);
			swap(ta, tb);
			swap(ga, gb);
		}
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
				for (int t = 0; t < 2; t++) {
					if (ga > gb) {
						a.wins++;
						a.won.insert(b.id);
						if (!ot) a.pwins++;
					} else {
						if (ot) a.otl++;
					}
					a.gdiff += ga - gb;
					a.goals += ga;
					swap(a, b);
					swap(ta, tb);
					swap(ga, gb);
				}
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

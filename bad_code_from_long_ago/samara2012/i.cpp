#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Memo {
	int id;
	int day;
	int cost;
	Memo(int id, int cost, int day) {
		this->id = id;
		this->cost = cost;
		this->day = day;
	}
	bool operator < (const Memo& other) const {
		return this->day < other.day;
	}
};

struct Exam {
	int id;
	int cost;
	int day;
	Exam (const Memo& memo) {
		this->id = memo.id;
		this->cost = memo.cost;
		this->day = memo.day;
	}
	int value() const {
		return cost-day;
	}
	bool operator < (const Exam& other) const {
		return other.value() > this->value();
	}
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	vector<Memo> memo;
	int n, c, d;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> d >> c;
		memo.push_back(Memo(i,c,d));
	} sort(memo.begin(), memo.end());

	int pos = 0;
	priority_queue<Exam> next;
	int ans[n];
	for (int t = 1; !next.empty() || pos < n; t++) {
		while (pos < n && memo[pos].day == t) {
			next.push(Exam(memo[pos]));
			pos++;
		}
		if (!next.empty()) {
			ans[next.top().id] = t;
			next.pop();
		}
	}

	for (int a: ans) {
		cout << a << " ";
	} cout << nl;

	return 0;
}

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

#define OPEN 1
#define ROOM 2
#define CLOSE 3
struct Point {
	int index;
	int a, b;
	int type;
	Point (int a, int t) {
		this->a = a;
		this->type = t;
	}
	Point (int i, int a, int t) {
		this->a = a;
		this->type = t;
		this->index = i;
	}
	Point (int i, int a, int b, int t) {
		this->a = a;
		this->b = b;
		this->type = t;
		this->index = i;
	}
	bool operator < (const Point& other) const {
		if (this->a == other.a) return this->type < other.type;
		else return this->a < other.a;
	}
};

struct BIT {
	int size;
	vector<int> freq;
	BIT(int n) {
		size = n;
		freq.resize(n+1);
		memset(&freq[0], 0, (n+1)*sizeof(freq[0]));
	}
	void insert(int x, int cnt=1) {
		for ( ; x <= size; x += x & -x)
			freq[x] += cnt;
	}
	int query(int x) {
		int sum = 0;
		for ( ; x > 0; x -= x & -x) 
			sum += freq[x];
		return sum;
	}
	int query(int xl, int xr) {
		return query(xr) - query(xl-1);
	}
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	vector<Point> points;
	int n;
	cin >> n;
	int roomsize[n];
	pair<int,int> interval[n];
	for (int i = 0; i < n; i++) {
		cin >> roomsize[i];
		points.push_back(Point(i, roomsize[i], ROOM));
	}
	for (int i = 0; i < n; i++) {
		cin >> interval[i].first >> interval[i].second;
		points.push_back(Point(i, interval[i].first, interval[i].second, OPEN));
		points.push_back(Point(i, interval[i].second, interval[i].first, CLOSE));
	}
	sort(points.begin(), points.end());

	// find a solution
	set<pair<int,int>> next;
	int room[n];
	int belong[n];
	int curr = 1;
	map<int,int> mapped;
	for (Point p: points) {
		if (p.type == ROOM) {
			if (next.empty()) {
				cout << "Let's search for another office." << nl;
				return 0;
			}
			else {
				room[next.begin()->second] = p.index;
				belong[p.index] = next.begin()->second;
				next.erase(next.begin());
			}
		}
		else if (p.type == OPEN) {
			next.insert(pair<int,int>(p.b, p.index));
		}
		else {
			next.erase(pair<int,int>(p.a, p.index));
		}
		// map
		if (!mapped.count(p.a))
			mapped.insert(pair<int,int>(p.a, curr++));
	}
	// determine uniqueness
	BIT seen(3*n);
	for (Point p: points) {
		if (p.type == ROOM) {
			if (seen.query(mapped[interval[belong[p.index]].first], mapped[interval[belong[p.index]].second])) {
				cout << "Ask Shiftman for help." << nl;
				return 0;
			}
			seen.insert(mapped[roomsize[p.index]], 1);
		}
		else if (p.type == CLOSE) {
			seen.insert(mapped[roomsize[room[p.index]]], -1);
		}
		// else do nothing if OPEN
	}
	// output
	cout << "Perfect!" << nl;
	for (int i = 0; i < n; i++)
		cout << room[i]+1 << " ";
	cout << nl;


	return 0;
}

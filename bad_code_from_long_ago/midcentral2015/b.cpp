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
const double EPS = 1e-10;

/*****************************************/

struct Vector {
	double x, y;
	Vector(double x=0, double y=0): x(x), y(y) {}
	double length() {
		return sqrt(x*x + y*y);
	}
};
Vector operator + (const Vector& a, const Vector& b) {
	return Vector(a.x + b.x, a.y + b.y);
}
Vector operator - (const Vector& a, const Vector& b) {
	return Vector(a.x - b.x, a.y - b.y);
}
Vector operator * (double c, const Vector& vec) {
	return Vector(c*vec.x, c*vec.y);
}
Vector operator / (const Vector& vec, double c) {
	return Vector(vec.x/c, vec.y/c);
}

struct Drop {
	double time;
	double radius;
	Vector center;
	Vector velocity;
	Drop(double t = -1): time(t) {}
	Drop(double t, double r, const Vector& c, const Vector& v): radius(r), center(c), velocity(v), time(t) {}
	bool operator < (const Drop& other) const {
		return this < &other;
	}
	Drop operator + (const Drop& other) const {
		Vector a;
		if (abs(center.x - other.center.x) > EPS)
			a.x = center.x - other.center.x;
		if (abs(center.y - other.center.y) > EPS)
			a.y = center.y - other.center.y;
		Vector v;
		if (abs(velocity.x - other.velocity.x) > EPS)
			v.x = velocity.x - other.velocity.x;
		if (abs(velocity.y - other.velocity.y) > EPS)
			v.y = velocity.y - other.velocity.y;
		// parallel
		if (abs(v.y*v.y + v.x*v.x) < EPS) {
			return Drop();
		}
		// never touch
		if (abs(a.x*v.x + a.y*v.y) < EPS) {
			return Drop();
		}
		double t = - (a.x*v.x + a.y*v.y) / (v.x*v.x + v.y*v.y);
		// binary search on t
		double left, right, mid;
		left = 0;
		right = t;
		// VIVE LA REVOLUTION
		for (int i = 0; i < 1789; i++) {
			mid = (left + right) / 2;
			double dist = ((center + mid*velocity) - (other.center + mid*other.velocity)).length();
			if (dist > radius + other.radius) {
				left = mid;
			} else {
				right = mid;
			}
		}
		// too far
		if (abs(mid - t) < EPS) {
			return Drop();
		}
		double rad = sqrt(radius*radius + other.radius*other.radius);
		Vector cent = (radius*radius*(center + mid*velocity) + other.radius*other.radius*(other.center + mid*other.velocity))
				/ (radius*radius + other.radius*other.radius);
		Vector veloc = (radius*radius*velocity + other.radius*other.radius*other.velocity)
				/ (radius*radius + other.radius*other.radius);
		return Drop(mid, rad, cent, veloc);
	}
	Drop update(double t) {
		center = center + t*velocity;
		return (*this);
	}
};

ostream& operator << (ostream& os, const Drop& d) {
	os << d.time << " " << d.radius << " " << d.center.x << "," << d.center.y << " " << d.velocity.x << "," << d.velocity.y; return os;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	set<Drop> drops;
	double x, y, vx, vy, r;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> vx >> vy >> r;
		drops.insert(Drop(0, r, Vector(x,y), Vector(vx,vy)));
	}
	double totaltime = 0;
	set<Drop>::iterator first, second;
	for (;;) {
		Drop next;
		for (auto one = drops.begin(); one != drops.end(); ++one) {
			for (auto two = one; two != drops.end(); ++two) {
				if (one == two) continue;
				Drop other = *one + *two;
				if (other.time > 0 && (next.time < 0 || other.time < next.time)) {
					next = other;
					first = one;
					second = two;
				}
			}
		}
		if (next.time < 0) {
			break;
		}
		totaltime += next.time;
		drops.erase(first);
		drops.erase(second);

		vector<Drop> newdrops;
		for (Drop d : drops) {
			newdrops.push_back(d.update(next.time));
		}
		drops.clear();
		
		drops.insert(next);
		for (Drop d : newdrops) {
			drops.insert(d);
		}
	}
	cout << fixed << setprecision(10) << drops.size() << " " << totaltime << nl;

	return 0;
}

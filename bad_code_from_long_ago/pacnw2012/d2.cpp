#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define ll long long
#define ld double
#define pt complex<ld>
#define pol vector<pt>
#define pii pair<int,int>
#define pdd pair<ld,ld>
#define nl '\n'

struct Frac {
    ll n, d;
    Frac(ll n): n(n), d(1) {}
    Frac(ll x, ll y) {
        if (x == 0 && y == 0) {
            n = 0, d = 1;
        }
        else {
            ll g = __gcd(x,y);
			if (g == 0) for(;;);
            n = x/g, d = y/g;
            if (d < 0) n = -n, d = -d;
        }
    }
    bool operator < (const Frac& other) const {
        return n*other.d < other.n*d;
    }
    bool operator == (const Frac& other) const {
        return n*other.d == other.n*d;
    }
};

struct Point {
    ll x, y;
    Point(int x=-2, int y=-2): x(x), y(y) {}
    bool operator < (const Point& other) const {
        if (x == other.x) return y > other.y;
        else return x < other.x;
    }
    Frac slope(const Point& center) const {
        return Frac(x-center.x, y-center.y);
    }
};

Point center;
bool by_angle(const Point& a, const Point& b) {
    Frac asl = a.slope(center);
    Frac bsl = b.slope(center);
    if (asl.d == 0) return true;
    if (bsl.d == 0) return false;
    return asl < bsl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int x, y;
    int n, width, height;
    vector<Point> points;
    set<Point> half;

    for (;;) {
        cin >> n >> width >> height;
        if (n == 0) {
            break;
        }

        center = Point(width, height);
        points.clear();
        half.clear();
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            x *= 2;
            y *= 2;
            Point p(x,y);
            points.push_back(p);
            if (p.x > center.x)
                half.insert(p);
        }
        sort(points.begin(), points.end(), by_angle);

        for (int i = 0; i < n; i++) {
            int start, end;
            start = i;
            while (i < n-1 && points[i].slope(center) == points[i+1].slope(center)) {
                half.erase(points[i++]);
            }
            half.erase(points[i]);
            end = i;

            if (half.size() <= n/2 && half.size() + end-start+1 >= n/2) {
                for (int j = start; j <= end && half.size() < n/2; j++) {
                    half.insert(points[j]);
                }
                break;
            } else {
                for (int j = start; j <= end; j++) {
                    if (points[j] < center) 
                        half.insert(points[j]);
                }
            }
        }

        for (const Point& p : half) {
            cout << p.x/2 << " " << p.y/2 << nl;
        }
    }

    return 0;
}

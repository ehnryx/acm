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
const ldouble EPS = 1e-12;

struct Line {
    int id;
    int x1, x2;
    Line(int i, int a, int b):
        id(i), x1(a), x2(b) {}
    bool operator < (const Line& other) const {
        if (x1 != other.x1) return x1 > other.x1;
        else return id < other.id;
    }
};

struct Frac {
    ll x, y;
    Frac(ll a=0, ll b=1) {
        ll g = gcd(a,b);
        x = a/g;
        y = b/g;
        if (y < 0) {
            x = -x;
            y = -y;
        }
    }
    ll gcd(ll a, ll b) {
        if (b == 0) return a;
        else return gcd(b, a%b);
    }
    bool operator == (const Frac& other) const {
        return x == other.x && y == other.y;
    }
    bool operator < (const Frac& other) const {
        return x*other.y < y*other.x;
    }
};
ostream& operator << (ostream& os, const Frac& f) {
    os << f.x << "/" << f.y; return os;
}

struct Point {
    int dir;
    Frac x;
    Point(const Line& first, const Line& other) {
        if (other.x2 == first.x2) {
            if (other.x1 < first.x1) dir = 1;
            else dir = -1;
            x = Frac(1,0);
        } else {
            if (other.x2 > first.x2) dir = 1;
            else dir = -1;
            x = Frac(other.x1 - first.x1, first.x2 - other.x2);
        }
    }
    bool operator < (const Point& other) const {
        return x < other.x;
    }
};

int main() {
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<Line> lines;
    vector<Point> pts;

    int a, b;
    cin >> a >> b;
    Line first = Line(0, a, b);
    lines.push_back(first);

    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        lines.push_back(Line(i, a, b));
        if (b != first.x2) {
            Point p(first, lines.back());
            if (p.x.x > 0) pts.push_back(p);
        } else if (a != first.x1) {
            Point p(first, lines.back());
            pts.push_back(p);
        }
    } 
    sort(lines.begin(), lines.end());
    sort(pts.begin(), pts.end());

    int high, low;
    int same, up, down;
    same = up = down = 0;
    for (int i = 0; i < n; i++) {
        if (lines[i].id == 0) {
            high = i+1;
            for (int j = i+1; j < n && lines[j].x1 == lines[i].x1; j++) {
                if (lines[j].x2 > lines[i].x2) up++;
                else if (lines[j].x2 < lines[i].x2) down++;
                else same++;
            }
            low = high + up + down + same;
            break;
        }
    }

    int rmin, rmax;
    rmin = high;
    rmax = low;
    high += up;
    low -= down;
    for (int i = 0; i < pts.size(); i++) {
        if (i > 0 && pts[i].x == pts[i-1].x) 
            continue;
        up = down = 0;
        for (int j = i; j < pts.size() && pts[j].x == pts[i].x; j++) {
            if (pts[j].dir == 1) up++;
            else down++;
        }
        rmin = min(rmin, high - down);
        rmax = max(rmax, low + up);
        high += up - down;
        low += up - down;
    }

    cout << rmin << " " << rmax << nl;

    return 0;
}

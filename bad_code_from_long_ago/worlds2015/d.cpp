#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

class Hole {
public:
	double r;
	int x,y,z;
	double volume() {
		return M_PI*4*r*r*r/3;
	}
};

bool cmp(Hole a, Hole b) {
	return a.z - a.r < b.z - b.r;
}

double bs(vector<Hole> &h, double v) {
	double left, mid, right, tv;
	const double e = 0.0000001;
	left = 0;
	right = 100000;
	while (right - left > e) {
		mid = (left+right)/2;
		tv = 10000000000.0*mid;
		for (auto &hole : h) {
			if (hole.z - hole.r > mid)
				break;
			if (hole.z + hole.r < mid)
				tv -= hole.volume();
			else {
				if (hole.z < mid) {
					tv -= hole.volume();
					tv += M_PI*(hole.z+hole.r-mid)*(hole.r*hole.r - (hole.z-mid)*(hole.z-mid) - (mid-hole.z)*(hole.z+hole.r-mid) - (hole.z+hole.r-mid)*(hole.z+hole.r-mid)/3);
				}
				else {
					tv -= M_PI*(mid-hole.z+hole.r)*(hole.r*hole.r - (hole.z-mid)*(hole.z-mid) - (hole.z-mid)*(mid-hole.z+hole.r) - (mid-hole.z+hole.r)*(mid-hole.z+hole.r)/3);
				}
			}
		}
		if (tv < v)
			left = mid;
		else
			right = mid;
	}
	return mid;
}

int main() {
	ios::sync_with_stdio(0);
	cout << fixed << setprecision(10);

	int hnum, slices;
	double volume = 1000000000000000.0;
	double step;
	double prev, curr;
	vector<Hole> holes;
	cin >> hnum >> slices;
	holes.resize(hnum);
	for (int i = 0; i < hnum; i++) {
		cin >> holes[i].r >> holes[i].x >> holes[i].y >> holes[i].z;
		volume -= holes[i].volume();
	}
	sort(holes.begin(), holes.end(), cmp);
	step = volume/slices;
	//cerr << "volume: " << volume << endl;
	//cerr << "slices: " << slices << endl;
	//cerr << "step: " << step << endl;
	prev = 0;
	for (int s = 1; s < slices; s++) {
		curr = bs(holes, s*step);
		cout << (curr - prev)/1000 << endl;
		prev = curr;
	}
	cout << 100 - prev/1000 << endl;

	return 0;
}

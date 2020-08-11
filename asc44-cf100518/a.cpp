#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long double ld;
typedef complex<ld> pt;

const ld EPS = 1e-13;
const ld PI = acos((ld)-1);

const int INF = 0x3f3f3f3f;

const int BS = 70;

struct Point {
  int x, y;
  operator pt() const { return pt(x,y); }
  void rotate() {
    int nx = -y;
    y = x;
    x = nx;
  }
};

ld solve1(int r, const vector<Point>& p) {
  const int M = 4;
  int left[M], right[M], top[M], bot[M];
	memset(left, -1, sizeof left);
	memset(right, -1, sizeof right);
	memset(top, -1, sizeof top);
	memset(bot, -1, sizeof bot);
  auto uleft = [&] (int id) {
    for (int i=0; i<M; i++) {
			if (left[i] == -1 || p[id].x <= p[left[i]].x) {
        for (int j=M-1; j>i; j--) {
          left[j] = left[j-1];
        }
        left[i] = id;
        break;
      }
    }
  };
  auto uright = [&] (int id) {
    for (int i=0; i<M; i++) {
			if (right[i] == -1 || p[id].x >= p[right[i]].x) {
        for (int j=M-1; j>i; j--) {
          right[j] = right[j-1];
        }
        right[i] = id;
        break;
      }
    }
  };
  auto utop = [&] (int id) {
    for (int i=0; i<M; i++) {
			if (top[i] == -1 || p[id].y >= p[top[i]].y) {
        for (int j=M-1; j>i; j--) {
          top[j] = top[j-1];
        }
        top[i] = id;
        break;
      }
    }
  };
  auto ubot = [&] (int id) {
    for (int i=0; i<M; i++) {
			if (bot[i] == -1 || p[id].y <= p[bot[i]].y) {
        for (int j=M-1; j>i; j--) {
          bot[j] = bot[j-1];
        }
        bot[i] = id;
        break;
      }
    }
  };

  int n = p.size();
  for (int i=0; i<n; i++) {
    uleft(i);
    uright(i);
    utop(i);
    ubot(i);
  }

  vector<int> bounds;
  for (int i=0; i<M; i++) {
    if (left[i] != -1) bounds.push_back(left[i]);
    if (right[i] != -1) bounds.push_back(right[i]);
    if (top[i] != -1) bounds.push_back(top[i]);
    if (bot[i] != -1) bounds.push_back(bot[i]);
  }

  ld res = 0;
  for (int a : bounds) {
    for (int b : bounds) {
      if (a==b) continue;
      for (int c : bounds) {
        if (a==c||b==c) continue;
        for (int d : bounds) {
          if (a==d||b==d||c==d) continue;
          ld cur = (ld)(p[a].x-p[b].x+2*r)*(p[c].y-p[d].y+2*r);
          res = max(res, cur);
        }
      }
    }
  }
  return res;
}

pt polar(ld r, ld ang) {
  return r * exp(pt(0,ang));
}

ld area(const pt& a, const pt& b) {
  return (b.real()-a.real())*(b.imag()-a.imag());
}

ld search1(const pt& lb, const pt& c, int r) {
  ld left = 0;
  ld right = PI/2;
  for (int bs=0; bs<BS; bs++) {
    ld mid1 = (2*left+right)/3;
    ld mid2 = (left+2*right)/3;
    ld res1 = area(lb, c+polar(r,mid1));
    ld res2 = area(lb, c+polar(r,mid2));
    if (res1 > res2) {
      right = mid2;
    } else {
      left = mid1;
    }
  }
  return area(lb, c+polar(r,left));
}

ld search2(const pt& lb, const pt& ub, int r) {
  ld left = PI;
  ld right = 3*PI/2;
	cerr << "left: " << left << "   right: " << right << nl;
  for (int bs=0; bs<BS; bs++) {
    ld mid1 = (2*left+right)/3;
    ld mid2 = (left+2*right)/3;
    ld res1 = search1(lb+polar(r,mid1), ub, r);
    ld res2 = search1(lb+polar(r,mid2), ub, r);
    if (res1 > res2) {
      right = mid2;
    } else {
      left = mid1;
    }
  }
	cerr << "search1 " << lb+polar(r,left) << " " << ub << nl;
  return search1(lb+polar(r,left), ub, r);
}

ld solve2(int r, vector<Point> p) {
  for (Point& it : p) {
    it.rotate();
  }

  const int M = 4;
  int left[M], right[M], top[M], bot[M];
	memset(left, -1, sizeof left);
	memset(right, -1, sizeof right);
	memset(top, -1, sizeof top);
	memset(bot, -1, sizeof bot);
  auto uleft = [&] (int id) {
    for (int i=0; i<M; i++) {
			if (left[i] == -1 || p[id].x <= p[left[i]].x) {
        for (int j=M-1; j>i; j--) {
          left[j] = left[j-1];
        }
        left[i] = id;
        break;
      }
    }
  };
  auto uright = [&] (int id) {
    for (int i=0; i<M; i++) {
			if (right[i] == -1 || p[id].x >= p[right[i]].x) {
        for (int j=M-1; j>i; j--) {
          right[j] = right[j-1];
        }
        right[i] = id;
        break;
      }
    }
  };
  auto utop = [&] (int id) {
    for (int i=0; i<M; i++) {
			if (top[i] == -1 || p[id].y >= p[top[i]].y) {
        for (int j=M-1; j>i; j--) {
          top[j] = top[j-1];
        }
        top[i] = id;
        break;
      }
    }
  };
  auto ubot = [&] (int id) {
    for (int i=0; i<M; i++) {
			if (bot[i] == -1 || p[id].y <= p[bot[i]].y) {
        for (int j=M-1; j>i; j--) {
          bot[j] = bot[j-1];
        }
        bot[i] = id;
        break;
      }
    }
  };

  int n = p.size();
  for (int i=0; i<n; i++) {
    uleft(i);
    uright(i);
    utop(i);
    ubot(i);
  }

  auto contains = [&] (int v[], int id) {
    for (int i=0; i<M; i++) {
      if (v[i] == id) return true;
    }
    return false;
  };

  vector<int> bounds, topright, botleft;
  for (int i=0; i<M; i++) {
    if (left[i] != -1) bounds.push_back(left[i]);
    if (right[i] != -1) bounds.push_back(right[i]);
    if (top[i] != -1) bounds.push_back(top[i]);
    if (bot[i] != -1) bounds.push_back(bot[i]);
    if (right[i] != -1 && contains(top, right[i])) {
      topright.push_back(right[i]);
    }
    if (left[i] != -1 && contains(bot, left[i])) {
      botleft.push_back(left[i]);
    }
  }

  ld res = 0;
  // check topright
  for (int a : bounds) {
    for (int b : bounds) {
      if (a==b) continue;
      for (int c : topright) {
        if (a==c||b==c) continue;
				cerr << "check " << a << " " << b << " " << c << endl;
        ld cur = search1(pt(p[a].x-r,p[b].y-r), p[c], r);
        res = max(res, cur);
      }
    }
  }
  // check topright + botleft
  for (int a : botleft) {
    for (int b : topright) {
      if (a==b) continue;
				cerr << "check " << a << " " << b << endl;
      ld cur = search2(p[a], p[b], r);
      res = max(res, cur);
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  for (int n, r; cin >> n >> r && n; ) {
    vector<Point> p;
    for (int i=0; i<n; i++) {
      int x, y;
      cin >> x >> y;
      p.push_back({x,y});
    }

    ld ans = max(ans, solve1(r,p));
    for (int i=0; i<4; i++) {
      ans = max(ans, solve2(r,p));
    }
    cout << fixed << setprecision(17) << ans << nl;
  }

  return 0;
}

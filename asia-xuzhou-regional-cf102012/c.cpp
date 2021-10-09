#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,tune=native")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-12;

const int N = 51;
ld dist[N*N*N*N];
int h[N];
vector<int> height;
vector<ld> diff;

struct Node {
  int a, b;
  ld dist;
  bool operator < (const Node& o) const {
    return dist > o.dist;
  }
};

ld sqr(const ld& x) { return x*x; }
ld cost(int a, int b, int na, int nb) {
  ld out = 0;
  if (a != na) {
    out += diff[min(a,na)];
  }
  if (b != nb) {
    out += diff[min(b,nb)];
  }
  return out;
}

//const int K = 5;
//vector<int> dx = { 1, 1, 1, 0, -1 };
//vector<int> dy = { 1, -1, 0, -1, -1 };
const int K = 8;
vector<int> dx = { 1, 1, 1, 0, 0, -1, -1, -1 };
vector<int> dy = { 1, 0, -1, 1, -1, 1, 0, -1 };

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(16);

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;

    for (int i=0; i<=n; i++) {
      cin >> h[i];
    }

    height.clear();
    diff.clear();

    height.push_back(0);
    for (int i=1; i<=n; i++) {
      int hs = h[i-1];
      int ht = h[i];
      if (hs == ht) {
        height.push_back(ht);
        diff.push_back(1);
      } else if (hs < ht) {
        int d = ht - hs;
        for (int j=1; j<=d; j++) {
          height.push_back(hs+j);
          diff.push_back(sqrt(sqr((ld)1/d) + 1));
        }
      } else {
        int d = hs - ht;
        for (int j=1; j<=d; j++) {
          height.push_back(hs-j);
          diff.push_back(sqrt(sqr((ld)1/d) + 1));
        }
      }
    }
    int m = height.size();
    fill(dist, dist+m*m, 1e42);

    bool found = false;
    priority_queue<Node> dijk;
    dijk.push({0, m-1, 0});
    dist[m-1] = 0;
    while (!dijk.empty()) {
      Node cur = dijk.top();
      dijk.pop();
      int a = cur.a;
      int b = cur.b;
      int id = a*m + b;
      //cerr << "visit " << a << " " << b << nl;
      if (a == b) {
        cout << 2*cur.dist << nl;
        found = true;
        break;
      }
      if (abs(dist[id] - cur.dist) < EPS) {
        for (int i=0; i<K; i++) {
          int na = a + dx[i];
          int nb = b + dy[i];
          //cerr << "try " << na << " " << nb << nl;
          if (0 <= na && na < m && 0 <= nb && nb < m && height[na] == height[nb]) {
            int nid = na*m + nb;
            ld nxt = cur.dist + cost(a,b,na,nb);
            if (nxt < dist[nid]) {
              dist[nid] = nxt;
              dijk.push({na, nb, nxt});
              //cerr << "push " << na << " " << nb << " w/ " << nxt << " from " << a << " " << b << nl;
            }
          }
        }
      }
    }
    assert(found);
  }

  return 0;
}

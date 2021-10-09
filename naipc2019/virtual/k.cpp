#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 1010;

struct card {
  ll x, y, a, b, p;
};

struct Node {
  ll g; bool same; ll dist;
  bool operator < (const Node& o) const {
    return dist > o.dist;
  }
};

card cards[N];
unordered_map<ll, ll> d;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> cards[i].x >> cards[i].y >> cards[i].a >> cards[i].b >> cards[i].p;
  }
  ll r0, c0; tie(r0, c0) = tie(cards[0].x, cards[0].y);
  if (!r0 && !c0) {
    puts("0");
    return 0;
  }

  priority_queue<Node> pq;
  for (int i=0; i<n; i++) {
    if (cards[i].x == r0 && cards[i].y == c0) {
      ll gi = __gcd(cards[i].a, cards[i].b);
      ll gsumi = __gcd(cards[i].a+cards[i].b, abs(cards[i].a-cards[i].b));
      pq.push({gi, gi==gsumi, cards[i].p});
    }
  }
  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();
    ll val = cur.g<<1|cur.same;
    ll sumg = (cur.same ? cur.g : cur.g*2);
    if (!d.count(val)) {
      //cerr << "VIS " << cur.g << " " << cur.same << " " << sumg << endl;
      if (r0 % cur.g == 0 && c0 % cur.g == 0 && (r0+c0) % sumg == 0 && (r0-c0) % sumg == 0) {
        cout << cur.dist << nl;
        return 0;
      }
      d[val] = cur.dist;
      for (int i=0; i<n; i++) {
        //cerr << "@ " << i << endl;
        if ((r0-cards[i].x) % cur.g == 0 && (c0-cards[i].y) % cur.g == 0 && (r0+c0-cards[i].x-cards[i].y) % sumg == 0 && (r0-c0-cards[i].x+cards[i].y) % sumg == 0) {
          ll ng = __gcd(cur.g, __gcd(cards[i].a, cards[i].b));
          ll nsumg = __gcd(sumg, __gcd(cards[i].a+cards[i].b, abs(cards[i].a-cards[i].b)));
          bool nsame = (nsumg == ng);
          if (!nsame) {
            //cerr << "ng: " << ng << "  nsum: " << nsumg << endl;
            assert(2*ng == nsumg);
          }
          if (!d.count(ng<<1|nsame)) {
            pq.push({ng, nsame, cur.dist + cards[i].p});
          }
        }
      }
    }
  }
  puts("-1");

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const ll INF = 0x3f3f3f3f;

const int N = 2*(sqrt(1e9)+5);

string curans;

ll tri[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  for (int i = 1; i < N; i++) {
    tri[i] = tri[i-1] + i;
  }
  int T; cin >> T;
  while (T--) {
    int ha, hb, aa, ab; cin >> ha >> hb >> aa >> ab;
    int rounds = 0;
    while (tri[rounds] < ha + hb) rounds++;
    // a -> b
    int ar = 0;
    while (tri[ar] < ha) ar++;
    int hi = tri[ar] - ha;
    int lo = hb - (tri[rounds] - tri[ar]);
    ll anum = (ll) ar * (aa + ab) + (ll) (rounds - ar) * ab;
    string aans;
    for (int i = 0; i < ar; i++) {
      aans.push_back('A');
    }
    for (int i = ar; i < rounds; i++) {
      aans.push_back('B');
    }
    ////cerr << lo << " " << aans.size() << nl;
    if (lo > 0 && hi > 0) {
      aans[hi-1] = 'B';
    }
    //cerr << aans << nl;

    // b -> a
    int br = 0;
    while (tri[br] < hb) br++;
    hi = tri[br] - hb;
    lo = ha - (tri[rounds] - tri[br]);
    ll bnum = (ll) br * (aa + ab) + (ll) (rounds - br) * aa;
    string bans;
    for (int i = 0; i < br; i++) {
      bans.push_back('B');
    }
    for (int i = br; i < rounds; i++) {
      bans.push_back('A');
    }
    //cerr << ar << " " << br << nl;
    int cur = 0, last = 0;
    for (int i = 1; i <= br; i++) {
      if (hi - (cur + i) > i) {
        cur += i;
        bans[i-1] = 'A';
        last = i;
      }
    }
    if (tri[br] != hb) {
      bans[max(lo - cur - 1, last)] = 'A';
    }

    ////cerr << ar << " " << br << " " << rounds << nl;

    if (anum < bnum || (anum == bnum && aans < bans)) {
      cout << anum << " " << aans << nl;
    } else {
      cout << bnum << " " << bans << nl;
    }
  }

  return 0;
}

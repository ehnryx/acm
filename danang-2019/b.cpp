#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const ll N = 300300;
const ll SEG = 4*N;

struct Rope {
	ll b, l1, l2, s;
	bool operator< (const Rope& o) {
		return s < o.s;
	}
};

struct Banana {
	ll l, h, x, y;
	bool operator < (const Banana& o) const {
		return h < o.h;
	}
};

vector<ll> ladder[N];
vector<Banana> bananas[SEG];
ll nxt[SEG];
ll dist[SEG];
ll seg_bot[SEG], seg_top[SEG];
ll seg_count;

vector<Banana> init_bananas[N];

struct Monkey {
	ll c, d, ind;
};

Monkey monkey[N];

ll n, h, r, b;
vector<Rope> ropes;

void build() {
	sort(ropes.begin(), ropes.end());

	for (ll u=1; u<=n; ++u) {
		sort(init_bananas[u].rbegin(), init_bananas[u].rend());
	}

	for (auto& rope : ropes) {
		ll u = rope.l1;
		ll v = rope.l2;

		ll tu = ladder[u].back();
		ll tv = ladder[v].back();

		ll su = ++seg_count;
		ll sv = ++seg_count;
		ladder[u].push_back(su);
		ladder[v].push_back(sv);

		nxt[tu] = sv;
		nxt[tv] = su;
		dist[tu] = rope.b;
		dist[tv] = rope.b;
		seg_top[tu] = seg_top[tv] = rope.s;
		seg_bot[su] = seg_bot[sv] = rope.s;

		seg_top[su] = seg_top[sv] = h;
		nxt[su] = nxt[sv] = -1;

		while (init_bananas[u].size() && init_bananas[u].back().h < seg_top[tu]) {
			bananas[tu].push_back(init_bananas[u].back());
			init_bananas[u].pop_back();
		}

		while (init_bananas[v].size() && init_bananas[v].back().h < seg_top[tv]) {
			bananas[tv].push_back(init_bananas[v].back());
			init_bananas[v].pop_back();
		}
	}

	for (ll u=1; u<=n; ++u) {
		ll tu = ladder[u].back();
		for (auto& ba : init_bananas[u]) {
			bananas[tu].push_back(ba);
		}
	}
}

ll query(ll ind, ll c, ll d) {
	ll pos = ladder[ind][0];
	ll t = 0;
	ll ans = 0;
	while (pos != -1) {
		for (auto& ban : bananas[pos]) {
			ll m = ban.x+ban.y;
			ll k = t+c*(ban.h-seg_bot[pos]);
			if (k%m >=1 && k%m <= ban.x) {
				++ans;
			}
		}

		t += dist[pos]*d + (seg_top[pos]-seg_bot[pos])*c;
		pos = nxt[pos];
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> h >> r >> b;

	ropes.resize(r);
	for (auto& ro : ropes) {
		cin >> ro.b >> ro.l1 >> ro.l2 >> ro.s;
	}

	for (ll i=1; i<=n; ++i) {
		ll seg = ++seg_count;
		ladder[i].push_back(seg);
		nxt[seg] = -1;
		seg_bot[seg] = 0;
		seg_top[seg] = h;
	}
	for (ll i=1; i<=n; ++i) {
		cin >> monkey[i].c >> monkey[i].d;
		monkey[i].ind = i;
	}

	for (ll i=1; i<=b; ++i) {
		Banana ban;
		cin >> ban.l >> ban.h >> ban.x >> ban.y;
		init_bananas[ban.l].push_back(ban);
	}

	build();

	ll ans = 0;

	for (ll i=1; i<=n; ++i) {
		ans += query(i, monkey[i].c, monkey[i].d);
	}

	cout << ans << "\n";

	return 0;
}

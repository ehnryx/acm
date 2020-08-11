#include <cstdio>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int N = 100000 + 5;

int nums[N], penalty[N];

struct tup {
	int x, y, z;
	tup(int x, int y, int z): x(x), y(y), z(z) {}
};

struct cmp {
	bool operator() (const tup& a, const tup& b) const {
		return (a.x > b.x) || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.z < b.z);
	}
};

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	typedef tree<tup, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update> map_t;
	map_t s;
	for (int i = 1; i <= n; i++) {
		s.insert(tup(0, 0, i));
		nums[i] = 0;
		penalty[i] = 0;
	}
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		s.erase(s.find(tup(nums[x], penalty[x], x)));
		nums[x]++;
		penalty[x] += y;
		s.insert(tup(nums[x], penalty[x], x));
		printf("%d\n", s.order_of_key(tup(nums[1], penalty[1], -1)) + 1);
	}
	return 0;
}

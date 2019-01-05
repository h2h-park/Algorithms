//https://www.acmicpc.net/problem/1753

#include <stdio.h>
#include <vector>
#include <queue>

class Dijkstra {
public:
	const int INF = 1 << 29;
	int n;
	struct data {
		int x, cost;
		const bool operator < (const data &rhs) const {
			return this->cost > rhs.cost;
		}
	};
	std::vector<data>* vec;
	int* dis;
	bool* check;

	Dijkstra(int n) {
		this->n = n;
		vec = new std::vector<data>[n + 1];
		dis = new int[n + 1];
		check = new bool[n + 1];
	}

	void add_edge(int x, int y, int z) {
		vec[x].push_back({ y, z });
	}

	int* shortest(int st) {
		int i;
		std::priority_queue<data> pq;
		for (i = 1; i <= n; i++) {
			dis[i] = INF;
			check[i] = false;
		}
		dis[st] = 0;
		pq.push({ st, 0 });
		for (; !pq.empty();) {
			data now = pq.top();
			pq.pop();
			if (check[now.x]) continue;
			check[now.x] = true;
			for (data chd : vec[now.x]) {
				if (check[chd.x]) continue;
				if (dis[chd.x] > dis[now.x] + chd.cost) {
					dis[chd.x] = dis[now.x] + chd.cost;
					pq.push({ chd.x, dis[chd.x] });
				}
			}
		}
		return dis;
	}
};

int main(void) {
	int n, m, start;
	int u, v, w;
	scanf("%d %d", &n, &m);
	scanf("%d", &start);

	Dijkstra D(n);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		D.add_edge(u, v, w);
	}

	int* dis = D.shortest(start);
	for (int i = 1; i <= n; i++) {
		if (dis[i] < D.INF) printf("%d\n", dis[i]);
		else puts("INF");
	}
	return false;
}
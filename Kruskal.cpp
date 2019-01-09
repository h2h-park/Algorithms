// https://www.acmicpc.net/problem/1197
#include <stdio.h>
#include <algorithm>
#include <vector>

class Disjoint {
public:
	int n;
	int* par;

	Disjoint(int n) {
		this->n = n;
		par = new int[n + 1];
		for (int i = 1; i <= n; i++) par[i] = i;
	}

	~Disjoint(void) {
		delete[] par;
	}

	int find(int p) {
		return (par[p] == p) ? p : (par[p] = find(par[p]));
	}
	
	bool uni(int x, int y) {
		int xr = find(x), yr = find(y);
		if (xr != yr) {
			par[xr] = yr;
			return true;
		}
		return false;
	}
};

template <typename T>
class Kruskal {
public:
	struct data {
		int x, y;
		T cost;
	};
	int n;
	std::vector<data> edge;
	
	Kruskal(int n) {
		this->n = n;
	}

	void addedge(int x, int y, T cost) {
		edge.push_back({ x, y, cost });
	}

	T mst(void) {
		T ret = 0;
		int rest = n - 1;
		Disjoint dj(n);
		std::sort(edge.begin(), edge.end(), [](const data &a, const data &b) {
			return a.cost < b.cost;
		});

		for (data now : edge) {
			if (dj.uni(now.x, now.y)) {
				rest--;
				ret += now.cost;
			}
			if (rest == 0) break;
		}

		return ret;
	}
};

int main(void) {
	int n, m;
	int a, b, c;
	scanf("%d %d", &n, &m);
	Kruskal<int> krs(n);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		krs.addedge(a, b, c);
	}
	printf("%d\n", krs.mst());
	return false;
}
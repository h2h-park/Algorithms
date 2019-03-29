// https://www.acmicpc.net/problem/6086

#include <stdio.h>
#include <vector>
#include <queue>

template <typename T>
class EK {
public:
	int n, m;
	T inf;
	std::vector<int>* vec;
	T** f;
	bool* check;
	
	EK(int n, int m, T inf) {
		this->n = n;
		this->m = m;
		this->inf = inf;
		vec = new std::vector<int>[n + 1];
		f = new T*[n + 1];
		for (int i = 0; i <= n; i++) {
			f[i] = new T[n + 1];
			for (int j = 0; j <= n; j++) f[i][j] = 0;
		}
		check = new bool[n + 1];
	}

	~EK(void) {
		delete[] vec;
		delete[] f;
		delete[] check;
	}

	void add_edge(int x, int y, T c) {
		vec[x].push_back(y);
		f[x][y] += c;
	}

	T bfs(int src, int snk, std::vector<int>& parent) {
		T ret = 0;
		std::queue<int> q;
		std::queue<T> flow;
		for (int i = 0; i <= n; i++) check[i] = false;

		q.push(src);
		flow.push(inf);
		check[src] = true;
		for (; !q.empty();) {
			int now = q.front();
			T now_f = flow.front();
			q.pop();
			flow.pop();

			if (now == snk) {
				ret = now_f;
				break;
			}

			for (int chd : vec[now]) {
				if (f[now][chd] == 0 || check[chd]) continue;
				q.push(chd);
				parent[chd] = now;
				flow.push((now_f > f[now][chd]) ? f[now][chd] : now_f);
				check[chd] = true;
			}
		}
		return ret;
	}

	T max_flow(int src, int snk) {
		T ret = 0, flow;
		std::vector<int> parent(n + 1);
		
		for ( ; flow = bfs(src, snk, parent); ) {
			ret += flow;
			for (int x = snk; x != src; x = parent[x]) {
				int par = parent[x];
				f[par][x] -= flow;
				f[x][par] += flow;
			}
		}
		return ret;
	}
};

int main(void) {
	int m, f;
	char x, y;
	scanf("%d", &m);
	EK<int> ek(256, m, 1000);
	for (int i = 1; i <= m; i++) {
		scanf(" %c %c %d", &x, &y, &f);
		ek.add_edge(x, y, f);
		ek.add_edge(y, x, f);
	}
	printf("%d\n", ek.max_flow(65, 90));
	return false;
}
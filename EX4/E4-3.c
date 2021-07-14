#include <iostream>
#include <set>
#include <cstdio>
#include <map> 
using namespace std;
const int nmax = 100000 + 20;
multiset<int>s;
int a[nmax]; //a[i] 按序存储 主存的访问次序 
int p[nmax]; //p[i]表示a[i]下一次出现的位置
int g[nmax]; //g[i]表示a[i]上一次出现的位置
//思路；把主存从下一此出现的最远的换掉 
int main(int argc, char** argv) {
	int n;//主存访问次数 
	int m;//cache容量 
	while (cin >> n >> m) {
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for (int i = 1; i <= n; i++) {
			p[i] = n + 1;//先设个初值，如果a[i]没有下一次,就保持n+1 
			p[g[a[i]]] = i;
			g[a[i]] = i;
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (s.find(i) != s.end()) {//出现 
				s.erase(i);     //删掉本次 
				s.insert(p[i]); //加入下一次 
			}
			else {//没出现
				ans++;
				if (s.size() == m) {//如果主存已经满了 
					s.erase(--s.end());//删掉最晚的
				}
				s.insert(p[i]); //加入下一次 

			}
		}
		cout << ans << endl;
	}
	return 0;
}
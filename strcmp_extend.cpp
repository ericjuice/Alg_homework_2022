#include<iostream>
#include <string>
using namespace std;

const int N = 2000;

int main(void)
{	
	int f[2][N];//动态规划所用的矩阵
	string a, b;
	int k;//假设增删字符串的代价固定是k，替换字符串的代价是ascii差值
	cin >> a >> b;
	cin >> k;
	int len_a=a.length();
	int len_b=b.length();
	for (int i = 0; i < N; ++i){//构造一个矩阵，i代表字符串A的字符位置，j代表B的
		f[0][i] = k * i;
	}
	f[1][0]=k;
	//cout<<len_a<<' '<<len_b<<endl;
	for (int i = 1; i <= len_a ; ++i){
		for (int j = 1; j <= len_b; ++j){
			f[1][j] = min(min(f[0][j], f[1][j - 1]) + k, f[0][j-1] + abs(a[i - 1] - b[j - 1]));
			//min(f[0][j], f[1][j-1])+k 代表横向和纵向移动，即增加字符串，所消耗的最小代价
			//min(min(**)+k, f[0][j-1]+abs(**))，代表斜向移动，即替换字符串，消耗的最小代价
		} 
		for(int m=0;m<N;m++){//每次计算只需要2行，节省空间。每一轮之后把第二行移到第一行
			f[0][m]=f[1][m];
		}
		f[1][0]=k*(i+1);
	}
	cout << f[0][len_b] << endl;

	return 0;
}

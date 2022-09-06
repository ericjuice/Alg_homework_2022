#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

void main(){
	int n;
	cin>>n;
	priority_queue <int,vector<int>,greater<int> > leaves;
	priority_queue <int,vector<int>,greater<int> > leaves_2;
	priority_queue<int,vector<int>,greater<int> > nodes;//存非叶节点权重
	int a;
	for(int i=0;i<n;i++){
		cin>>a;
		leaves.push(a);
		leaves_2.push(a);
	}
	for(int i=0;i<n-1;i++){
		int temp=leaves.top();
		leaves.pop();
		temp+=leaves.top();
		leaves.pop();
		leaves.push(temp);//叶子节点融合俩最小的
		nodes.push(temp);//nodes加上这个非叶节点
	}
	int sum1=0,sum2=0;//叶子/非叶权重和
	for(int i=0;i<n;i++){
		sum1+=leaves_2.top();
		leaves_2.pop();
	}
	for(int i=0;i<n-1;i++){
		sum2+=nodes.top();
		nodes.pop();
	}
	cout.setf(ios::fixed);
	//利用规律：平均编码长度=非叶权重和/叶子权重和
	cout<<setprecision(2)<<(float)sum2/sum1;
}

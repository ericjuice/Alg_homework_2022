#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

struct node{
	double x;
	double y;
};
double get_distance(node a,node b){
	return (a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x);
}
bool cmp_y(node a,node b){//y升序
	return a.y<b.y;
}
bool cmp_x(node a,node b){//x升序
	return a.x<b.x;
}
double min_dis=10000.0;//最小距离，初始化为较大的数

double calcu(node *n,int start,int end){//nodes[i][0] is x，[i][1] is y;下标在s到e的范围内，闭区间
	int length = end-start + 1;
	if(length<=3){//总长度小于=3直接寻找
		switch(length){
		case 3:{
				double min1=min(get_distance(n[start], n[start+1]),get_distance(n[start], n[end]));
				double min2=min(min1,get_distance(n[start+1], n[end]));
				return  min2;
			   }
		case 2:
			return get_distance(n[start],n[end]);
		}
	}
	int mid=(start+end)/2;
    min_dis = min(calcu(n,start,mid), calcu(n,mid + 1,end));
        
    //归并，判断左右的点是否更短的距离
    //只有x-mid.x<min_dis的点才有可能更近，即gap
    node* gap = new node[length];
    int possibleNum = 0;
    for(int i = start; i <= end; i++) {
        if(abs(n[i].x - n[mid].x) < min_dis) {
            gap[possibleNum] = n[i];
            ++possibleNum;
        }
    }
    // 按照纵坐标进行排序以减少比较次数
    sort(gap, gap + possibleNum, cmp_y);
    // 暴力比较gap的距离
    for(int i = 0; i < possibleNum - 1; ++i) {
        for(int j = i + 1; j < possibleNum; ++j) {
            // 如果j点的纵坐标与i点的纵坐标的差距已经超过目前的最短距离，则剩下的点就不用比较了
            if(gap[j].y - gap[i].y > min_dis) {
                break;
            }else {
                min_dis = min(min_dis, get_distance(gap[i], gap[j]));
            }
        }
    }     
    // 释放资源
    delete [] gap;

	return min_dis;
}

int main(){
	int n;
	cin>>n;
	node *px=new node [n];
	for(int i=0;i<n;i++){
		cin>>px[i].x>>px[i].y;
	}
	sort(px,px+n,cmp_x);
	float result=calcu(px,0,n-1);
	printf("%.2f",result);
	
	delete []px;
}
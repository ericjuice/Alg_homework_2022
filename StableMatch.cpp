#include <iostream>
using namespace std;

int invite(int inviter,int invited,int *list,int *invited_check){
	if(invited_check[invited]<0)//还没被邀请,return 1
		return 1;
	if(list[inviter]<list[invited_check[invited]])//邀请者的排名比当前的对象高,return 2
		return 2;
	return 0;
}
void initial(int *a,int n,int target){//a[n]初始化为target
	for(int i=0;i<n;i++)
		a[i]=target;
}

int match(int *result,int **womanprefer,int **manprefer,int n){
	int *womans_man=new int[n];//下标表示接受的对象，-1表示还没被邀请
	int *mans_woman=new int[n];
	int *mychance=new int[n];
	int **womanchangelist=new int*[n];//转置过的女生的prefer,下标是男生index，值为排名
	for(int i=0;i<n;i++){
		womanchangelist[i]=new int[n];
		for(int j=0;j<n;j++)
			womanchangelist[i][womanprefer[i][j]]=j;
	}
	initial(result,n,-1);//初始化结果
	initial(womans_man,n,-1);//将两个确定匹配的表置-1
	initial(mans_woman,n,-1);
	initial(mychance,n,n);//每个邀请者有n次机会

	for(int i=0;i<n;i++){//go inviting
		if(mans_woman[i]>=0||mychance[i]<1)//当前男的已经有对象了或者没机会了，换下一个男的
			continue;
		//cout<<endl;有的注释是调试用的，不用管
		for(int j=0;j<n;j++){//第i个男人向第j个目标发起邀请,manprefer[i][j]为女方编号
			//cout<<"1 ";
			mychance[i]--;//邀请机会-1
			int end=invite(i,manprefer[i][j],womanchangelist[manprefer[i][j]],womans_man);//邀请结果
			if(end==2){//如果成功并且踢走某人
				int kicked=womans_man[manprefer[i][j]];//先踢掉当前的人
				mans_woman[kicked]=-1;//当前男的被甩
				womans_man[manprefer[i][j]]=i;//新男人上位
				mans_woman[i]=manprefer[i][j];//新女人上位
				i=kicked-1;//那么被踢掉的人重新选择,i会++，故减一
				break;//跳出去让那个失败者重新来
			}
			else if(end==1){
				womans_man[manprefer[i][j]]=i;//新男人上位
				mans_woman[i]=manprefer[i][j];//新女人上位
				break;//邀请完成
			}
			else continue;//失败了，下一个女人
		}
	}	
	//cout<<"\nyes";
	for(int i=0;i<n;i++)//值赋过去
		result[i]=mans_woman[i];
	for(int j=0;j<n;j++){
		delete []womanchangelist[j];
	}
	delete []womanchangelist;
	delete []womans_man;
	delete []mans_woman;
	delete []mychance;
	return *result;
}

int main(){
	int n;//men and women
	cout<<"Please input n\n";
	cin>>n;
	cout<<"Now input lists\n";
	int **manprefer=new int *[n];
	int **womanprefer=new int *[n];
	for(int i=0;i<n;i++){
		manprefer[i]=new int[n];
		for(int j=0;j<n;j++){
			int x;
			cin>>x;
			manprefer[i][j]=x-1;//输入是从1开始的，要从0开始
		}
	}
	for(int i=0;i<n;i++){
		womanprefer[i]=new int[n];
		for(int j=0;j<n;j++){
			int x;
			cin>>x;
			womanprefer[i][j]=x-1;
		}
	}
	int *result=new int[n];
	match(result,womanprefer,manprefer,n);
	for(int i=0;i<n;i++){
		cout<<result[i]+1;
		if(i!=n-1)
			cout<<' ';
		else cout<<"\n";           
	}
	for(int j=0;j<n;j++){
		delete []manprefer[j];
		delete []womanprefer[j];
	}
	delete []result;
	delete []manprefer;
	delete []womanprefer;
}
#include <iostream>
#include <queue>
using namespace std;

struct bian //边的集合
{
    int node1;
    int node2;
    int weight;
    friend bool operator<(bian a, bian b)
    {
        return a.weight > b.weight; //按权重升序
    }
};

void set_tree(int *nodes, int n, int origin, int dest)
{ //把n长度的nodes数组里所有值为ori的改成dest
    for (int i = 0; i < n; i++)
    {
        if (nodes[i] == origin)
            nodes[i] = dest;
    }
}

int main()
{
    int n, m; //节点和边数
    priority_queue<bian> q_bian;
    cin >> n >> m;
    int *nodes = new int[n];

    for (int i = 0; i < n; i++)
    {
        nodes[i] = i; //用一维数组表示节点，下标+1为节点号，值是节点所属的树的编号
    }
    for (int i = 0; i < m; i++) // q_bian保存了边的最小堆
    {
        bian temp;
        cin >> temp.node1 >> temp.node2 >> temp.weight;
        q_bian.push(temp);
    }
    int sum = 0;
    while (q_bian.size() > 0)
    {
        int new_n1 = q_bian.top().node1;
        int new_n2 = q_bian.top().node2;
        if (nodes[new_n1 - 1] != nodes[new_n2 - 1])
        { //从小的开始遍历边，如果节点不在同一棵树，就融合。也就是加入这条边不会构成回路
            sum += q_bian.top().weight;
            set_tree(nodes, n, nodes[new_n1 - 1], nodes[new_n2 - 1]);
        }
        q_bian.pop();
    }
    cout << sum;
    system("pause");
}

#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

class Solution
{
    int step_count = 1;
    double start_time;
    double end_time;

public:
    void solveShuDu(vector<vector<char>> &board)
    {
        cout << "开始求解:\n";
        start_time = clock();
        back(board, 0, 0);
        end_time = clock();
        cout << "解答完成,用时" << (end_time - start_time) / CLOCKS_PER_SEC << "秒，答案如下\n";
    }
    bool isvalid(vector<vector<char>> &board, int x, int y, int n)
    {
        for (int i = 0; i < 9; i++) //寻找横竖以及九宫格内有无相同的数，有的话就false
        {
            if (board[x][i] == n)
                return false;
            if (board[i][y] == n)
                return false;
            if (board[(x / 3) * 3 + i / 3][(y / 3) * 3 + i % 3] == n)
                return false;
        }
        return true;
    }

    bool back(vector<vector<char>> &board, int x, int y)
    {
        if (y == 9) //该换行了
        {
            x += 1;
            y = 0;
        }
        if (x == 9) //搜索完成
            return true;

        if (board[x][y] != '.') //这个空有数字了，跳
            return back(board, x, y + 1);
        else
        {
            for (char a = '1'; a <= '9'; a++)
            {
                if (isvalid(board, x, y, a)) //合法就循环放入1-9试一试
                {
                    board[x][y] = a;
                    if (back(board, x, y + 1))
                    { //下一个成功找到答案，回溯
                        cout << "已完成寻找" << step_count++ << "个数\n";
                        return true;
                    }
                    board[x][y] = '.'; //这个答案不合适，换回去
                }
            }
            return false;
        }
        return false;
    }
};

int main()
{
    const int boardsize = 9;
    vector<vector<char>> myboard(boardsize);
    cout << "请输入矩阵，数字或者'.'\n";
    for (int i = 0; i < 9; i++)
    {
        myboard[i] = vector<char>(boardsize);
        for (int j = 0; j < 9; j++)
        {
            cin >> myboard[i][j];
        }
    }
    cout << "输入完成\n";
    Solution boardsolution;
    boardsolution.solveShuDu(myboard);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << myboard[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
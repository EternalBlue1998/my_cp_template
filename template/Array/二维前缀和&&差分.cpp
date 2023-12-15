#include <bits/stdc++.h>
using namespace std;

//二维前缀和
class PrefixSum{
    vector<vector<int>> pre;
public:
    PrefixSum(vector<vector<int>> &matrix) {
        int n = matrix.size(), m = matrix[0].size();
        pre.resize(n + 1, vector<int>(m + 1));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + matrix[i][j];
            }
        }
    }
    int get(int x1, int y1, int x2, int y2) {
        //左上(x1, y1)，右下(x2, y2)
        return pre[x2 + 1][y2 + 1] - pre[x2 + 1][y1] - pre[x1][y2 + 1] + pre[x1][y1];
    }
};

//二维差分
vector<vector<int>> D;      //差分数组, 按上面的方式得到前缀和pre后, pre[i + 1][j + 1]为原数组A[i][j]
//将区域左上(x1, y1)，右下(x2, y2)内所有区块加上d
void update(int x1, int y1, int x2, int y2, int d) {
    D[x1][y1] += d;
    D[x1][y2 + 1] -= d;
    D[x2 + 1][y1] -= d;
    D[x2 + 1][y2 + 1] += d;
}

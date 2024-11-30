#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "vertex.cpp"
#include "utils.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    // グラフデータを読み込み
    vector<Vertex> vtxs = read_graph_data("sample.txt");

    string log = "Q,sigma,delta,";     // 履歴
    vector<int> crt_id = {0}, prev_id; // nodeのid (分岐するから、vectorで管理)

    string input = argv[1];           // 入力記号列
    string accepted_lambda = argv[2]; // 受理条件の文字列

    // 記号列をなぞる。遷移状況をcsv形式で記録する
    for (const char &v : input)
    {
        prev_id = crt_id;
        crt_id = vector<int>(0);

        for (const int &i : prev_id)
        {
            for (const int &t : vtxs[i].to[v])
            {
                crt_id.push_back(t);
                log += "q" + to_string(i) + "," + v + "," + "q" + to_string(t) + "\n";
            }
        }
    }

    // 最後に到達したnodeのlambdaを取得し、受理したかどうかを出力
    for (const int &i : crt_id)
    {
        if (vtxs[i].lambda == accepted_lambda)
        {
            cout << "Accepted!!" << endl;
            return 0;
        }
    }
    cout << "Rejected!!" << endl;

    return 0;
}

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "vertex.cpp"
#include "utils.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Error: Invalid Input!!" << endl;
        return 0;
    }

    string input = argv[1];       // 入力記号列
    string accepted_lambda = "1"; // 受理条件の文字列
    if (argc > 2)
    {
        accepted_lambda = argv[2];
    }

    // グラフデータを読み込み
    vector<Vertex> vtxs = read_graph_data("sub_graph.txt");
    cout << "vtxs length: " << vtxs.size() << endl;
    for (int i = 0; i < vtxs.size(); i++)
    {
        cout << vtxs[i].to_str() << endl;
    }

    string log = "Q,sigma,delta,\n";   // 履歴
    vector<int> crt_id = {0}, prev_id; // nodeのid (分岐するから、vectorで管理)

    cout << "input: " << input << endl;
    cout << "lambda: " << accepted_lambda << endl;

    // 記号列をなぞる。遷移状況をcsv形式で記録する
    for (const char &v : input)
    {
        prev_id = crt_id;
        crt_id = vector<int>(0);

        for (const int &i : prev_id)
        {
            for (const int &t : vtxs[i].to[int(v - '0')])
            {
                crt_id.push_back(t);
                log += "q" + to_string(i) + "," + v + "," + "q" + to_string(t) + "\n";
            }

            // もし遷移先がなかったら、-で埋める
            if (!vtxs[i].to[int(v - '0')].size())
            {
                log += "q" + to_string(i) + "," + v + "," + "-" + "\n";
            }
        }
    }

    // 遷移表を書き出し
    ofstream file("table.csv"); // 遷移表
    file << log << endl;

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

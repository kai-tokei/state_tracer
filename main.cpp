#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <math.h>

#include "vertex.cpp"
#include "utils.cpp"

using namespace std;
namespace fs = std::filesystem;

string binary(int bina)
{
    int ans = 0;
    for (int i = 0; bina > 0; i++)
    {
        ans = ans + (bina % 2) * pow(10, i);
        bina = bina / 2;
    }
    return to_string(ans);
}

// トレース結果から、受理されるかどうかを判定
bool is_accepted(vector<Vertex> &vtxs, vector<int> &crt_id, string &accepted_lambda)
{
    bool is_accepted = false;
    // 最後に到達したnodeのlambdaを取得し、受理したかどうかを出力
    for (const int &i : crt_id)
    {
        is_accepted |= vtxs[i].lambda == accepted_lambda;
    }
    return is_accepted;
}

// 頂点をトレースする
string trace(vector<Vertex> &vtxs, string input, vector<int> &crt_id)
{
    string log = "";
    vector<int> prev_id;

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
                log += "q" + to_string(i) + "," + v + "," + "q" + to_string(t) + "," + vtxs[t].lambda + "\n";
            }

            // もし遷移先がなかったら、-で埋める
            if (!vtxs[i].to[int(v - '0')].size())
            {
                log += "q" + to_string(i) + "," + v + "," + "-,-" + "\n";
            }
        }
        log += ",,,,\n";
    }

    return log;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Error: Invalid Augmunts!!, (path) (input string) [lambda]" << endl;
        return 0;
    }
    string graph_file_path = argv[1]; // 読み込むファイルのpath
    string input = "-1";              // 入力記号列
    string accepted_lambda = "1";     // 受理条件の文字列
    if (argc > 2)
    {
        input = argv[2];
    }
    if (argc > 3)
    {
        accepted_lambda = argv[3];
    }

    vector<Vertex> vtxs = read_graph_data(graph_file_path); // グラフデータを読み込み
    string log = "Q,sigma,delta,lambda,\n";                 // 履歴

    if (input == "-1")
    {
        for (int i = 0; i <= 100; i++)
        {
            vector<int> crt_id = {0};             // nodeのid (分岐するから、vectorで管理)
            log = trace(vtxs, binary(i), crt_id); // グラフのトレース
            if (is_accepted(vtxs, crt_id, accepted_lambda))
            {
                cout << i << ": " << binary(i) << endl;
            }
        }
    }
    else
    {
        vector<int> crt_id = {0};                                                                   // nodeのid (分岐するから、vectorで管理)
        log = trace(vtxs, input, crt_id);                                                           // グラフのトレース
        cout << (is_accepted(vtxs, crt_id, accepted_lambda) ? "Accepted!!" : "Rejected!!") << endl; // 受理したかどうかを
    }

    // 遷移表を書き出し
    fs::create_directories("tables");
    ofstream file("tables/" + input + "_" + (is_accepted ? "Accepted!!" : "Rejected!!") + "_table.csv"); // 遷移表
    file << log << endl;
    file << ",,," << (is_accepted ? "Accepted!!" : "Rejected!!") << "," << endl;
}

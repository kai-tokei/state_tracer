#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "vertex.cpp"
#include "utils.cpp"

using namespace std;

int main()
{
    // グラフデータを読み込み
    vector<Vertex> vtxs = read_graph_data("sample.txt");

    // 記号列を読み込み
    // 記号列をなぞる。遷移状況をcsv形式で記録する
    // 最後に到達したnodeのlambdaを取得し、出力

    return 0;
}

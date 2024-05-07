#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "Table.h"
using namespace std;
namespace fs = filesystem;
vector<string>filenames;
int main() {
	string folder_path = "songxml"; // 更改为你的文件夹路径
    ofstream out("out.txt");
	for (const auto& entry : fs::directory_iterator(folder_path)) {
		if (entry.path().extension() == ".xml") {
			filenames.push_back(entry.path());
            string s=entry.path();
			// 这里可以对找到的文件进行处理
            Table t(s);
            t.output(out);
		}
	}
	out<<"ok";
    return 0;
}
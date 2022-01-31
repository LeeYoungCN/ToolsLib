#ifndef FILE_PRIORITY_H
#define FILE_PRIORITY_H
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include "public_typedef.h"
#include "public_macro.h"
using namespace std;

enum FileParaIndex : UINT32 {
    DIRECTORY,
    PRIORITY,
    NUM,
    OWNER,
    GROUP,
    SIZE,
    MONTH,
    DAY,
    TIME,
    NAME,
    FULL_NAME,
    INDEX_CNT
};

class FilePriority {
public:
    FilePriority(const char *oldFileName, const char *newFileName);
    ~FilePriority();
    void Run();
private:
    void ReadOldFile();
    void GetFileStrInfo(const string &fileStr, vector<string> &fileInfo);
    void RefreshSizeInfo(const vector<string> &fileInfo);

    void WriteNewFile();
    void WriteLine(const vector<string> &fileInfo);
    // 文件名
    string oldFileName;
    string newFileName;
    // 文件流
    ifstream oldFile;
    ofstream newFile;
    // 正则表达式模式
    regex folderPattern{".*:$"};                   // 路径模式
    regex filePattern{"^.{1}([-r][-w][-x]){3}.*"}; // 文件模式
    //
    vector<vector<string>> fileInfoVec;
    vector<UINT64> maxSizeInfo = vector<UINT64>(FileParaIndex::INDEX_CNT);
    vector<string> titleInfo;
};

#endif // FILE_PRIORITY_H

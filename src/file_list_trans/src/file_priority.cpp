#include "file_priority.h"
#include "string_public_func.h"

using namespace UTF8;

const char SPLIT_CHAR = ' ';
const UINT32 SUFFIX_SPACE_NUM = 1;
const string TITLE_INFO[FileParaIndex::INDEX_CNT] = {
    "文件地址",
    "文件权限",
    "文件数量",
    "文件Owner",
    "文件属组",
    "文件大小",
    "修改时间-月",
    "修改时间-日",
    "修改时间-时分",
    "文件名称"
    "文件全称"
};

const UINT32 PRINT_ORDER[] = {
    FileParaIndex::DIRECTORY,
    FileParaIndex::PRIORITY,
    FileParaIndex::OWNER,
    FileParaIndex::GROUP,
    FileParaIndex::FULL_NAME
};

FilePriority::FilePriority(const char *oldFileName, const char *newFileName) :
    oldFileName(string(oldFileName)), newFileName(string(newFileName))
{
    titleInfo = vector<string>(TITLE_INFO, TITLE_INFO + FileParaIndex::INDEX_CNT);
    RefreshSizeInfo(titleInfo);
}

FilePriority::~FilePriority()
{
    if (oldFile.is_open()) {
        oldFile.close();
    }
    if (newFile.is_open()) {
        newFile.close();
    }
}

void FilePriority::Run()
{
    ReadOldFile();
    WriteNewFile();
}

void FilePriority::ReadOldFile()
{
    oldFile.open(oldFileName.c_str(), ios::in);
    if (!oldFile.is_open()) {
        cout << oldFileName << " open fail!" << endl;
        return;
    }
    string tmpStr;
    string tmpFolder;
    while(getline(oldFile, tmpStr)) {
        if (regex_match(tmpStr, folderPattern)) {
            tmpStr.pop_back();
            if (tmpStr.back() == '/') {
                tmpStr.pop_back();
            }
            tmpFolder = tmpStr;
        }
        if (regex_match(tmpStr, filePattern)) {
            vector<string> fileInfo(FileParaIndex::INDEX_CNT);
            fileInfo[FileParaIndex::DIRECTORY] = tmpFolder;
            GetFileStrInfo(tmpStr, fileInfo);
            fileInfoVec.emplace_back(fileInfo);
            RefreshSizeInfo(fileInfo);
        }
    }
    cout << oldFileName << " read OK!" << endl;
    oldFile.close();
}

void FilePriority::GetFileStrInfo(const string &fileStr, vector<string> &fileInfo)
{
    string::const_iterator it = fileStr.begin();
    string::const_iterator end = fileStr.end();
    for (UINT32 i = FileParaIndex::PRIORITY; i < FileParaIndex::FULL_NAME; i++) {
        fileInfo[i] = GetNextStr(it, end, SPLIT_CHAR);
    }
    fileInfo[FileParaIndex::FULL_NAME] = fileInfo[FileParaIndex::DIRECTORY] + '/' + fileInfo[FileParaIndex::NAME];
}

void FilePriority::RefreshSizeInfo(const vector<string> &fileInfo)
{
    for (UINT32 i = FileParaIndex::DIRECTORY; i < FileParaIndex::INDEX_CNT; i++) {
        maxSizeInfo[i] = max(maxSizeInfo[i], GetStrSpaceSize(fileInfo[i]));
    }
}

void FilePriority::WriteNewFile()
{
    newFile.open(newFileName,  ios::trunc|ios::out);
        if (!newFile.is_open()) {
        cout << newFileName << " open fail!" << endl;
        return;
    }
    WriteLine(titleInfo);
    for (const auto& fileInfo : fileInfoVec) {
        WriteLine(fileInfo);
    }
    cout << newFileName << " write OK!" << endl;
    newFile.close();
}

void FilePriority::WriteLine(const vector<string> &fileInfo)
{
    UINT32 arrSize = ITEM_OF(PRINT_ORDER);
    UINT32 index = 0;
    for (UINT32 i = 0; i < arrSize - 1; i++) {
        index = PRINT_ORDER[i];
        newFile << GetStrWithSpace(fileInfo[index], maxSizeInfo[index], SUFFIX_SPACE_NUM);
    }
    index = PRINT_ORDER[arrSize - 1];
    newFile << fileInfo[index] << endl;
}

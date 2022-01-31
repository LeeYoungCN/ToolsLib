#include <iostream>
#include "file_priority.h"

using namespace std;

const int NEW_FILE_INDEX = 1;
const int OLD_FILE_INDEX = 2;
const int INPUT_PARA_NUM = 3;

int main(int argc, char *argv[])
{
    if (argc < INPUT_PARA_NUM) {
        cout << "input error argc =" << argc << endl;
        return 1;
    }

    FilePriority fp(argv[NEW_FILE_INDEX], argv[OLD_FILE_INDEX]);
    fp.Run();

    return 0;
}

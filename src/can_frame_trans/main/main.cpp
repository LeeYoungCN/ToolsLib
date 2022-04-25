#include <iostream>
#include "can_frame_trans.h"
#include "public_typedef.h"

using namespace std;

SINT32 main(SINT32 argc, CHAR *argv[])
{
    CanFrameTrans f;
    f.TransFrame(argc, argv);
    return 0;
}

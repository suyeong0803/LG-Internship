extern "C"
{
#include "libavformat/avformat.h"
#include <libavutil/mathematics.h>
}

#include <iostream>


#pragma warning(disable:4996)

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")

#include <string>
#include <vector>

#include "videoInfo.h"

void concat(std::vector<videoInfo> folder);
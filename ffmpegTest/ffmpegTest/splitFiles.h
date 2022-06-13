#pragma once

extern "C"
{
#include "libavformat/avformat.h"
#include <libavutil/mathematics.h>
}

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")

#include "videoInfo.h"
#include <string>

void split(int start_time, int end_time, std::string filePath);
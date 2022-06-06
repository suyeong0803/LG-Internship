#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>

#include <io.h>
#include <stdlib.h>

#include <time.h>

#include "checkType.h"

#define F_OK 0
#define access _access

//int doConvert(std::string input, std::string output)
//{
//    // 실행할 명령어 (ffmpeg -i INPUTFILE OUTPUTFILE)
//    std::string command = "";
//
//    command = "ffmpeg -i " + input + " -q:v 0 " + output;
//    system(command.c_str());
//
//    return 0;
//}

//int checkType(std::string input, std::string type)
//{
//
//    if (access(input.c_str(), F_OK) != 0) {
//        // file doesn't exists
//        printf("%s : Invalid Input Path\n", input);
//        return -1;
//    }
//
//    std::string input_type = input.substr(input.size() - 3, 3); // input의 파일 형식 저장 ( mpg , mp4 )
//
//    std::string output = input.substr(0, input.size() - 4) + "_output"; // input과 같은 이름의 파일_output
//
//    if (type == "MPEG2")
//    {
//        if (input_type == "mp4")
//        {
//            output += ".mpg";
//        }
//
//        else if (input_type == "mpg")
//        {
//            printf("%s : already MPEG2\n", input);
//            return -1;
//        }
//
//        else
//        {
//            printf("%s : Invalid Input Type", input);
//            return -1;
//        }
//    }
//
//    else if (type == "MPEG4")
//    {
//        if (input_type == "mpg")
//        {
//            output += ".mp4";
//            // strcat_s(output, sizeof(output), ".mp4"); // output의 형식을 mpg으로 설정
//        }
//
//        else if (input_type == "mp4")
//        {
//            printf("%s : already MPEG4\n", input);
//            return -1;
//        }
//
//        else
//        {
//            printf("%s : Invalid Input Type", input);
//            return -1;
//        }
//    }
//
//    else
//    {
//        printf("%s : Invalid Converting Type", input);
//        return -1;
//    }
//
//    doConvert(input, output);
//
//    return 0;
//}

int main()
{
    clock_t start = clock();

    for (int i = 0; i < 2; i++)
    {
        std::string input, type;
        std::cin >> input >> type;

        checkType* check = new checkType();

        if (check->callConverter(input, type) == -1) i--;
    }

    clock_t end = clock();

    printf("%f", (double)(end - start));

    return 0;
}
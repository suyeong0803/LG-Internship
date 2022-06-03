#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>

#include <io.h>
#include <stdlib.h>
#define F_OK 0
#define access _access

int doConvert(std::string input, std::string output)
{
    // popen 실행할 명령어 (ffmpeg -i INPUTFILE OUTPUTFILE)
    char command[100] = "";

    std::string str = "";
    str = "ffmpeg -i " + input + " -q:v 0 " + output;

    /*strcat_s(command, sizeof(command), "ffmpeg -i ");
    strcat_s(command, sizeof(command), input);
    strcat_s(command, sizeof(command), " -q:v 0 ");
    strcat_s(command, sizeof(command), output);*/

    // printf("%s\n", command);

    // (쉘 명령, 입력(r) or 출력(w))
    system(command);

    return 0;
}

int checkType(std::string input, std::string type)
{
    
    if (access(input, F_OK) != 0) {
        // file doesn't exists
        printf("%s : Invalid Input Path\n", input);
        return -1;
    }

    std::string input_type = input.substr(input.size() - 3, 3); // input의 파일 형식 저장 ( mpg , mp4 )
    //strncpy_s(input_type, sizeof(input_type), input + (strlen(input) - 3), 3);
   
    std::string output = input.substr(input.size() - 4);
    //strncpy_s(output, sizeof(output), input, strlen(input) - 4); // input과 같은 이름으로 output 파일 만듦 ( 형식 제외하고 )

    if (type == "MPEG2")
    {
        if (input_type == "mp4")
        {
            output += ".mpg";
            // strcat_s(output, sizeof(output), ".mpg"); // output의 형식을 mpg으로 설정
        }

        else if (input_type == "mpg")
        {
            printf("%s : already MPEG2\n", input);
            return -1;
        }

        else
        {
            printf("%s : Invalid Input Type", input);
            return -1;
        }
    }

    else if (type == "MPEG4")
    {
        if (input_type == "mpg")
        {
            output += ".mp4";
            // strcat_s(output, sizeof(output), ".mp4"); // output의 형식을 mpg으로 설정
        }

        else if (input_type == "mp4")
        {
            printf("%s : already MPEG4\n", input);
            return -1;
        }

        else
        {
            printf("%s : Invalid Input Type", input);
            return -1;
        }
    }

    else
    {
        printf("%s : Invalid Converting Type", input);
        return -1;
    }

    doConvert(input, output);

    return 0;
}

int main()
{

    for (int i = 0; i < 2; i++)
    {
        std::string input, type;
        std::cin << input << type;

        //scanf_s("%s %s", input, sizeof(input), type, sizeof(type));
        if (checkType(input, type) == -1) i--;
    }

    return 0;
}

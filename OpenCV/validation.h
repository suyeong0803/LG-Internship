#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>

// ���� ���� ���� ���� ���
#include <boost/filesystem.hpp>

#include "MyConverter.h"

class validation
{
public:
    bool isChecked = false;
    char input[128];
    std::string type;

    int checkPath(std::string input)
    {
        if (input.empty()) return -4; 

        boost::filesystem::path p(input);
        if (boost::filesystem::exists(p))
        {
            if (boost::filesystem::is_regular_file(p))
            {
                std::string extension = boost::filesystem::extension(input); // .mp4

                if (extension == ".mpg" || extension == ".mp4") return 0;
                else return -1; // mpg, mp4 �� ����
            }

            else if (boost::filesystem::is_directory(p)) return -2; // ���丮�� ���
            else return -3; // ���������� ���丮, ���� ��� �ƴ� ���
        }
        else return -3; // ���� ����
    }

    int callConverter(std::string input, std::string convertType)
    {
        if (!isChecked) return -2;
        if (input.empty()) return -4;

        boost::filesystem::path p(input);
        type = boost::filesystem::extension(p); // input�� ���� ���� ���� ( mpg , mp4 )
        std::string stem = "";
        for (int i = 0; i < input.length() - type.length(); i++) stem += input[i];

        if (convertType == ".mpg")
        {
            if (type == convertType) return -1;
            else
            {
                MPEG2Converter* converter = new MPEG2Converter();
                converter->convert(stem); // ���� �� �̸��� ����

                return 1;
            }
        }

        else if (convertType == ".mp4")
        {
            if (type == convertType) return -1;
            else
            {
                MPEG4Converter* converter = new MPEG4Converter();
                converter->convert(stem); // ���� �� �̸��� ����

                return 2;
            }
        }

        return -3;
    }
};
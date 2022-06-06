#include <string>
#define interface struct

interface Converter
{
	virtual void convert(std::string input) = 0;
};

class MPEG2Converter : public Converter
{
public:
	virtual void convert(std::string input)
	{
		std::string command = "ffmpeg -i " + input + ".mp4 -q:v 0  " + input + "_convert.mpg";
		system(command.c_str());
	}
};

class MPEG4Converter : public Converter
{
public:
	virtual void convert(std::string input)
	{
		std::string command = "ffmpeg -i " + input + ".mpg -q:v 0  " + input + "_convert.mp4";
		system(command.c_str());
	}
};
#include <stdio.h>
#include <string.h>

#define W 1280
#define H 720

unsigned char frame[H][W][3] = { 0 };

int main()
{
    // Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
   
    char filePath[100], savePath[100];
    scanf("%s %s", filePath, savePath);

    CString str;
    str += "ffmeg -i " + filePath + " " + savePath;

     // (쉘 명령, 입력(r) or 출력(w))
    FILE* pipein = _popen(str, "r");

    while (fgets(frame, H * W * 3, pipein)) 

    // Flush and close input and output pipes
    fflush(pipein);
    _pclose(pipein);
}

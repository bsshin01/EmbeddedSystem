#include <stdio.h>
#include <stdlib.h>
#include "textlcd.h"

void printUsage(const char* progName)
{
    printf("Usage:\n");
    printf("  %s                → Clear LCD\n", progName);
    printf("  %s <line> <text>  → Write text to LCD (line: 1 or 2)\n", progName);
}

int main(int argc, char* argv[])
{
    // LCD 초기화
    if (!textLcdInit()) {
        fprintf(stderr, "TextLCD init failed\n");
        return 1;
    }

    // 인자가 없으면 전체 Clear
    if (argc == 1) {
        if (!textLcdClear()) {
            fprintf(stderr, "TextLCD clear failed\n");
            return 1;
        }
        return 0;
    }

    // 인자가 부족하거나 잘못되었을 때
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }

    // 라인 번호 및 메시지 파싱
    int line = atoi(argv[1]);
    const char* message = argv[2];

    if (line < 1 || line > 2) {
        fprintf(stderr, "Invalid line number: %d (must be 1 or 2)\n", line);
        return 1;
    }

    // 텍스트 출력
    if (!textLcdWriteLine(line, message)) {
        fprintf(stderr, "Failed to write to LCD\n");
        return 1;
    }

    return 0;
}

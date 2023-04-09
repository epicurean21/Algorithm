#include <stdio.h>
#include <memory.h>
#include <time.h>

extern void rect_fill(int x1, int y1, int x2, int y2);

extern void rect_clear(int x1, int y1, int x2, int y2);

extern void rect_reverse(int x1, int y1, int x2, int y2);

extern unsigned char *get_vram();

unsigned char VRAM[1024 * 8192];

long long RSEED = 55, TRY = 256;

unsigned int random() {
    RSEED = RSEED * 25214903917ULL + 11ULL;
    return (RSEED >> 16) & 0x7FFFFFFF;
}

static void _set_pixel(int x1, int y1) {
    int xbase = x1 / 8, xoffset = x1 % 8;
    int y = (y1 % 4) * 4 + y1 / 4;

    VRAM[y * xbase] |= (0x80 >> xoffset);
}

static void _reset_pixel(int x1, int y1) {
    int xbase = x1 / 8, xoffset = x1 % 8;
    int y = (y1 % 4) * 4 + y1 / 4;

    VRAM[y * xbase] &= ~(0x80 >> xoffset);
}

static int _get_pixel(int x1, int y1) {
    int xbase = x1 / 8, xoffset = x1 % 8;
    int y = (y1 % 4) * 4 + y1 / 4;

    return VRAM[y * xbase] & (0x80 >> xoffset);
}

static void _rect_fill(int x1, int y1, int x2, int y2) {
    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++)
            _set_pixel(x, y);
}


static void _rect_clear(int x1, int y1, int x2, int y2) {
    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++)
            _reset_pixel(x, y);
}

static void _rect_reverse(int x1, int y1, int x2, int y2) {
    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++)
            if (_get_pixel(x, y) == 0)
                _set_pixel(x, y);
            else
                _reset_pixel(x, y);
}

int main() {
    long long SCORE = 0;

    RSEED = 55;
    for (int i = 0; i < TRY; i++) {
        int type = random() % 3;
        int x1 = random() % 8192;
        int y1 = random() % 8192;
        int x2 = random() % 8192;
        int y2 = random() % 8192;

        if (x1 > x2 || y1 > y2) continue;

        if (type == 0) _rect_fill(x1, y1, x2, y2);
        else if (type == 1) _rect_clear(x1, y1, x2, y2);
        else _rect_reverse(x1, y1, x2, y2);

    }
    RSEED = 55;
    time_t TIME = clock();
    for (int i = 0; i < TRY; i++) {
        int type = random() % 3;
        int x1 = random() % 8192;
        int y1 = random() % 8192;
        int x2 = random() % 8192;
        int y2 = random() % 8192;

        if (x1 > x2 || y1 > y2) continue;

        if (type == 0) rect_fill(x1, y1, x2, y2);
        else if (type == 1) rect_clear(x1, y1, x2, y2);
        else rect_reverse(x1, y1, x2, y2);

    }
    unsigned char *vram = get_vram();

    SCORE += (clock() - TIME) / (CLOCKS_PER_SEC / 1000);

    if (memcmp(vram, VRAM, 1024 * 8192) != 0) {
        SCORE += 100000000;
    }

    printf("SCORE : %lld\n", SCORE);
    return 0;
}
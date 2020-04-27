#include <curses.h>

#include <curspriv.h>
#include <emscripten.h>

# define A(x) ((chtype)x | A_ALTCHARSET)

chtype acs_map[128] =
{
        A(0), A(1), A(2), A(3), A(4), A(5), A(6), A(7), A(8), A(9),
        A(10), A(11), A(12), A(13), A(14), A(15), A(16), A(17), A(18),
        A(19), A(20), A(21), A(22), A(23), A(24), A(25), A(26), A(27),
        A(28), A(29), A(30), A(31), ' ', '!', '"', '#', '$', '%', '&',
        '\'', '(', ')', '*',

        A(0x1a), A(0x1b), A(0x18), A(0x19),

        '/',

        0xdb,

        '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
        '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
        'X', 'Y', 'Z', '[', '\\', ']', '^', '_',

        A(0x04), 0xb1,

        'b', 'c', 'd', 'e',

        0xf8, 0xf1, 0xb0, A(0x0f), 0xd9, 0xbf, 0xda, 0xc0, 0xc5, 0x2d,
        0x2d, 0xc4, 0x2d, 0x5f, 0xc3, 0xb4, 0xc1, 0xc2, 0xb3, 0xf3,
        0xf2, 0xe3, 0xd8, 0x9c, 0xf9,

        A(127)
};


void PDC_gotoyx(int row, int col)
{
    EM_ASM_INT({
        term.cursorSet($0, $1);
    }, row, col);
}

void PDC_transform_line(int lineno, int x, int len, const chtype *srcp)
{

    for (int j = 0; j < len; j++) {
        chtype ch = srcp[j];
        int style = 0;

#ifdef CHTYPE_LONG
        if (ch & A_ALTCHARSET && !(ch & 0xff80))
            ch = (ch & (A_ATTRIBUTES ^ A_ALTCHARSET)) | acs_map[ch & 0x7f];
#endif
        if (ch & A_REVERSE)
            style |= 1<<0;
        if (ch & A_UNDERLINE)
            style |= 1<<1;
        if (ch & A_BOLD)
            style |= 1<<4;

        if (ch & A_COLOR) {
            short fg, bg;

            PDC_pair_content(PAIR_NUMBER(ch & A_COLOR), &fg, &bg);
            if (bg) {
                style |= (bg+1) << 8;
                style |= 1<<0;
            } else {
                style |= (fg+1) << 8;
            }
        }

        EM_ASM_INT({
            term.setChar($0, $1, $2, $3);
        }, ch & 0xFF, lineno, x+j, style);
    }
}

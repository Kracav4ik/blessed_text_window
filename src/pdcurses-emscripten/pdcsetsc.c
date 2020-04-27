#include <curspriv.h>
#include <emscripten.h>

int PDC_curs_set(int visibility)
{
    int ret_vis;
    ret_vis = SP->visibility;
    SP->visibility = visibility;

    if (visibility)
        EM_ASM(term.cursorOn());
    else
        EM_ASM(term.cursorOff());

    return ret_vis;
}

int PDC_set_blink(bool blinkon)
{
    if (pdc_color_started)
        COLORS = 16;

    return blinkon ? ERR : OK;
}

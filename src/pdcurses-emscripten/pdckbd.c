#include <curspriv.h>
#include <emscripten.h>

void PDC_set_keyboard_binary(bool on)
{
}

bool PDC_check_key(void)
{
    if ((PDC_get_columns() != SP->cols ||
         PDC_get_rows() != SP->lines) && !SP->resized)
        return TRUE;

    return EM_ASM_INT_V({ return term.inputChar; }) ? TRUE : FALSE;
}

int PDC_mouse_set(void)
{
    return ERR;
}

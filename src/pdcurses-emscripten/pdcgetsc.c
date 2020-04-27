#include <emscripten.h>

int PDC_get_cursor_mode(void)
{
    return EM_ASM_INT_V({ return term.crsrBlinkMode ? 0 : term.crsrBlockMode ? 1 : 2; });
}

int PDC_get_rows(void)
{
    return EM_ASM_INT_V({ return term.conf.rows; });
}

int PDC_get_columns(void)
{
    return EM_ASM_INT_V({ return term.conf.cols; });
}

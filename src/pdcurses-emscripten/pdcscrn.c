#include <curspriv.h>
#include <emscripten.h>
#include <stdlib.h>

static struct {short f, b;} atrtab[PDC_COLOR_PAIRS];

int PDC_scr_open(int argc, char **argv)
{
    SP = calloc(1, sizeof(SCREEN));
    
    if (!SP)
        return ERR;

    EM_ASM(
        term = new Terminal({
            termDiv: 'termDiv',
            handler: function() {},
            x: 0, y: 0,
            initHandler: function() {
                term.charMode = true;
                term.keylock = true;
                term.cursorOn();
                afterInit();
            }
        });
        term.open();
    );

    SP->mono = 0;
    SP->orig_attr = FALSE;
    
    const char* PDC_LINES = getenv("PDC_LINES");
    const char* PDC_COLS = getenv("PDC_COLS");
    if (PDC_COLS && PDC_LINES) {
        EM_ASM_INT({
            term.resizeTo($0, $1);
        }, atoi(PDC_COLS), atoi(PDC_LINES));
    }

    SP->lines = PDC_get_rows();
    SP->cols = PDC_get_columns();

    SP->audible = FALSE;

    PDC_reset_prog_mode();

    return OK;

}

int PDC_resize_screen(int nlines, int ncols)
{
    EM_ASM_INT({
        term.resizeTo($0, $1);
    }, ncols, nlines);

    SP->resized = FALSE;
    SP->cursrow = SP->curscol = 0;

    return OK;
}

void PDC_reset_prog_mode(void)
{
}

void PDC_restore_screen_mode(int i)
{
}

void PDC_save_screen_mode(int i)
{
}

void PDC_init_pair(short pair, short fg, short bg)
{
    atrtab[pair].f = fg;
    atrtab[pair].b = bg;
}

int PDC_pair_content(short pair, short *fg, short *bg)
{
    *fg = atrtab[pair].f;
    *bg = atrtab[pair].b;

    return OK;
}

set(EXE_NAME blessed_text_window)

include_directories(.)

set(PDCURSES_LIB
        curses.h
        curspriv.h
        panel.h

        common/acs437.h
        common/acsgr.h
        common/acsuni.h
        common/font437.h
        common/iconbmp.h

        pdcurses/addch.c
        pdcurses/border.c
        pdcurses/getch.c
        pdcurses/inopts.c
        pdcurses/mouse.c
        pdcurses/printw.c
        pdcurses/slk.c
        pdcurses/addchstr.c
        pdcurses/clear.c
        pdcurses/getstr.c
        pdcurses/insch.c
        pdcurses/move.c
        pdcurses/README.md
        pdcurses/termattr.c
        pdcurses/addstr.c
        pdcurses/color.c
        pdcurses/getyx.c
        pdcurses/insstr.c
        pdcurses/outopts.c
        pdcurses/refresh.c
        pdcurses/touch.c
        pdcurses/attr.c
        pdcurses/debug.c
        pdcurses/inch.c
        pdcurses/instr.c
        pdcurses/overlay.c
        pdcurses/scanw.c
        pdcurses/util.c
        pdcurses/beep.c
        pdcurses/delch.c
        pdcurses/inchstr.c
        pdcurses/kernel.c
        pdcurses/pad.c
        pdcurses/scr_dump.c
        pdcurses/window.c
        pdcurses/bkgd.c
        pdcurses/deleteln.c
        pdcurses/initscr.c
        pdcurses/keyname.c
        pdcurses/panel.c
        pdcurses/scroll.c
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(PDCURSES_LIB
            ${PDCURSES_LIB}

            wincon/pdcgetsc.c
            wincon/pdcsetsc.c
            wincon/pdcclip.c
            wincon/pdckbd.c
            wincon/pdcutil.c
            wincon/pdcdisp.c
            wincon/pdcscrn.c
            wincon/pdcwin.h
    )
endif()

add_library(pdcurses_lib ${PDCURSES_LIB})
target_link_libraries(${EXE_NAME} pdcurses_lib)

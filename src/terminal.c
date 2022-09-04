#include "serial.h"
#include "terminal.h"

void terminal() {
    char* m86logoser = 
                "   __     __)                        ___     __ \r\n"
                "  (, /|  /|       /) /)          /) (   )  /    \r\n"
                "    / | / |  _   // // _   __  _(/  .--'  /__   \r\n"
                " ) /  |/  |_(_(_(/_(/_(_(_/ (_(_(_ (___) (__ )  \r\n"
                "(_/   '     \r\n";

    ser_clear();
    ser_print(m86logoser);
    ser_print("Welcome to the MIST shell\r\n");

    char* inp;

    while(inp != "exit") {
        ser_print("$ ");
        ser_readstr(inp, 100);
        ser_print("\r\n");
        ser_print(inp);
        ser_print("\r\n");
    }
}
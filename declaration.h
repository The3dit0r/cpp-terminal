#pragma once

#include "./lib/global/global.h"
#include "./lib/printer/printer.h"

Terminal terminal = Terminal();
Printer printer = Printer(terminal.width, terminal.height - 1);

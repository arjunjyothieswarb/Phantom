#ifndef __TERM_UTILS_HPP__
#define __TERM_UTILS_HPP__

#include <termios.h>
#include <unistd.h>

static termios orig_termios;

void enableRawMode();
void disableRawMode();

#endif
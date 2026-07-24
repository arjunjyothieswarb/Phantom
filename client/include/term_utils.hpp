#ifndef __TERM_UTILS_HPP__
#define __TERM_UTILS_HPP__

#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void enableRaw();
void disableRaw();

#endif
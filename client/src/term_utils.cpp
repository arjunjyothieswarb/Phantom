#include "term_utils.hpp"

void enableRawMode()
{
    // Store the original settings
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON | ISIG); // No echo | disable line buffering | disable sig term
    raw.c_cc[VMIN] = 1;                     // Return after 1 byte
    raw.c_cc[VTIME] = 0;                    // No timeout

    // Update settings
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode()
{
    // Restoring the original settings
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
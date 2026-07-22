#include <iostream>
#include <cstdio>
#include <thread>
#include <atomic>
#include <string>
#include <unistd.h>
#include <termios.h>

#define INPUT_SAMPLE_RATE_MS 300

std::atomic<char> key_press;
std::atomic<bool> isRunning = true;
std::atomic<int64_t> prev_stamp = 0;

void reg_input(void)
{
    std::chrono::time_point<std::chrono::steady_clock> sys_clk_stamp;
    char c;
    while (true)
    {
        // key_press = getchar();
        tcflush(STDIN_FILENO, TCIFLUSH);
        read(STDIN_FILENO, &c, 1);
        key_press = c;
        sys_clk_stamp = std::chrono::steady_clock::now();
        prev_stamp = std::chrono::duration_cast<std::chrono::milliseconds>(sys_clk_stamp.time_since_epoch()).count();
        if (key_press == 'q')
        {
            isRunning = false;
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(INPUT_SAMPLE_RATE_MS));
    }
}

void disp_output(void)
{
    std::int64_t diff;
    std::chrono::time_point<std::chrono::steady_clock> sys_clk_stamp;
    while (isRunning)
    {
        sys_clk_stamp = std::chrono::steady_clock::now();
        diff = std::chrono::duration_cast<std::chrono::milliseconds>(sys_clk_stamp.time_since_epoch()).count() - prev_stamp;
        if (diff > 200)
        {
            // std::cout << "diff: " << diff << std::endl;
            key_press = ' ';
        }

        std::cout << "Key Pressed: '" << key_press << "'\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(INPUT_SAMPLE_RATE_MS * 2));
    }

    return;
}

struct termios orig_termios;

void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON | ISIG); // No echo | disable line buffering | disable sig term
    raw.c_cc[VMIN] = 1;                     // Return after 1 byte
    raw.c_cc[VTIME] = 0;                    // No timeout

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

int main(int argc, char **argv)
{
    enableRawMode();
    std::thread inputThread(&reg_input);
    std::thread outputThread(&disp_output);

    inputThread.join();
    outputThread.join();

    disableRawMode();
    return 0;
}
#include <iostream>
#include <thread>
#include <atomic>

#include "term_utils.hpp"
#include "udp_client_utils.hpp"

#define UDP_TRANSMISSION_RATE_MS 100

UDPClient myUDPClient;

std::atomic<char> msg_buff;
std::atomic<bool> isRunning;
std::atomic<uint64_t> prev_time;

char buff;

void capture_key_press()
{
    while (isRunning)
    {
        // Flushing the input to ensure only the
        // latest press gets transmitted
        tcflush(STDIN_FILENO, TCIFLUSH);
        read(STDIN_FILENO, &msg_buff, 1);

        buff = msg_buff.load();
        prev_time = get_micros();
        if (buff == 'q')
            isRunning = false;

        std::cout << "Key Pressed: " << buff << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return;
}

int main(int argc, char **argv)
{
    int msg_len = 1;
    int status;

    // Initializing client
    status = myUDPClient.init_client();
    if (status)
        return status;

    // Set running to true
    isRunning = true;

    // Setting terminal to non-canonical mode
    enableRawMode();

    // Start key capture thread
    std::thread cap_key_thread(&capture_key_press);

    while (isRunning)
    {
        if (get_micros() - prev_time < UDP_TRANSMISSION_RATE_MS)
            myUDPClient.send_msg(&buff, msg_len);

        std::this_thread::sleep_for(std::chrono::milliseconds(UDP_TRANSMISSION_RATE_MS));
    }

    // Thread rejoins here
    cap_key_thread.join();

    // Restorting default terminal settings
    disableRawMode();

    return 0;
}
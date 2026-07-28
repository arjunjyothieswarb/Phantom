#include <iostream>
#include <string>
#include <thread>

#include "udp_serv_utils.hpp"
#include "motor_controls.hpp"

#define MAX_HISTORY_MS 200
#define SLEEP_DURATION_MS 300

char buf;

UDPServer myUDP;
int status;

CarControl phantom_ctl;

int main(int argc, char **argv)
{
    status = myUDP.init_server();
    if (status)
        return status;

    std::thread recv_thread(&UDPServer::recv_buff, &myUDP, &buf);

    phantom_ctl.driver.set_motor_state(MOTOR_LEFT, HIGH);
    phantom_ctl.driver.set_motor_state(MOTOR_RIGHT, HIGH);

    while (1)
    {
        if ((get_micros() - myUDP.get_time_stamp()) > MAX_HISTORY_MS)
            buf = '\0';
        std::cout << "Recieve: " << buf << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION_MS));

        switch (buf)
        {
        case 'w':
            phantom_ctl.setCMD(CMD_UP);
            break;
        case 'a':
            phantom_ctl.setCMD(CMD_LEFT);
            break;
        case 's':
            phantom_ctl.setCMD(CMD_DOWN);
            break;
        case 'd':
            phantom_ctl.setCMD(CMD_RIGHT);
            break;
        default:
            phantom_ctl.setCMD(CMD_STOP);
        }
    }

    recv_thread.join();
    return 0;
}
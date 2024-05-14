#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <set>

#include "ESPNOW_manager.h"
#include "wifi.h"

using namespace std;

static uint8_t cast_addr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
ESPNOW_manager *espnow;

struct remote {
    uint8_t addr[6];
};

inline bool operator<(const remote& lhs, const remote& rhs)
{
  return lhs.addr[5] < rhs.addr[5];
}

set<struct remote> remotes;
shared_mutex remotes_mutex;

void print_mac(uint8_t addr[6]) {
    for (int i = 0; i < 5; ++i)
        cout << setw(2) << setprecision(2) << setfill('0') << hex << (unsigned)addr[i] << ":";
    cout << setw(2) << setprecision(2) << setfill('0') << hex << (unsigned)addr[5];
}

void register_remote(uint8_t mac[6]) {
    unique_lock lock(remotes_mutex);
    remote r;
    memcpy(r.addr, mac, 6);
    remotes.insert(r);
    cout << " [REGISTERED]";
}

void callback(uint8_t src_mac[6], uint8_t *data, int len) {
    print_mac(src_mac);
    cout << " (" << dec << len << ")> ";

    if (len == sizeof(wifi_msg_s)) {
        wifi_msg_s* msg = (wifi_msg_s*)data;
        switch(msg->type) {
            case DISCOVER:
                cout << "DISCOVER";
                break;
            case ACKNOWLEDGE:
                cout << "ACKNOWLEDGE";
                register_remote(src_mac);
                break;
            default:
                cout << "UNKNOWN";
        }
    }
    cout << endl;
}

void send(uint8_t addr[6], wifi_msg_s* msg) {
    print_mac(addr);
    cout << " (" << dec << sizeof(wifi_msg_s) << ")< " << msg->type << endl;
    espnow->set_dst_mac(addr);
    espnow->send((uint8_t*)msg, sizeof(wifi_msg_s));
}

void discover() {
    wifi_msg_s msg = {
        .type = DISCOVER
    };
    send(cast_addr, &msg);
}

void control(bool on) {
    bool ron = false;
    for (auto remote : remotes) {
        wifi_msg_s msg = {
            .type = CONTROL,
            .target = -1,
            .on = on != ron,
            .color = 0x228B22,
        };
        send(remote.addr, &msg);
        ron = !ron;
    }
}

int main(int argc, char **argv) {
    assert(argc > 1);
    nice(-20);
    espnow = new ESPNOW_manager(argv[1]);
    espnow->set_recv_callback(&callback);
    espnow->start();

    discover();

    auto last = chrono::high_resolution_clock::now();
    bool on = false;

    while (1) {
        this_thread::yield();
        auto now = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(now - last);
        if (duration >= chrono::milliseconds{1000}) {
            cout << "test" << endl;
            last = now;
            control(on);
            on = !on;
        }
    }
    espnow->end();
}

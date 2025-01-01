#include "ProxyBot.hpp"
#include "IPC.hpp"

int main() {
    std::shared_ptr<ProxyBot>bot(new ProxyBot);
    IPCdispatcher ipc{bot};
    try{
        bot->start();
    }
    catch (TgBot::TgException& msg) {
        std::cout << msg.what();
    }
    return 0;
}
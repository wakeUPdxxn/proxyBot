#include "ProxyBot.hpp"

int main() {
    ProxyBot bot;
    try {
        bot.start();
    }
    catch (TgBot::TgException& msg) {
        std::cout << msg.what();
    }
    return 0;
}
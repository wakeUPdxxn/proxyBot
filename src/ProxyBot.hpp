#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <tgbot/tgbot.h>

using namespace TgBot;

class ProxyBot {

public:
    ProxyBot();
    ~ProxyBot();
    void start();

private:
    struct Target {
        std::string os;
        std::string ip;
    };
    struct User {
        std::unordered_map<uint64_t, Target*>targets;
    };
    std::string token{ "7104114958:AAEa7_p6UMOJkcrR_-OGRHKQJSEBb3J4EhY" };
    TgBot::Bot bot{ token };

    TgBot::InlineKeyboardMarkup::Ptr targetsKeyboard;

    std::unordered_map<uint64_t, User*>users;
    std::vector<uint64_t>allowedId;

    std::vector<TgBot::InlineKeyboardButton::Ptr> menuRow0;

    void parseAllowedList();
    void setCommands();
    void setEventFunc();
};
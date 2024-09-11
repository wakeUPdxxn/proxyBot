#include "ProxyBot.hpp"

using namespace std;

ProxyBot::ProxyBot() {
    targetsKeyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
    parseAllowedList();
    for (const auto& id : allowedId) {
        users.emplace(id, new User);
    }
}

ProxyBot::~ProxyBot() {
    for (auto& user : users) {
        if (user.second != nullptr) {
            delete user.second;
            user.second = nullptr;
        }
    }
}

void ProxyBot::parseAllowedList(){
    fstream in;
    in.open("allowedUsersId", ios::in);

    stringstream ss;
    ss << in.rdbuf();

    uint64_t id;
    while (ss >> id) {
        allowedId.push_back(id);
    }
}

void ProxyBot::start() {
    try {
        setCommands();
        setEventFunc();
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            cout << "Long poll started \n";
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        cout << e.what() << endl;
    }
}

void ProxyBot::setCommands() {

    vector<BotCommand::Ptr> commands;
    BotCommand::Ptr cmdArray(new BotCommand);
    cmdArray->command = "targets";
    cmdArray->description = "Show all your targets";

    commands.push_back(cmdArray);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "start";
    cmdArray->description = "Start listening";
    commands.push_back(cmdArray);

    bot.getApi().setMyCommands(commands);
}

void ProxyBot::setEventFunc() {
    bot.getEvents().onCommand("start", [&](Message::Ptr message) {
        std::unordered_map<uint64_t, User*>::iterator user;

        user = users.find(message->from->id);
        if(user!=users.end()) {
            bot.getApi().sendMessage(message->chat->id, "Listening...");
        }
        else {
            bot.getApi().sendMessage(message->chat->id, "You are have no permission to this command!");
        }
        });
    bot.getEvents().onCommand("targets", [&](Message::Ptr message) {
        auto caller = users.find(message->from->id);
        if (caller != users.end()) {
            bot.getApi().sendMessage(message->chat->id, "Your actual targets is:");
            //for (const auto& target : caller->second->targets) {
                std::string response = "target 1 - target 2 -";
                bot.getApi().sendMessage(message->chat->id, response,"MarkdownV2");
            //}
        }
        else {
            bot.getApi().sendMessage(message->chat->id, "You are have no permission to this command!");
        }
        });

    bot.getEvents().onCallbackQuery([&](CallbackQuery::Ptr query) {
        cout << "Query data" << query->data;
        if (!StringTools::startsWith(query->data, "id")) {
            string response = "Wrong Command";
            bot.getApi().sendMessage(query->message->chat->id, response);
        }
        });
}

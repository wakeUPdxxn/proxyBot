#include "ProxyBot.hpp"

using namespace std;

ProxyBot::ProxyBot() {
    targetsMarkup = std::make_shared<TgBot::InlineKeyboardMarkup>();
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

void ProxyBot::performTargetsColumn(const std::string &id) {
    TgBot::InlineKeyboardButton::Ptr targetButton(new TgBot::InlineKeyboardButton);
    targetButton->text = "target id: "+ id;
    targetButton->callbackData = id;
    targetsColumn.push_back(targetButton);

    targetsMarkup->inlineKeyboard.push_back(targetsColumn);
}

void ProxyBot::setCommands() {

    vector<BotCommand::Ptr> commands;
    BotCommand::Ptr cmd(new BotCommand);
    cmd->command = "targets";
    cmd->description = "Show all your targets";

    commands.push_back(cmd);

    cmd = BotCommand::Ptr(new BotCommand);
    cmd->command = "start";
    cmd->description = "Start listening";

    commands.push_back(cmd);

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
            for (const auto& target : caller->second->targets) {
                performTargetsColumn(target.first);
            }
            bot.getApi().sendMessage(message->chat->id, "Your targets is:", NULL, NULL, targetsMarkup, "MarkdownV2");
        }
        else {
            bot.getApi().sendMessage(message->chat->id, "You are have no permission to this command!");
        }
        });

    bot.getEvents().onCallbackQuery([&](CallbackQuery::Ptr query) {
        auto &chosenTargetId = query->data;
        auto senderId = query->message->chat->id;
        std::string response = "Current target set to: " + chosenTargetId;
        bot.getApi().sendMessage(senderId, response);
        users.at(senderId)->currentTarget = users.at(senderId)->targets.find(chosenTargetId)->second;
        });
}

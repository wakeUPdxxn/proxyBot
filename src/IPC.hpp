#include <boost/interprocess/ipc/message_queue.hpp>
#include <thread>

class ProxyBot;

class Command {
	virtual void execute() = 0;
};

class notifyCommand final : Command {
public:
	notifyCommand(std::weak_ptr<ProxyBot> &&receiver) :__receiver(std::move(receiver)) {};
	void execute();
private:
	std::weak_ptr<ProxyBot>__receiver;
};

class IPCdispatcher { //dispacth ipc proccess and invokes a notify command at new data comes
public:
	IPCdispatcher(std::weak_ptr<ProxyBot> &&parent);
	~IPCdispatcher();
private:
	void wait(std::stop_token stoken);
private:
	std::unique_ptr<std::jthread> __worker;
	std::unique_ptr<notifyCommand>cmd;
};
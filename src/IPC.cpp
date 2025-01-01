#include "ProxyBot.hpp"
#include "IPC.hpp"

namespace bipc = boost::interprocess;

void notifyCommand::execute()
{
	if (std::shared_ptr<ProxyBot> p = __receiver.lock()) {
		p->onNewData();
	}
}

IPCdispatcher::IPCdispatcher(std::weak_ptr<ProxyBot> &&parent)
{
    cmd = std::make_unique<notifyCommand>(std::move(parent));

    __worker = std::make_unique<std::jthread>(std::bind(&IPCdispatcher::wait, this, std::placeholders::_1));
    __worker->detach();
}

IPCdispatcher::~IPCdispatcher()
{
    if (__worker->joinable()) __worker->join();
    __worker->request_stop();
}

void IPCdispatcher::wait(std::stop_token stoken)
{
    std::unique_ptr<bipc::message_queue> __message_q = 
        std::make_unique<bipc::message_queue>(bipc::open_or_create, "dataReady_q", 10, sizeof(int)); 

    int id{ 0 };
    [[maybe_unused]] boost::ulong_long_type size{ 0 };
    [[maybe_unused]] unsigned int priority{ 0 };
    try {
        while (!stoken.stop_requested()) {
            __message_q->receive(&id, sizeof(int), size, priority);    //sync blocking
            cmd->execute();
        }
    }
    catch (bipc::interprocess_exception& e) {
        std::cout << e.what();
    }
    bipc::message_queue::remove("dataReady_q");
}

# proxyBot
Bot for receiving data from a third-party process and forwarding it to a specific user <br /> <br />
Requires:
- Threads
- CURL(optional)
- OpenSSL
- Boost system
- Boost interprocess <br />
### If comeone interested in, follow the steps below <br /> 
## Env. and deps.
First of all you neeed to obtain your bot token and create an environment var. named as proxyBotToken  <br />
#### Then in the root directory run:
git submodule init <br />
git submodule update <br />
#### Install requirements by: <br />
apt-get install -y libpthread-stubs0-dev libcurl-dev libssl-dev libboost-system-dev libboost-exception-dev
## To build with cmake:
- mkdir build && cd build
- cmake ..
- cmake --build .
## Or just:
- ./build.sh <br />
Executable file will be located in "rootFolder"/bin
# ToDo
- [x] interprocess communication for recieve data
- target data output to user

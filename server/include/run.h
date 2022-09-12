#include "baseApp.cpp"
#include "cliBaseApp.cpp"

namespace Messanger
{
    SOCKET initSocket();

    void clientHendler(SOCKET ClientSocket);

    void run();
}
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

int main()
{
    mongocxx::uri uri("mongodb://<hostname>:<port>/?directConnection=true");
    mongocxx::client client(uri);
}
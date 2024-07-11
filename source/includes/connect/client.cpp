#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

int main()
{
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);
}
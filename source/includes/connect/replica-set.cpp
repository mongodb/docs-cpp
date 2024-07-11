#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

int main()
{
    mongocxx::uri uri("mongodb://host1:27017/?replicaSet=sampleRS");
    mongocxx::client client(uri);
}
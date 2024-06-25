// start-instance
#include <mongocxx/instance.hpp>

mongocxx::instance instance{};
// end-instance

// start-client
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

mongocxx::instance instance{};
mongocxx::uri uri("mongodb://localhost:27017");
mongocxx::client client(uri);
// end-client
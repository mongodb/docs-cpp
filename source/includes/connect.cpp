// start-instance
#include <mongocxx/instance.hpp>

mongocxx::instance instance{};
// end-instance

// start-client
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

mongocxx::uri uri("mongodb://localhost:27017");
mongocxx::client client(uri);
// end-client

// start-stable-api
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

mongocxx::uri uri("mongodb://<username>:<password>@<hostname>:<port>");
mongocxx::options::client client_options;
mongocxx::options::server_api server_api_options(k_version_1);
server_api_options.strict(true);
server_api_options.deprecation_errors(true);
client_options.server_api_opts(server_api_options);
mongocxx::client client(uri, client_options);
// end-stable-api
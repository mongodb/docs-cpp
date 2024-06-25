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

// start-atlas
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/exception/exception.hpp>

// Replace the placeholder with your Atlas connection string
mongocxx::uri uri("<connection string>");

// Create a mongocxx::client with a mongocxx::options::client object to set the Stable API version
mongocxx::options::client client_options;
mongocxx::options::server_api server_api_options(k_version_1);
server_api_options.strict(true);
server_api_options.deprecation_errors(true);

client_options.server_api_opts(server_api_options);
mongocxx::client client(uri, client_options);

try
{
    // Ping the server to verify that the connection works
    auto admin = client["admin"];
    bsoncxx::document::value command = bsoncxx::from_json(R"({"ping": 1})");
    auto result = admin.run_command(command.view());
    std::cout << bsoncxx::to_json(result) << "\n";
    std::cout << "Pinged your deployment. You successfully connected to MongoDB!\n";
}
catch (const mongocxx::exception &e)
{
    std::cerr << "An exception occurred: " << e.what() << '\n';
    return EXIT_FAILURE;
}
// end-atlas

// start-replica-set
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

mongocxx::uri uri("mongodb://host1:27017/?replicaSet=sampleRS");
mongocxx::client client(uri);
// end-replica-set

// start-direct-connection
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

mongocxx::uri uri("mongodb://<hostname>:<port>/?directConnection=true");
mongocxx::client client(uri);
// end-direct-connection
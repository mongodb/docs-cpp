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

// start-connection-string-options
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true&tlsCertificateKeyFile=path/to/file.pem");
mongocxx::client client(uri);
// end-connection-string-options
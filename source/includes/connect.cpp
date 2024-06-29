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

// start-client-options
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/tls.hpp>

mongocxx::options::client client_options;
mongocxx::options::tls tls_options;
tls_options.pem_file("path/to/file.pem");
client_options.tls_opts(tls_options);

mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true");
mongocxx::client client(uri);
mongocxx::client client(uri, client_options);
// end-client-options
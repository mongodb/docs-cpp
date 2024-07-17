// start-connection-uri
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true&tlsCertificateKeyFile=path/to/file.pem");
mongocxx::client client(uri);
// end-connection-uri

// start-client-options
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

mongocxx::options::client client_options;
mongocxx::options::tls tls_options;

tls_options.pem_file("/path/to/file.pem");
client_options.tls_opts(tls_options);

mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true");
mongocxx::client client(uri, client_options);
// end-client-options

// start-uri-object
mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true");
mongocxx::client client(uri);
auto is_tls_enabled = uri.tls();
// end-uri-object
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true&tlsCertificateKeyFile=path/to/file.pem");
mongocxx::client client(uri);
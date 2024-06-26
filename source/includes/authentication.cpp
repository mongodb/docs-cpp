// start-scram-sha-256
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

auto uri = mongocxx::uri("mongodb://<username>:<password>@<hostname>:<port>/?"
                         "authSource=admin&authMechanism=SCRAM-SHA-256");
mongocxx::client client(uri);
// end-scram-sha-256

// start-scram-sha-1
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

auto uri = mongocxx::uri("mongodb://<username>:<password>@<hostname>:<port>/?"
                         "authSource=admin&authMechanism=SCRAM-SHA-1");
mongocxx::client client(uri);
// end-scram-sha-1

// start-x509
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

auto uri = mongocxx::uri("mongodb://<hostname>:<port>/?"
                         "tls=true&tlsCertificateKeyFile=path/to/client.pem&authMechanism=MONGODB-X509");
mongocxx::client client(uri);
// end-x509

// start-aws-connection-uri
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

auto uri = mongocxx::uri("mongodb://<AWS IAM access key ID>:<AWS IAM secret access key>@<hostname>:<port>/?"
                         "&authMechanism=MONGODB-AWS");
mongocxx::client client(uri);
// end-aws-connection-uri

// start-aws-connection-uri-session
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

auto uri = mongocxx::uri("mongodb://<AWS IAM access key ID>:<AWS IAM secret access key>@<hostname>:<port>/?"
                         "&authMechanism=MONGODB-AWSS&authMechanismProperties=AWS_SESSION_TOKEN:<token>");
mongocxx::client client(uri);
// end-aws-connection-uri-session

// start-aws-environment
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

auto uri = mongocxx::uri("mongodb://<hostname>:<port>/?"
                         "authMechanism=MONGODB-AWS");
mongocxx::client client(uri);
// end-aws-environment

// start-kerberos
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

auto uri = mongocxx::uri("mongodb://<username>%40EXAMPLE.COM@<hostname>:<port>/?"
                         "&authMechanism=GSSAPI"
                         "&authMechanismProperties=SERVICE_NAME:<authentication service name>");
mongocxx::client client(uri);
// end-kerberos

// start-plain
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

auto uri = mongocxx::uri("mongodb://<username>:<password>@<hostname>:<port>/?"
                         "&authMechanism=PLAIN&tls=true");
mongocxx::client client(uri);
// end-plain
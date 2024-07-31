#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/exception/exception.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

int main()
{
    mongocxx::instance instance;

    {
        // Retrieves one document that matches a query filter
        // start-local
        mongocxx::uri uri("mongodb://localhost:27017/");
        mongocxx::client client(uri);
        // end-local
    }

    {
        // start-atlas
        mongocxx::uri uri("<Atlas connection string>");
        mongocxx::client client(uri);
        // end-atlas
    }

    {
        // Retrieves one document that matches a query filter
        // start-replica-set
        mongocxx::uri uri("mongodb://<replica set member>:<port>/?replicaSet=<replica set name>");
        mongocxx::client client(uri);
        // end-replica-set
    }

    {
        // start-enable-tls
        mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true");
        mongocxx::client client(uri);
        // end-enable-tls
    }

    {
        // start-disable-ocsp
        mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true&tlsDisableOCSPEndpointCheck=true");
        mongocxx::client client(uri);
        // end-disable-ocsp
    }

    {
        // start-crl
        mongocxx::options::client client_options;
        mongocxx::options::tls tls_options;

        tls_options.crl_file("/path/to/file.pem");
        client_options.tls_opts(tls_options);

        mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true");
        mongocxx::client client(uri, client_options);
        // end-crl
    }

    {
        // start-insecure-tls
        mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true&tlsInsecure=true");
        mongocxx::client client(uri);
        // end-insecure-tls
    }

    {
        // start-disable-hostname
        mongocxx::uri uri("mongodb://<hostname>:<port>/?tls=true&tlsAllowInvalidHostnames=true");
        mongocxx::client client(uri);
        // end-disable-hostname
    }

    {
        // start-compression-all
        mongocxx::uri uri("mongodb://<hostname>:<port>/?compressors=snappy,zstd,zlib");
        mongocxx::client client(uri);
        // end-compression-all
    }

    {
        // start-compression-zlib
        mongocxx::uri uri("mongodb://<hostname>:<port>/?compressors=zlib&zlibCompressionLevel=1");
        mongocxx::client client(uri);
        // end-compression-zlib
    }

    {
        // Retrieves one document that matches a query filter
        // start-stable-api
        mongocxx::uri uri("<connection string>");
        
        mongocxx::options::client client_options;
        mongocxx::options::server_api server_api_options(mongocxx::options::server_api::version::k_version_1);
        client_options.server_api_opts(server_api_options);
        mongocxx::client client(uri, client_options);
        // end-stable-api
    }
}
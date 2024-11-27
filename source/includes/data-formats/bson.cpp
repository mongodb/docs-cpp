#include <iostream>
#include <chrono>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

int main() {
    mongocxx::instance instance;
    mongocxx::uri uri("<connection string>");
    mongocxx::client client(uri);

    {
        // Create a BSON document using the list builder
        // start-bson-list
        bsoncxx::builder::list list_builder = { "address", {  "street", "Pizza St", "zipcode", "10003" },
                                                "coord",   { -73.982419, 41.579505 }, 
                                                "cuisine", "Pizza",
                                                "name", "Mongo's Pizza" 
                                            }; 

        auto document = list_builder.view().get_document();  

        std::cout << bsoncxx::to_json(document) << std::endl;
        // end-bson-list 
    }

    {
        // Create a BSON document using the make_document() method
        // start-bson-one-off
        using bsoncxx::builder::basic::kvp;
        using bsoncxx::builder::basic::make_document; 

        auto document = make_document(kvp("hello","world"));

        std::cout << bsoncxx::to_json(document.view()) << std::endl;
        // end-bson-one-off
    }


    {
        // Create a BSON document using the append() method
        // start-bson-append
        using bsoncxx::builder::basic::kvp;

        auto document = bsoncxx::builder::basic::document{};
        document.append(kvp("hello", "world"));

        std::cout << bsoncxx::to_json(document.view()) << std::endl;
        // end-bson-append
    }
}
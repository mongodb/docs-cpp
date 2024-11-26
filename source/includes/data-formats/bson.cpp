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

    // 
    {
      "address" : {
         "street" : "Pizza St",
         "zipcode" : "10003"
      },
      "coord" : [-73.982419, 41.579505],
      "cuisine" : "Pizza",
      "name" : "Mongo's Pizza"
    }

    {
        // Create a BSON document using the list builder
        // start-bson-list
        bsoncxx::builder::list list_builder = { "address", {  "street", "Pizza St",
                                                                "zipcode", "10003"
                                                            },
                                                "coord",   { -73.982419, 41.579505 }, 
                                                "cuisine", "Pizza",
                                                "name", "Mongo's Pizza" 
                                                }; 

        bsoncxx::document::view document = list_builder.view().get_document();  
        // end-bson-list 
    }
}
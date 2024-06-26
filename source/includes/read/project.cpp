#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

int main() {
    mongocxx::instance instance{};
    mongocxx::uri uri("<connection string>");
    mongocxx::client client(uri);

    // start-db-coll
    auto db = client["sample_restaurants"];
    auto collection = db["restaurants"];
    // end-db-coll

    // start-project-include
    auto result = collection.find_one(make_document(kvp("name", "LinkedIn")));
    std::cout << bsoncxx::to_json(*result) << std::endl;
    // end-project-include

    // start-project-include-without-id
    auto cursor = collection.find(make_document(kvp("founded_year", 1970)));
    // end-project-include-without-id

    // start-project-exclude
    auto cursor = collection.find(make_document(kvp("founded_year", 1970)));
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-project-exclude
 
   // start-modify
    mongocxx::options::find opts;
    opts.limit(5);
    auto cursor = collection.find(make_document(kvp("number_of_employees", 1000)), opts);
   // end-modify

}

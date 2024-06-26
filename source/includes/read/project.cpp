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
    mongocxx::options::find opts{};
    opts.projection(make_document(kvp("name", 1), kvp("cuisine", 1), kvp("borough", 1)));

    auto cursor = collection.find(make_document(kvp("name", "Emerald Pub")), opts);
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-project-include

    // start-project-include-without-id
    mongocxx::options::find opts{};
    opts.projection(make_document(kvp("_id", 0), kvp("name", 1), kvp("cuisine", 1), kvp("borough", 1)));

    auto cursor = collection.find(make_document(kvp("name", "Emerald Pub")), opts);
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-project-include-without-id

    // start-project-exclude
    mongocxx::options::find opts{};
    opts.projection(make_document(kvp("grades", 0), kvp("address", 0)));

    auto cursor = collection.find(make_document(kvp("name", "Emerald Pub")), opts);
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-project-exclude

}

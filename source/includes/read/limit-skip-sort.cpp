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

    // start-limit-method
    mongocxx::options::find opts{};
    opts.limit(5);

    auto cursor = collection.find(make_document(kvp("cuisine", "Italian")), opts);
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-limit-method

    // start-sort-method
    mongocxx::options::find opts{};
    opts.sort(make_document(kvp("name", 1)));

    auto cursor = collection.find(make_document(kvp("cuisine", "Italian")), opts);
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-sort-method

    // start-skip-method
    mongocxx::options::find opts{};
    opts.skip(10);

    auto cursor = collection.find(make_document(kvp("borough", "Manhattan")), opts);
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-skip-method

    // start-limit-sort-skip
    mongocxx::options::find opts{};
    opts.sort(make_document(kvp("name", 1))).limit(5).skip(10);

    auto cursor = collection.find(make_document(kvp("cuisine", "Italian")), opts);
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-limit-sort-skip

}

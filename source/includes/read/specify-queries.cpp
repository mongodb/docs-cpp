#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::make_array;

int main() {
    mongocxx::instance instance{};
    // start-setup
    mongocxx::uri uri("<connection string>");
    mongocxx::client client(uri);
    auto db = client["db"];
    auto collection = db["fruits"];

    std::vector<bsoncxx::document::value> fruits;
    fruits.push_back(make_document(kvp("_id", 1), kvp("name", "apples"), kvp("qty", 5), kvp("rating", 3), kvp("color", "red"), kvp("type", make_array("fuji", "honeycrisp"))));
    fruits.push_back(make_document(kvp("_id", 2), kvp("name", "bananas"), kvp("qty", 7), kvp("rating", 4), kvp("color", "yellow"), kvp("type", make_array("cavendish"))));
    fruits.push_back(make_document(kvp("_id", 3), kvp("name", "oranges"), kvp("qty", 6), kvp("rating", 2), kvp("type", make_array("naval", "mandarin"))));
    fruits.push_back(make_document(kvp("_id", 4), kvp("name", "pineapples"), kvp("qty", 3), kvp("rating", 5), kvp("color", "yellow")));

    auto result = collection.insert_many(fruits);
    // end-setup

    // start-find-exact
    auto cursor = collection.find(make_document(kvp("color", "yellow")));
    // end-find-exact

    // start-find-all
    auto cursor = collection.find({});
    // end-find-all

    // start-find-comparison
    auto cursor = collection.find(make_document(kvp("rating", make_document(kvp("$gt", 2)))));
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-find-comparison
 
   // start-find-logical
    auto cursor = collection.find(
        make_document(kvp("$or",
                            make_array(make_document(kvp("qty", make_document(kvp("$gt", 5)))),
                                        make_document(kvp("color", "yellow"))))));
    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
   // end-find-logical

    // start-find-array
    auto cursor = collection.find(make_document(kvp("type", make_document(kvp("$size", 2)))));
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-find-array

    // start-find-element
    auto cursor = collection.find(make_document(kvp("color", make_document(kvp("$exists", "true")))));
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-find-element

    // start-find-evaluation
    auto cursor = collection.find(make_document(kvp("name", make_document(kvp("$regex", "p{2,}")))));
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-find-evaluation
}
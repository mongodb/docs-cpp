#include <iostream>

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

    {
        // Retrieves distinct values of the "borough" field
        // start-distinct
        auto cursor = collection.distinct("borough", {});
        for(auto&& doc : cursor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }
        // end-distinct
    }

    {
        // Retrieves distinct "borough" field values for documents with a "cuisine" value of "Italian"
        // start-distinct-with-query
        auto cursor = collection.distinct("borough", make_document(kvp("cuisine", "Italian")));
        for(auto&& doc : cursor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }
        // end-distinct-with-query
    }

    {
        // Retrieves documents matching the "name" field query and excludes their "grades" and "address" values when printing
        // start-distinct-with-comment
        mongocxx::options::distinct opts{};
        opts.comment(bsoncxx::types::bson_value::view_or_value{"Bronx pizza restaurants"});

        auto cursor = collection.distinct("name",
            make_document(kvp("$and",
                                make_array(make_document(kvp("borough", "Bronx")),
                                            make_document(kvp("cuisine", "Pizza"))))),
            opts
        );
        for (auto&& doc : cursor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }
        // end-distinct-with-comment
    }
}
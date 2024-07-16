#include <iostream>

#include <bsoncxx/builder/list.hpp>
#include <bsoncxx/builder/stream/document.hpp>
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

    {
        // Creates a time series collection to store precipitation data
        // start-create-ts
        auto db = client["precipitation"];
        
        auto ts_info = make_document(
            kvp("timeseries", make_document(
                kvp("timeField", "precipitation_mm"),
                kvp("metaField", "location"),
                kvp("granularity", "minutes")
        )));

        auto collection = db.create_collection("sept2023", ts_info.view());
        // end-create-ts
    }

    {
        // Lists the collections in the "precipitation" database
        auto db = client["precipitation"];
        // start-list-colls
        auto cursor = db.list_collections();

        for(auto&& doc : cursor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }
        // end-list-colls
    }

}
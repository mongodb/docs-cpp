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
    auto db = client["sample_training"];
    auto collection = db["companies"];
    // end-db-coll
 
    {
        // Counts documents that have a "founded_year" value of 2010
        // start-count-specific
        auto result = collection.count_documents(make_document(kvp("founded_year", 2010)));
        std::cout << "Number of documents: " << result << std::endl;
        // end-count-specific
    }

    {
        // Counts a maximum of 100 documents that have a "number_of_employees" value of 50
        // start-modify-count
        mongocxx::options::count opts;
        opts.limit(100); 
        auto result = collection.count_documents(make_document(kvp("number_of_employees", 50)));
        std::cout << "Number of documents: " << result << std::endl;
        // end-modify-count
    }

    {
        // Estimates the number of documents in the collection
        // start-count-estimate
        auto result = collection.estimated_document_count();
        std::cout << "Estimated number of documents: " << result << std::endl;
        // end-count-estimate
    }
}
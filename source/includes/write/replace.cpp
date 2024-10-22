#include <iostream>

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

    // start-db-coll
    auto db = client["sample_restaurants"];
    auto collection = db["restaurants"];
    // end-db-coll

    {
        // replaces the fields and values of a document with the name "Bagels N Buns" with a document 
        // with the same _id value and no fields other than the name "2 Bagels 2 Buns"
        // start-replace-one
        // Create inputs 
        auto query_filter = make_document(kvp("name", "Nobu"));
        auto replace_doc = make_document(kvp("name", "La Bernadin"));

        // Call replace_one()
        auto result = collection.replace_one(query_filter.view(), replace_doc.view());

        // Print new document 
        auto new_doc = collection.find_one(make_document(kvp("name", "La Bernadin")));
        std::cout << "New document: " << bsoncxx::to_json(*new_doc) << std::endl;
        // end-replace-one
    }

    {
        // start-replace-options-hint
        auto index_specification = make_document(kvp("name", 1));
        collection.create_index(index_specification.view());

        mongocxx::options::replace opts{}; 
        opts.hint(mongocxx::hint{"name_1"});

        auto query_filter = make_document(kvp("name", "Nobu"));
        auto replace_doc = make_document(kvp("name", "La Bernadin"));

        auto result = collection.replace_one(query_filter.view(), replace_doc.view(), opts);
        // end-replace-options-hint 
    }
    
    {
        // start-replace-options-upsert
        mongocxx::options::replace opts{}; 
        opts.upsert(true);

        auto query_filter = make_document(kvp("name", "In-N-Out Burger"));
        auto replace_doc = make_document(kvp("name", "Shake Shack"));

        std::cout << "Number of documents before replace: " << collection.count_documents({}) << std::endl;
        auto result = collection.replace_one(query_filter.view(), replace_doc.view(), opts);
        std::cout << "Number of documents after replace: " << collection.count_documents({}) << std::endl;
        // end-replace-options-upsert
    }

    {
        // Replaces the matching document and prints the number of matched documents
        // start-replace-result-matched
        auto query_filter = make_document(kvp("name", "Shake Shack"));
        auto replace_doc = make_document(kvp("name", "In-N-Out Burger"));

        auto result = collection.replace_one(query_filter.view(), replace_doc.view());
        std::cout << "Matched documents: " << result->matched_count() << std::endl;        
        // end-replace-result-matched
    }

    {

        // Replaces the matching document and prints the number of modified documents
        // start-replace-result-upsert
        mongocxx::options::replace opts{}; 
        opts.upsert(true);

        auto query_filter = make_document(kvp("name", "In-N-Out Burger"));
        auto replace_doc = make_document(kvp("name", "Shake Shack"));

        auto result = collection.replace_one(query_filter.view(), replace_doc.view(), opts);
        auto id = result->upserted_id()->get_value();
                
        std::cout << "Upserted ID: " << id.get_oid().value.to_string() << std::endl;
        // end-replace-result-upsert
    }
}
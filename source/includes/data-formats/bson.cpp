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
    {
        // Create a BSON document using the stream builder
        // start-bson-stream

        // Create and fill a builder::stream::document
        using bsoncxx::builder::stream::document;
        auto stream_doc = document{}; 
        stream_doc << "hello" << "world";

        std::cout << "stream_doc: " << bsoncxx::to_json(stream_doc.view()) << std::endl;

        // Convert a stream to its underlying BSON value using the finalize helper
        using bsoncxx::builder::stream::finalize;
        auto finalize_doc = document{} << "finalize" << "me" << finalize;

        std::cout << "finalize_doc: " << bsoncxx::to_json(finalize_doc.view()) << std::endl;

        // Add all keys and corresponding values from one document into another using the concatenate helper
        using bsoncxx::builder::stream::concatenate;
        stream_doc << concatenate(finalize_doc.view()); 

        std::cout << "Concatenated doc: " << bsoncxx::to_json(stream_doc.view()) << std::endl;

        // Build a subdocument using open_document and close_document
        using bsoncxx::builder::stream::open_document;
        using bsoncxx::builder::stream::close_document; 
        
        auto topLevelDoc1 = document{}; 
        topLevelDoc1 << "hello" << "world" << "subDoc" << open_document << "subdoc_key" << "subdoc_value" << close_document; 

        std::cout << "topLevelDoc1: " << bsoncxx::to_json(topLevelDoc1.view()) << std::endl;

        // Nest an existing BSON document in 3 ways: 
        // 1. Create a bsoncxx::types:b_document with the document view and append it 
        // 2. Open a new document and concatenate the document view in
        // 3. Stream in the document view 
        using bsoncxx::types::b_document;
        auto nestedValue = document{} << "nest" << "me" << finalize; 

        auto topLevelDoc2 = document{} << "subDoc1" << b_document{nestedValue.view()} 
                                       << "subDoc2" << open_document << concatenate(nestedValue.view()) << close_document 
                                       << "subDoc3" << nestedValue.view()
                                       << finalize; 

        std::cout << "topLevelDoc2: " << bsoncxx::to_json(topLevelDoc2.view()) << std::endl;
        // end-bson-stream

        // start-bson-print
        bsoncxx::document::value = document{} << "I am" << "a BSON document" << finalize;
        std::cout << bsoncxx::to_json(doc.view()) << std::endl;
        // end-bson-print
    }
}
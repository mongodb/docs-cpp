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
        // start-bson-values
        bsoncxx::document::value basic_doc{basic_builder.extract()};
        bsoncxx::document::value stream_doc{stream_builder.extract()};
        // end-bson-values

        // start-bson-views
        bsoncxx::document::view document_view{document_value.view()};
        bsoncxx::document::view basic_view{basic_builder.view()};
        bsoncxx::document::view stream_view{stream_builder.view()};
        // end-bson-views
    }
    {
        // Create a dangling view
        // start-bson-dangling-view
        bsoncxx::document::view make_a_dangling_view() {
            bsoncxx::builder::basic::document builder{};
            builder.append(kvp("hello", "world"));

            // Creates a document::value on the stack that will disappear when we return.
            bsoncxx::document::value stack_value{builder.extract()};

            // Returns a dangling view of the local value
            return stack_value.view(); // Bad!!
        }
        // end-bson-dangling-view
    }
    {
        // Create a dangling view off of a builder
        // start-bson-dangling-builder
        bsoncxx::builder::stream::document temp_builder{};
        temp_builder << "oh" << "no";
        bsoncxx::document::view dangling_view = temp_builder.extract().view(); // Bad!!
        // end-bson-dangling-builder
    }
    {
        // Create a BSON document using the list builder
        // start-bson-list
        bsoncxx::builder::list list_builder = { "hello", "world" }

        bsoncxx::builder::view document = list_builder.view().get_document();  

        std::cout << bsoncxx::to_json(document) << std::endl;
        // end-bson-list 
    }

    {
        // Create a BSON document using the make_document() method
        // start-bson-make-document
        using bsoncxx::builder::basic::kvp;
        using bsoncxx::builder::basic::make_document; 

        bsoncxx::document::value document = make_document(kvp("hello","world"));

        std::cout << bsoncxx::to_json(document.view()) << std::endl;
        // end-bson-make-document
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
        using bsoncxx::builder::stream::document{};
        auto stream_builder = document{} << "hello" << "world"; 

        auto doc_value = stream_builder.extract();
        auto doc_view = stream_builder.view();

        std::cout << bsoncxx::to_json(doc_view) << std::endl;
        // end-bson-stream 
    }
    {
        // Create and fill a builder::stream::document
        // start-bson-stream-finalize 
        using bsoncxx::builder::stream::document;
        using bsoncxx::builder::stream::finalize;

        bsoncxx::document::value document = document{} << "hello" << "world" << finalize;

        std::cout << bsoncxx::to_json(document.view()) << std::endl;
        // end-bson-stream-finalize
    }
    {
        // Add all keys and corresponding values from one document into another using the concatenate helper
        // start-bson-concat-nest

        // Concatenate two documents using concatenate
        using bsoncxx::builder::stream::document;
        using bsoncxx::builder::stream::finalize;
        using bsoncxx::builder::stream::concatenate;

        auto document1 = document{} << "hello" << "again" << finalize; 

        auto document2 = document{} << "goodbye" << "world" << concatenate(document1.view()) << finalize; 

        std::cout << bsoncxx::to_json(document2.view()) << std::endl;


        // Build a subdocument using open_document and close_document
        using bsoncxx::builder::stream::open_document;
        using bsoncxx::builder::stream::close_document;

        auto topLevelDoc = document{} << "hello" << "world" << "subDoc" 
                                      << open_document << "subdoc_key" << "subdoc_value" << close_document
                                      << finalize; 

        std::cout << bsoncxx::to_json(topLevelDoc.view()) << std::endl;
        // end-bson-concat-nest

        
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
#include <iostream>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

int main() {

    {
        // start-with-transaction
        
        // Establish a connection to the MongoDB deployment 
        mongocxx::instance instance{};
        mongocxx::client client(mongocxx::uri{"<connectionString>"});

        // Define database and collection variables
        auto db = client["sample_mflix"];
        auto movies_collection = db["movies"];
        auto comments_collection = db["comments"]; 

        // Start a client session
        auto session = client.start_session();

        // Define a callback specifying the sequence of operations to perform during the transaction
        mongocxx::client_session::with_transaction_cb callback = [&](mongocxx::client_session* session) {
            // Important::  You must pass the session to the operations.
            movies_collection.insert_one(*session, make_document(kvp("title", "Parasite")));
            comments_collection.insert_one(*session, make_document(kvp("name", "Rhaenyra Targaryen"), kvp("text", "Dracarys.")));
        };


        try {
            // Define an options instance to set the majority write concern for the transaction operations explicitly 
            mongocxx::options::transaction opts;
            mongocxx::write_concern wc{};
            wc.acknowledge_level(mongocxx::write_concern::level::k_majority);
            opts.write_concern(wc);

            // Start a transaction, execute the operations in the callback function, and commit the results 
            session.with_transaction(callback, opts);
        } catch (const mongocxx::exception& e) {
            std::cout << "An exception occurred: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
        // end-with-transaction
    }
    {
        // start-start-transaction
       // Create a mongocxx::instance to initialize the drive and initialize a mongocxx::client
        // using your MongoDB deployment connection string to establish a connection to the MongoDB server
        mongocxx::instance instance{};
        mongocxx::client client(mongocxx::uri{"<connectionString>"});

        // Define database and collection variables
        auto db = client["sample_mflix"];
        auto movies_collection = db["movies"];
        auto comments_collection = db["comments"];

       // Start a client session
        auto session = client.start_session();

        try {
            // Define an options instance to set the write concern for the transaction operations
            mongocxx::options::transaction opts;
            mongocxx::write_concern wc{};
            wc.acknowledge_level(mongocxx::write_concern::level::k_majority);
            opts.write_concern(wc);

            // Start a transaction
            session.start_transaction();

            // Specify the series of database operations to perform during the transaction
            movies_collection.insert_one(session, make_document(kvp("title", "Parasite")));
            comments_collection.insert_one(session, make_document(kvp("name", "Rhaenyra Targaryen"), kvp("text", "Dracarys II")));

            // Commit the transaction 
            session.commit_transaction();
        } catch (const mongocxx::exception& e){ 
            std::cout << "An exception occurred: " << e.what() << std::endl;
            return EXIT_FAILURE;   
        }

        return EXIT_SUCCESS;
        // end-start-transaction
    }
}


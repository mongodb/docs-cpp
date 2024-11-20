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
        // start-callback-api
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

        // Define an options instance to set the majority write concern for the transaction operations explicitly 
        mongocxx::options::transaction opts;
        mongocxx::write_concern wc;
        wc.acknowledge_level(mongocxx::write_concern::level::k_majority);
        opts.write_concern(wc);

        try {
            // Start a transaction, execute the operations in the callback function, and commit the results 
            session.with_transaction(callback, opts);
        } catch (const mongocxx::exception& e) {
            std::cout << "An exception occurred: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
        // end-callback-api
    }
    {
        // start-core-api
        // Establish a connection to the MongoDB deployment 
        mongocxx::instance instance{};
        mongocxx::client client(mongocxx::uri{"<connectionString>"});

        // Define a function to handle TransientTransactionError retry logic
        using transaction_func = std::function<void(mongocxx::client_session& session)>;
        auto run_transaction_with_retry = [](transaction_func txn_func, mongocxx::client_session& session) {
            while (true) {
                try {
                    txn_func(session);  // performs transaction.
                    break;
                } catch (const mongocxx::operation_exception& oe) {
                    std::cout << "Transaction aborted. Caught exception during transaction." << std::endl;
                    // If transient error, retry the whole transaction.
                    if (oe.has_error_label("TransientTransactionError")) {
                        std::cout << "TransientTransactionError, retrying transaction ..." << std::endl;
                        continue;
                    } else {
                        throw oe;
                    }
                }
            }
        };

        // Define a function to handle UnknownTransactionCommitResult retry logic
        auto commit_with_retry = [](mongocxx::client_session& session) {
            while (true) {
                try {
                    session.commit_transaction();  // Uses write concern set at transaction start.
                    std::cout << "Transaction committed." << std::endl;
                    break;
                } catch (const mongocxx::operation_exception& oe) {
                    // Can retry commit
                    if (oe.has_error_label("UnknownTransactionCommitResult")) {
                        std::cout << "UnknownTransactionCommitResult, retrying commit operation ..." << std::endl;
                        continue;
                    } else {
                        std::cout << "Error during commit ..." << std::endl;
                        throw oe;
                    }
                }
            }
        };

        auto transaction_operations = [&](mongocxx::client_session& session) {
            auto& client = session.client(); 

            // Define database and collection variables
            auto db = client["sample_mflix"];
            auto movies_collection = db["movies"];
            auto comments_collection = db["comments"];

            // Define an options instance to set the majority write concern for the transaction operations explicitly 
            mongocxx::options::transaction opts;
            mongocxx::write_concern wc;
            wc.acknowledge_level(mongocxx::write_concern::level::k_majority);
            opts.write_concern(wc);

            session.start_transaction(opts);

            try {
                // Specify database operations to run during transaction
                movies_collection.insert_one(session, make_document(kvp("title", "Parasite")));
                comments_collection.insert_one(session, make_document(kvp("name", "Rhaenyra Targaryen"), kvp("text", "Dracarys")));
            } catch (const mongocxx::operation_exception& oe) {
                std::cout << "Caught exception during transaction, aborting." << std::endl;
                session.abort_transaction();
                throw oe;
            }

            commit_with_retry(session);
        };

        auto session = client.start_session();
        
        try {
            run_transaction_with_retry(update_employee_info, session);
        } catch (const mongocxx::operation_exception& oe) {
            // Do something with error.
            throw oe;
        }
        // end-core-api
    }



}


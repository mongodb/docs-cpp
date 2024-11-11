
// start-session
// Create a mongocxx::instance to initialize the drive and initialize a mongocxx::client
// using your MongoDB deployment connection string to establish a connection to the MongoDB server
mongocxx::instance instance{};
mongocxx::client client(mongocxx::uri uri("<connection string>"));

// Define the database and collection
// Connect to the movies collection in the preloaded Atlas sample_mflix database
auto db = client["sample_mflix"];
auto collection = db["movies"];

// Prepare to set majority write explicitly. Note: on Atlas deployments this won't always be
// needed. The suggested Atlas connection string includes majority write concern by default.
write_concern wc_majority{};
wc_majority.acknowledge_level(write_concern::level::k_majority);

// Start a client session
auto session = client.start_session();

// Define a callback function that specifies the sequence of operations to perform inside the transaction.
client_session::with_transaction_cb callback = [&](client_session* session) {
    // Important::  You must pass the session to the operations.
    foo.insert_one(*session, make_document(kvp("title", "Parasite")));
    bar.insert_one(*session, make_document(kvp("title", "The Banshees of Inisherin")));
};

// Call the with_transaction() method and pass in the callback function 
// and an options object that sets the write concern for the transaction operations
try {
    // Define an options object that sets the write concern for the transaction operations
    options::transaction opts;
    opts.write_concern(wc_majority);

    // Call with_transactions to run and commit the insert operations defined in the callback function  
    session.with_transaction(callback, opts);
} catch (const mongocxx::exception& e) {
    std::cout << "An exception occurred: " << e.what() << std::endl;
    return EXIT_FAILURE;
}

// Return the status of the transaction. This automatically calls the mongocxx::client_session destructor, 
// closing the connection to the server.  
return EXIT_SUCCESS;
// end-session

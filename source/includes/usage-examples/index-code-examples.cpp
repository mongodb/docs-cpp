// start-single-field
auto index_specification = make_document(kvp("<field name>", 1));
auto result = collection.create_index(index_specification.view());

std::cout << "Index created: " << bsoncxx::to_json(result) << std::endl;
// end-single-field

// start-compound-field
auto index_specification = make_document(kvp("<field name 1>", -1), kvp("<field name 2>", -1));
auto result = collection.create_index(index_specification.view());

std::cout << "Index created: " << bsoncxx::to_json(result) << std::endl;
// end-compound-field

// start-remove-index
collection.indexes().drop_one("<index name>");

std::cout << "Index dropped." << std::endl;
// end-remove-index

// start-remove-all-indexes
collection.indexes().drop_all();

std::cout << "All indexes removed." << std::endl;
// end-remove-all-indexes

// start-create-search-index
auto siv = collection.search_indexes();
auto name = "<searchIndexName>";
auto definition = make_document(kvp("mappings", make_document(kvp("dynamic", true))));
auto model = mongocxx::search_index_model(name, definition.view());

// Create the search index
auto result = siv.create_one(model);
std::cout << "New index name: " << result << std::endl;
// end-create-search-index
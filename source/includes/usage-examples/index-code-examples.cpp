// start-single-field
auto index_specification = make_document(kvp("<fieldName>", 1));
auto result = collection.create_index(index_specification.view());

std::cout << "Index created: " << bsoncxx::to_json(result) << std::endl;
// end-single-field

// start-compound-field
auto index_specification = make_document(kvp("<fieldName1>", -1), kvp("<fieldName2>", -1));
auto result = collection.create_index(index_specification.view());

std::cout << "Index created: " << bsoncxx::to_json(result) << std::endl;
// end-compound-field

// start-remove-index
collection.indexes().drop_one("<indexName>");

std::cout << "Index dropped." << std::endl;
// end-remove-index

// start-remove-all-indexes
collection.indexes().drop_all();

std::cout << "All indexes removed." << std::endl;
// end-remove-all-indexes

// start-create-search-index
// Create an index model with your index name and definition
auto siv = collection.search_indexes();
auto name = "<searchIndexName>";
auto definition = make_document(kvp("mappings", make_document(kvp("dynamic", true))));
auto model = mongocxx::search_index_model(name, definition.view());

// Create the search index
auto result = siv.create_one(model);
std::cout << "New index name: " << result << std::endl;
// end-create-search-index

// start-create-multiple-search-indexes
// Create a vector to store Search index models
auto siv = collection.search_indexes();
std::vector<mongocxx::search_index_model> models; 

// Add an index model with dynamic mappings to the input vector
auto name_1 = "myDynamicIndex";
auto definition_1 = make_document(kvp("mappings", make_document(kvp("dynamic", true))));
auto model_1 = mongocxx::search_index_model(name_1, definition_1.view()); 
models.push_back(model_1);

// Add an index model with static mappings to the input vector
auto name_2 = "myStaticIndex";
auto fields = make_document(kvp("title", make_document(kvp("type", "string"), kvp("analyzer","lucene.standard"))), kvp("year", make_document(kvp("type","number"))));
auto definition_2 = make_document(kvp("mappings", make_document(kvp("dynamic", false), kvp("fields", fields))));
auto model_2 = mongocxx::search_index_model(name_2, definition_2.view());
models.push_back(model_2); 

// Create the search indexes
auto result = siv.create_many(models);

// Print the search index names
std::cout << "New index names:" << std::endl;
for (const std::string& name : result) {
    std::cout << name << std::endl;
}
// end-create-multiple-search-indexes

// start-list-search-indexes
auto siv = collection.search_indexes();
auto result = siv.list(); 
for (const auto &idx : result) {
    std::cout << bsoncxx::to_json(idx) << std::endl;
}
// end-list-search-indexes

// start-update-search-index
auto siv = collection.search_indexes();
auto update_fields = make_document(kvp("<fieldName>", make_document(kvp("type", "<fieldType>"))));
auto update_definition = make_document(kvp("mappings", make_document(kvp("dynamic", false), kvp("fields", update_fields))));
siv.update_one(<searchIndexName>, update_definition.view());
// end-update-search-index

// start-remove-search-index
auto siv = collection.search_indexes();
siv.drop_one("<searchIndexName>");
// end-remove-search-index
// start-single-field
auto index_specification = make_document(kvp("<field name>", 1));
auto result = collection.create_index(index_specification.view());

std::cout << "Index created: " << bsoncxx::to_json(result) << std::endl;
// end-single-field

// start-remove-index
collection.indexes().drop_one("title_1");

std::cout << "Index 'title_1' dropped." << std::endl;
// end-remove-index

// start-remove-all-indexes
collection.indexes().drop_all();

std::cout << "All indexes removed." << std::endl;
// end-remove-all-indexes
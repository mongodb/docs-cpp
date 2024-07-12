// start-single-field
auto index_specification = make_document(kvp("<field name>", 1));
std::string result = collection.create_index(std::move(index_specification));

std::cout << "Index created: " << result << std::endl;
// end-single-field

// start-remove-index
collection.indexes().drop_one("title_1");

std::cout << "Index 'title_1' dropped." << std::endl;
// end-remove-index

// start-remove-all-indexes
collection.indexes().drop_all();

std::cout << "All indexes removed." << std::endl;
// end-remove-all-indexes
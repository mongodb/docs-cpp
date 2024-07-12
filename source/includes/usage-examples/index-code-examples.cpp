// start-single-field
auto index_specification = make_document(kvp("<field name>", 1));
std::string result = collection.create_index(std::move(index_specification));

std::cout << "Index created: " << result << std::endl;
// end-single-field
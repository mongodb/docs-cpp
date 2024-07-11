// start-index-single
auto index_specification = make_document(kvp("title", 1));
collection.create_index(std::move(index_specification));
// end-index-single

// start-remove-index
collection.drop_index("title_1");
// end-remove-index

// start-remove-all-indexes
collection.drop_indexes();
// end-remove-all-indexes

// start-remove-all-wildcard
collection.drop_index("*");
// end-remove-all-wildcard
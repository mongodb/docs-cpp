#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/oid.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/gridfs/bucket.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

std::string getEnvVar(const std::string &key) {
    const char* val = std::getenv(key.c_str());
    if (val == nullptr) {
        throw std::runtime_error("Set the " + key + " variable to your Atlas URI that connects to the sample dataset");
    }
    return std::string(val);
}

// Converts a BSON document to a JSON string
// start-to-json
std::string toJSON(const bsoncxx::document::view &document) {
    return bsoncxx::to_json(document);
}
// end-to-json

int main() {
    // Initialize the MongoDB driver
    mongocxx::instance instance{};

    // Get the MongoDB URI from environment variable
    auto uri = mongocxx::uri(getEnvVar("MONGODB_URI"));
    mongocxx::client client(uri);
    auto db = client["db"];  // Replace 'db' with your database name
    
    // Creates a GridFS bucket or references an existing one
    // start-create-bucket
    auto bucket = db.gridfs_bucket();
    // end-create-bucket

    // Creates or references a GridFS bucket with a custom name
    // start-create-custom-bucket
    mongocxx::options::gridfs opts;
    opts.bucket_name("myCustomBucket");

    auto custom_bucket = db.gridfs_bucket(opts);
    // end-create-custom-bucket

    // Uploads a file called "my_file" to the GridFS bucket and writes data to it
    // start-open-upload-stream
    mongocxx::options::gridfs::upload opts;
    opts.chunk_size_bytes(1048576);
    auto uploader = bucket.open_upload_stream("my_file", opts);

    // ASCII for "HelloWorld"
    std::uint8_t bytes[10] = {72, 101, 108, 108, 111, 87, 111, 114, 108, 100};

    for (auto i = 0; i < 5; ++i) {
        uploader.write(bytes, 10);
    }

    uploader.close();
    // end-open-upload-stream

    // Uploads data to a stream, then writes the stream to a GridFS file
    // start-upload-from-stream
    std::ifstream file("/path/to/input_file", std::ios::binary);
    bucket.upload_from_stream("new_file", file);
    // end-upload-from-stream

    // Prints information about each file in the bucket
    // start-retrieve-file-info
    auto cursor = bucket.find({});
    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    // end-retrieve-file-info

    // Downloads a file from the GridFS bucket by referencing its ObjectId value
    // start-open-download-stream
    auto oid = bsoncxx::oid("66e0a5487c880f844c0a32b1");
    auto downloader = bucket.open_download_stream(oid);

    std::vector<uint8_t> buffer(downloader.file_length());
    downloader.read(buffer.data(), buffer.size());
    // end-open-download-stream

    // Downloads an entire GridFS file to a download stream
    // start-download-to-stream
    std::ofstream output_file("/path/to/output_file", std::ios::binary);
    bucket.download_to_stream(bsoncxx::oid("66e0a5487c880f844c0a32b1"), output_file);
    // end-download-to-stream

    // Deletes a file from the GridFS bucket with the specified ObjectId
    // start-delete-files
    bucket.delete_file(bsoncxx::oid("66e0a5487c880f844c0a32b1"));
    // end-delete-files

    return 0;
}
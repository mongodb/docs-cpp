// start-auto-encrypt
auto mongocryptd_options = make_document(kvp("mongocryptdBypassSpawn", true));

options::auto_encryption auto_encrypt_opts{};
auto_encrypt_opts.extra_options({mongocryptd_options.view()});

options::client client_opts;
client_opts.auto_encryption_opts(std::move(auto_encrypt_opts));

// Create and use your client here
// end-auto-encrypt

// start-json-schema
auto data_key_id = client_encryption.create_data_key("local");
auto json_schema = document{} << "properties" << open_document << "encryptedFieldName" << open_document << "encrypt"
                                << open_document << "keyId" << open_array << data_key_id << close_array << "bsonType"
                                << "string"
                                << "algorithm"
                                << "AEAD_AES_256_CBC_HMAC_SHA_512-Deterministic" << close_document << close_document
                                << close_document << "bsonType"
                                << "object" << finalize;
// end-json-schema

// start-explicit-encrypt
// Configure your MongoDB client here

auto kms_providers = document{} << "local" << open_document << "key"
                                << local_master_key << close_document
                                << finalize;

options::client_encryption client_encryption_opts{};
client_encryption_opts.key_vault_namespace({"keyvault", "datakeys"});
client_encryption_opts.kms_providers(kms_providers.view());
client_encryption_opts.key_vault_client(&client);

class client_encryption client_encryption(std::move(client_encryption_opts));

// Explicitly encrypts a BSON value
auto to_encrypt = bsoncxx::types::bson_value::make_value("secret message");
auto encrypted_message = client_encryption.encrypt(to_encrypt, encrypt_opts);

// Explicitly decrypts a BSON value
auto decrypted_message = client_encryption.decrypt(encrypted_message);

// Inserts the encrypted value into the database
coll.insert_one(make_document(kvp("encryptedField", encrypted_message)));
// end-explicit-encrypt

// start-auto-decrypt
options::auto_encryption auto_encrypt_opts{};
auto_encrypt_opts.bypass_auto_encryption(true);

options::client client_opts{};
client_opts.auto_encryption_opts(std::move(auto_encrypt_opts));
class client client_encrypted {uri{}, std::move(client_opts)};
// end-auto-decrypt
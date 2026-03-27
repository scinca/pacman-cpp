//
// Created by simon on 26.03.26.
//

#include "Database.h"

#include <iostream>
#include <optional>
#include <ostream>
#include <string>

Database::Database(const std::string& db_path) {

    const int rc = sqlite3_open(db_path.c_str(), &db_);

    if (rc != SQLITE_OK) {
        const std::string error_message {std::format( "Failed to open DB: {}" ,sqlite3_errmsg(db_))};
        sqlite3_close(db_);
        throw std::runtime_error(error_message);
    }
    sqlite3_exec(db_, "PRAGMA journal_mode=WAL; PRAGMA foreign_keys=ON;", nullptr, nullptr, nullptr);
    std::cout << "SQLite version: " << sqlite3_libversion() << std::endl;
    std::cout << "DB opened successfully!" << std::endl;


}

Database::~Database() {
    if (db_ != nullptr) {
        sqlite3_close(db_);
    }
}

std::expected<std::string, MapError> Database::GetMap(int map_number) {
    return "test";// temporary
}

//
// Created by simon on 26.03.26.
//
#include <iostream>
#include <ostream>
#include <string>
#include "Map/Map.h"
#include "Database.h"




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

    if (const auto result = InitDB(); !result) {
        std::cerr << "Failed to initialize database\n";
    }
}

Database::~Database() {
    if (db_ != nullptr) {
        sqlite3_close(db_);
    }
}

std::expected<std::string, MapError> Database::GetMap(const int map_number) const {
    const Statement stmt("SELECT map_data FROM maps WHERE id = ?;", db_);

    sqlite3_bind_int(stmt.Get(), 1, map_number);

    int rc = sqlite3_step(stmt.Get());

    if (rc == SQLITE_ROW) {
        const auto data = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.Get(), 0) //first column 0
        );
        return std::string(data);
    }else if (rc == SQLITE_DONE) {
        return std::unexpected(MapError::NotFound); // No rows matched
    }
    return std::unexpected(MapError::DatabaseUnavailable);
}

std::vector<MapInfo> Database::GetAllMaps() const {
    std::vector<MapInfo> result;
    const Statement stmt("SELECT * FROM maps", db_);


    while (sqlite3_step(stmt.Get()) == SQLITE_ROW) {
        MapInfo map;
        map.id = sqlite3_column_int(stmt.Get(), 0);
        map.content = reinterpret_cast<const char*>(sqlite3_column_text(stmt.Get(), 1));
        map.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt.Get(), 2));
        map.author = reinterpret_cast<const char *>(sqlite3_column_text(stmt.Get(), 3));
        map.creation_date = reinterpret_cast<const char *>(sqlite3_column_text(stmt.Get(), 4));
        result.push_back(map);
    }

    return result;

}





std::expected<int, MapValidationError> Database::AddMap(std::string map, const std::string &map_name, const std::string &author) const {
    const Statement stmt("INSERT OR IGNORE INTO maps (map_data, map_name, map_author) VALUES (?, ?, ?);", db_);
    std::erase(map, '\n');
    std::erase(map, '\r');
    MapValidationError error;

    const auto result = Map::ValidateMap(map);
    if (result.has_value()) {
        return std::unexpected(result.value());

    }


    sqlite3_bind_text(stmt.Get(),1,map.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.Get(),2,map_name.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.Get(),3,author.c_str(),-1,SQLITE_TRANSIENT);

    if (sqlite3_step(stmt.Get()) != SQLITE_DONE) {
        return std::unexpected(MapValidationError::DatabaseError);
    }


    return sqlite3_last_insert_rowid(db_);
}




std::expected<void, MapError> Database::InitDB() const {
    const auto sql = R"sql(
    CREATE TABLE IF NOT EXISTS maps (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    map_data TEXT NOT NULL UNIQUE,
    map_name TEXT NOT NULL,
    map_author TEXT NOT NULL DEFAULT 'You',
    created_at TEXT DEFAULT (datetime('now'))
    ))sql";

    char* error = nullptr;
    if (sqlite3_exec(db_, sql, nullptr, nullptr, &error) != SQLITE_OK) {
        const std::string error_message = std::format("InitDB failed: {}", error);
        sqlite3_free(error);
        return std::unexpected(MapError::DatabaseUnavailable);
    }

    const auto result = AddMap(default_map_, "Default Map", "scinca");
    if (result.has_value() == false) { //cant use .error because i dont want to make logic for casting enum to bool;
        std::cerr << "Something went wrong while it shouldn't have." << std::endl;
    }
    return {};
}





Statement::Statement(std::string_view SQL, sqlite3 *database) {
    sqlite3_stmt* raw_statement = nullptr;
    if (sqlite3_prepare_v2(database, SQL.data(), -1, &raw_statement, nullptr) != SQLITE_OK) {
        throw std::runtime_error(std::format("Failed to pepare statemement: {}", sqlite3_errmsg(database)));
    }
    sql_statement_ = raw_statement;
}

Statement::~Statement() {
    sqlite3_finalize(sql_statement_);
}
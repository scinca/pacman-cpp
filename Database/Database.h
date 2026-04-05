//
// Created by simon on 26.03.26.
//

#ifndef PACMAN_CPP_DATABASE_H
#define PACMAN_CPP_DATABASE_H

#include <expected>
#include <string>
#include <vector>
#include <cstdint>



#include "../third_party/sqlite/sqlite3.h"


enum class MapValidationError;

struct MapInfo {
    int id;
    std::string content;
    std::string name;
    std::string author;
    std::string creation_date;

};

enum class DatabaseError {
    NotFound,
    DatabaseUnavailable,
    InvalidData,
};

class Database {
    public:
    explicit Database(const std::string& db_path= "pacman.db");
    ~Database();
    [[nodiscard]] std::expected<std::string, DatabaseError> GetMap(int map_number) const;
    [[nodiscard]] std::expected<std::int64_t, MapValidationError> AddMap(std::string map, const std::string &map_name, const std::string &author) const;
    [[nodiscard]] std::vector<MapInfo> GetAllMaps() const;

    private:
    [[nodiscard]] std::expected<void, DatabaseError> InitDB() const;
    sqlite3* db_{};

};

class Statement {
    public:
    explicit Statement(std::string_view SQL, sqlite3* database);
    ~Statement();

    [[nodiscard]] sqlite3_stmt* Get() const { return sql_statement_; }

    private:
    sqlite3_stmt* sql_statement_{};
    sqlite3* db_{};
};



#endif //PACMAN_CPP_DATABASE_H
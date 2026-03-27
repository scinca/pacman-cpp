//
// Created by simon on 26.03.26.
//

#ifndef PACMAN_CPP_DATABASE_H
#define PACMAN_CPP_DATABASE_H
#include <expected>
#include <optional>
#include <string>

#include "../third_party/sqlite/sqlite3.h"

enum class MapError {
    NotFound,
    DatabaseUnavailable,
    InvalidData,
};

class Database {
    public:
    explicit Database(const std::string& db_path= "pacman.db");
    ~Database();

    std::expected<std::string, MapError> GetMap(int map_number);
    std::expected<void, MapError> AddMap(std::string map, std::string map_name, std::string author);

    private:
    sqlite3* db_{};

    void InitDB();


};


#endif //PACMAN_CPP_DATABASE_H
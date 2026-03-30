//
// Created by simon on 26.03.26.
//

#ifndef PACMAN_CPP_DATABASE_H
#define PACMAN_CPP_DATABASE_H

#include <expected>
#include <string>

#include "../Map/Map.h"

#include "../third_party/sqlite/sqlite3.h"


enum class MapValidationError;

struct MapInfo {
    int id;
    std::string content;
    std::string name;
    std::string author;
    std::string creation_date;

};

enum class MapError {
    NotFound,
    DatabaseUnavailable,
    InvalidData,
};

class Database {
    public:
    explicit Database(const std::string& db_path= "pacman.db");
    ~Database();
    [[nodiscard]] std::expected<std::string, MapError> GetMap(int map_number) const;
    [[nodiscard]] std::expected<int, MapValidationError> AddMap(std::string map, const std::string &map_name, const std::string &author) const;
    [[nodiscard]] std::vector<MapInfo> GetAllMaps() const;

    private:
    [[nodiscard]] std::expected<void, MapError> InitDB() const;
    sqlite3* db_{};

    std::string default_map_{
        "X000000000000000000000000000000000000000000?0000000###0###0#####0#####0########0#####0#####0###0###0000000000000000000000000000000000000000000000000000###0#0#0###0#0##0##0#0######0#####0#####0###?###00###00000###0#0000000#0######0000000#####00000###00###0#0#0###0#0##0##0#0######0#####0#####0###0###0000000000000000000000000000000000000000000000000000###0#0#0###0#0##0##0#0######0#####0#####0###0###00###00000###0#0000000#0######0000000#####00000###00###0#0#0###0#0##0##0#0######0#####0#####0###0###00000000000000000?0000000000000000000000000000000000###0#0#0###0#0000#00000#0#000#0#0#0#####0###0###00###00000###0#0000000#0000#0#0000000#####00000###00###0#0#0###0#0000##0#00#0#0#0#0#0#0#####0###0###0000000000000000000000000000000000000000000000000000###0#0#0###0#0000#00000#0#000#0#0#0#####0###0###00###00000###0#0000000000000000000000#####00000###0000000000000000000000000000000000000000000000000000###0#0#0###0#0##0##0#0######0#####0#####0###0###00###00000###0#0000000#0######0000000#####00000###0000000000000000000000000000000000000000000000000000###0#0#0###0#0##0##0#0######0#####0#####0###0###00###00000###0#0000000#0######0000000#####00000###00###0#0#0###0#0##0##0#0######0#####0#####0###0###0000000000000000000000000000000000000000000000000000###00000###0#0000000#0######0000000#####00000###00###0#0#0###0#0##0##0#0######0#####0#####0###0###000000000000000000000000000000000000000000000000000"
    };

};

class Statement {
    public:
    explicit Statement(std::string_view SQL, sqlite3* database);
    ~Statement();

    sqlite3_stmt* Get() const { return sql_statement_; } // might be useful later.

    private:
    sqlite3_stmt* sql_statement_{};
    sqlite3* db_{};
};



#endif //PACMAN_CPP_DATABASE_H
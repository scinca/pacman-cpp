//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_MAP_H
#define PACMAN_CPP_MAP_H
#include <expected>
#include <string>


class map {
    public:
    std::expected<void, std::string> load(const std::string& filename);
    std::expected<void, std::string> draw(const std::string& filename);

    private:
    std::string loaded_map;
};


#endif //PACMAN_CPP_MAP_H
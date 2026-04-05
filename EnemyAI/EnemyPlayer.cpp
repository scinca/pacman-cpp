//
// Created by simon on 08.03.26.
//

#include "EnemyPlayer.h"
#include <iostream>
#include <algorithm>
#include "raylib.h"
#include "ApplicationConfig.h"
#include "Time/DeltaTime.h"
#include "Map/Map.h"


EnemyPlayer::EnemyPlayer(Map *map, Time *time, HumanPlayer *player, const int starting_tile, const Color color) : PlayerBase(map, time, starting_tile, color), random_number_generator_(std::random_device{}()){
    player_ = player;
    color_ = color;
    std::tie(position_x_, position_y_) = Map::GetTileCenter(starting_tile);
    start_tile_ = starting_tile;
    GetTile();
    last_known_player_tile_ = player_->GetCurrentTile();


}




void EnemyPlayer::Move() {
    GetTile();
    CenterPosition();

    if (IsAtTileCenter()) {
        PlayerBase::CheckSurroundingTiles();
        if (!CheckMoveValidity(current_direction_)) {
            current_direction_ = Direction::NONE;
        }
            BreadthFirstSearch();
    }
    UpdatePosition();
}

void EnemyPlayer::CheckSurroundingTiles(const int tile, const Direction direction, std::queue<std::pair<int, Direction>> *to_be_explored, std::vector<bool> *explored_set) const {
    const auto& config = ApplicationConfig::GetInstance();
    if (tile > config.TilesX * config.TilesY -1 || tile < 0) {
        return;
    }
    const int tile_x = tile % config.TilesX;
    const int tile_y = tile / config.TilesX;

    if (tile_x > 0 && map_->CanMove(tile - 1) && !explored_set->at(tile - 1)) {

        Direction temp_direction = (direction == Direction::NONE) ? Direction::LEFT : direction;
        explored_set->at(tile - 1) = true;

        to_be_explored->emplace(tile -1,temp_direction);
    }
    if (tile_x < config.TilesX-1 && map_->CanMove(tile + 1) && !explored_set->at(tile + 1)) {
        Direction temp_direction = (direction == Direction::NONE) ? Direction::RIGHT : direction;
        explored_set->at(tile + 1) = true;
        to_be_explored->emplace(  tile+ 1 ,temp_direction);

    }
    if (tile_y > 0 && map_->CanMove(tile - config.TilesX) && !explored_set->at(tile - config.TilesX)) {
        Direction temp_direction = (direction == Direction::NONE) ? Direction::UP : direction;
        explored_set->at(tile - config.TilesX) = true;
        to_be_explored->emplace(tile - config.TilesX,temp_direction);

    }
    if (tile_y < config.TilesY -1 && map_->CanMove(tile + config.TilesX) && !explored_set->at(tile + config.TilesX)) {
        Direction temp_direction = (direction == Direction::NONE) ? Direction::DOWN : direction;
        explored_set->at(tile + config.TilesX) = true;
        to_be_explored->emplace(tile + config.TilesX,temp_direction);

    }
}



void EnemyPlayer::BreadthFirstSearch() {
    const auto& config = ApplicationConfig::GetInstance();
    std::queue<std::pair<int, Direction>>to_be_explored ;
    std::vector<bool>explored_set;
    explored_set.assign(config.TilesX * config.TilesY, false);
    to_be_explored.emplace(current_tile_, Direction::NONE);
    explored_set[current_tile_] = true;

    while (!to_be_explored.empty()) {
        auto [tile , direction] = to_be_explored.front();

        if (tile == player_->GetCurrentTile()) {
            if (GetRandomInt() < config.failure_percentage && !possible_moves_.empty()) {
                current_direction_ = possible_moves_.at(GetRandomValue(0, static_cast<int>(possible_moves_.size()) -1));
                return;
            }

            current_direction_ = direction;
            if (player_->GetCurrentTile() != last_known_player_tile_) {
                last_known_player_tile_ = player_->GetCurrentTile();
            }
            return;
        }
        CheckSurroundingTiles(tile, direction, &to_be_explored, &explored_set);
        to_be_explored.pop();
    }
}

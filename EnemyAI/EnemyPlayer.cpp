//
// Created by simon on 08.03.26.
//

#include "EnemyPlayer.h"
#include <iostream>
#include <algorithm>
#include <optional>
#include <stdexcept>
#include "raylib.h"
#include "ApplicationConfig.h"
#include "Time/DeltaTime.h"
#include "Map/Map.h"


EnemyPlayer::EnemyPlayer(Map *map, Time *time, HumanPlayer *player, const int starting_tile, const Color color) : PlayerBase(map, time, starting_tile, color), random_number_generator_(std::random_device{}()){
    player_ = player;
    color_ = color;
    const auto temp_positions = Map::GetTileCenter(starting_tile);
    if (temp_positions.has_value()) {
        std::tie(position_x_, position_y_) = temp_positions.value();
    }else {
        throw std::runtime_error("starting position invalid ( This shouldn't have happened since Map should have been validated");
    }

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

    if (scattering_) {
        if (current_tile_ == start_tile_) {
            scattering_ = false;
            random_move_count_ = 0;
        }
        else if (random_move_count_ <= 0) {
            random_move_count_ = 0;
            scattering_ = false;
        }else {
            random_move_count_--;
        }
    }

    const int target = scattering_ ? start_tile_ : player_->GetCurrentTile();

    std::queue<std::pair<int, Direction>>to_be_explored ;
    std::vector<bool>explored_set;
    explored_set.assign(config.TilesX * config.TilesY, false);
    to_be_explored.emplace(current_tile_, Direction::NONE);
    explored_set[current_tile_] = true;

    while (!to_be_explored.empty()) {
        auto [tile , direction] = to_be_explored.front();

        if (tile == target) {
            if (GetRandomInt() < config.FailurePercentage && !possible_moves_.empty() && !scattering_) {
                scattering_ = true;
                random_move_count_ = GetRandomInt(1, 4);
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

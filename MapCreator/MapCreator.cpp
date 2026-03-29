//
// Created by simon on 29.03.26.
//

#include "MapCreator.h"

MapCreator::MapCreator(Database *database): db_(database)
{
    temporary_map_.assign(1400, ' ');

}

#include "cell.hpp"

cell::cell(int p_entityID)
{
    entityID = p_entityID;
}

int cell::getEntityID()
{
    return entityID;
}
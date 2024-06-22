#include "cell.hpp"

cell::cell(int p_entityID)
{
    switch (p_entityID)
    {
        case 0: // 0 - space
        {
            entityID = 0;
            break;
        }
        case 1: // 1 - white dot
        { 
            entityID = 1;
            break;
        }
        case 2: // 2 - sand
        {
            entityID = 2;
            break;
        }
        case 3: // 3 - water
        {
            entityID = 3;
            break;
        }
        case 4: // 4 - wood
        {
            entityID = 4;
            flamable = true;
            break;
        }
        case 5: // 5 - fire
        {
            entityID = 5;
            lifeTime = 240;
            break;
        }
        case 6: // 6 - steam
        {
            entityID = 6;
            break;
        }
        case 7: // 7 - smoke
        {
            entityID = 6;
            break;
        }
    }
}

int cell::getEntityID()
{
    return entityID;
}

int cell::getMass()
{
    return mass;
}

int cell::getlifeTime()
{
    return lifeTime;
}

void cell::setMass(int p_mass)
{
    mass = p_mass;
}

void cell::addMass(int p_mass)
{
    mass += p_mass;
}

void cell::reduceMass(int p_mass)
{
    mass -= p_mass;
}

void cell::setID(int p_entityID)
{
    entityID = p_entityID;
}

void cell::reduceLifeTime(int p_lifeTime)
{
    lifeTime -= p_lifeTime;
}

bool cell::isFlamable()
{
    return flamable;
}

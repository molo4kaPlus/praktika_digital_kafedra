#pragma once

// 0 - space
// 1 - white dot
// 2 - sand
// 3 - water
// 4 - wood

class cell
{
    private:
        int entityID;
        int lifeTime;
        int mass;
        bool flamable = false;
    public:
        cell(int p_entityID);
        int getMass();
        void setMass(int p_mass);
        void addMass(int p_mass);
        void reduceMass(int p_mass);
        void reduceLifeTime(int p_lifeTime);
        void setID(int p_entityID);
        int getEntityID();
        int getlifeTime();
        bool hasGravity();
        bool isFlamable();
};  
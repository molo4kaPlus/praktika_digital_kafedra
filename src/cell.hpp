#pragma once

// 0 - space
// 1 - white dot
// 2 - sand

class cell
{
    private:
        int entityID;
    public:
        cell(int p_entityID);
        int getEntityID();
};  
#include "mpsdatamanager.h"

MpsDataManager::MpsDataManager() {}

MpsDataManager* MpsDataManager::instance()
{
    static MpsDataManager self;
    return &self;
}

int MpsDataManager::mapSize() const
{
    return id2uav.size();
}

void MpsDataManager::addUAV(
        uint32_t id, int intIndex,
        osgSim::DOFTransform* pUAV)
{
    id2uav.insert(id, pUAV);
    index2id.insert(intIndex, id);
}

osgSim::DOFTransform* MpsDataManager::findUAV(
        uint32_t id) const
{
    return id2uav.value(id, nullptr);
}

osgSim::DOFTransform* MpsDataManager::findUAVByIndex(
        int index) const
{
    return findUAV(index2id.value(index));
}

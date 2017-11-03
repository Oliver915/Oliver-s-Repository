#ifndef MPSDATAMANAGER_H
#define MPSDATAMANAGER_H

#include <QMap>
#include <osgSim/DOFTransform>

typedef QMap<uint32_t, osgSim::DOFTransform*> ID2UAVMap;
typedef QMap<int, uint32_t> Index2IDMap;

/**
 * @brief The MpsDataManager class
 */
class MpsDataManager
{
public:
    /**
     * @brief ~MpsDataManager
     */
    ~MpsDataManager() {}

    /**
     * @brief instance
     * @return
     */
    static MpsDataManager* instance();

    /**
     * @brief mapSize
     * @return
     */
    int mapSize() const;

    /**
     * @brief addUAV
     */
    void addUAV(
            uint32_t id, int intIndex,
            osgSim::DOFTransform* pUAV);

    /**
     * @brief findUAV
     * @param id
     * @return
     */
    osgSim::DOFTransform* findUAV(uint32_t id) const;

    /**
     * @brief findUAVByIndex
     * @param index
     * @return
     */
    osgSim::DOFTransform* findUAVByIndex(int index) const;

protected:
    // map（id(key),puav(value))
    ID2UAVMap id2uav;

    // map(index(key),id(value))
    Index2IDMap index2id;

private:
    /**
     * @brief MpsDataManager
     */
    MpsDataManager();
};

#endif  // MPSDATAMANAGER_H

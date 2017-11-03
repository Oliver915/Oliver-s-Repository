#ifndef MPSHUDHANDLER_H
#define MPSHUDHANDLER_H

#include <osgSim/DOFTransform>
#include <osgText/Text>

/**
 * @brief The MpsHUDHandler class
 */
class MpsHUDHandler
{
public:
    /**
     * @brief MpsHUDHandler
     * @param txt
     */
    MpsHUDHandler(osgText::Text* txt);
    ~MpsHUDHandler() {}

    /**
     * @brief setLable
     * @param name
     */
    void setLable(const std::string& name);

    /**
     * @brief updateText
     * @param doft
     */
    void updateText(const osgSim::DOFTransform* doft);

protected:
    // the text node which is displayed in HUD
    osgText::Text* text;
};

#endif  // HUDHANDLER_H

#include "mpshudhandler.h"
#include <iomanip>
#include <sstream>

// const
static const double ANGLE = 180 / 3.1415926;
static const double COOR_CONVERT_FACTOR = 180 / 20037508.34;

MpsHUDHandler::MpsHUDHandler(osgText::Text* txt)
    : text(txt)
{
}

void MpsHUDHandler::setLable(const std::string& name)
{
    if (text) text->setText(name);
}

void MpsHUDHandler::updateText(
        const osgSim::DOFTransform* doft)
{
    if (doft == nullptr) return;

    double y = doft->getCurrentTranslate().y() + 1450000;
    double vExp = exp(
            y / (3.1415926 / 180) * COOR_CONVERT_FACTOR);
    double latitude = (360 / 3.1415926) * atan(vExp) - 90;

    std::ostringstream os;
    os << "Name : " << doft->getName() << std::endl
       << std::endl
       << "Longtitude : " << std::setprecision(10)
       << (doft->getCurrentTranslate().x() + 4950000) *
                    COOR_CONVERT_FACTOR
       << std::endl
       << std::endl
       << "Latitude : " << latitude << std::endl
       << std::endl
       << std::setprecision(6)
       << "Height : " << doft->getCurrentTranslate().z()
       << std::endl
       << std::endl
       << "Heading : "
       << doft->getCurrentHPR().x() * (-ANGLE) << std::endl
       << std::endl
       << "Pitch : " << doft->getCurrentHPR().y() * ANGLE
       << std::endl
       << std::endl
       << "Rolling : " << doft->getCurrentHPR().z() * ANGLE;

    setLable(os.str());
}

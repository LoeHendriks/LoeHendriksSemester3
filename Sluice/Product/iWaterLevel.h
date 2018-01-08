#ifndef IWATERLEVEL_H
#define IWATERLEVEL_H

#include "Enums.h"


    class iWaterLevel
    {
        public:
            virtual ~iWaterLevel() {};
            virtual WaterLevel GetWaterLevel() = 0;
    };


#endif

#pragma once

#include <string>
#include "../Entity/Component.h"

class SpriteComponent : public Component{
    private:
        std::string filename;
        

    public:
        SpriteComponent(){};

        void setFilename(const std::string& filename){
            this->filename = filename;
        }

        std::string getFilename() const{
            return filename;
        }
};
#ifndef PICTURE_H
#define PICTURE_H

#include <QThread>
#include "SDL2/SDL.h"
#include "SDL2/SDL_vulkan.h"
#include "opencv2/core.hpp"
#include "opencv2/photo.hpp"

class Picture : public QThread
{
public:
    Picture();
    void crypto(QString filename);
};

#endif // PICTURE_H

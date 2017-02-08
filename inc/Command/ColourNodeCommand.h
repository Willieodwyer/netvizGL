//
// Created by werl on 15/01/17.
//

#ifndef NETVIZGL_COLOURNODECOMMAND_H
#define NETVIZGL_COLOURNODECOMMAND_H

#include "../GLWindow.h"
#include "Command.h"

class ColourNodeCommand: public Command
{
private:
    GLWindow *window;
public:
    ColourNodeCommand(GLWindow *pWindow);
    void execute() override;
};

#endif //NETVIZGL_COLOURNODECOMMAND_H

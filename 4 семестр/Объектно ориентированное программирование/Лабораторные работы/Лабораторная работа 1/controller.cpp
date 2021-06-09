#include "controller.h"
#include "rc.h"
#include "functions.h"
#include "figure.h"
#include <iostream>


rc_type controller(myscene_t scene, int act_number, const data& act)
{
    static figure fig = init_fig();
    rc_type rc = OK;
    if (act_number == DOWNLOAD)
    {
        rc = download_model(fig, act);
    }
    else if (act_number ==  MOVE_NUMBER)
    {
        rc = move_fig(fig, act);
    }
    else if (act_number == ROTATION_NUMBER)
    {
        rc = rotation_fig(fig, act);
    }
    else if (act_number == SCALE_NUMBER)
    {
        rc = scale_fig(fig, act);
    }
    else if (act_number == DELETE_NUMBER)
    {
        rc = free_fig(fig);
    }
    else if (act_number == DRAW_NUMBER)
    {
        rc = draw_fig(fig, scene);
    }
    else
    {
        rc = ERR_PARAMETR;
    }

    return rc;
}

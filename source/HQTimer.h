#pragma once

#include <windows.h>


class HQTimer
{
private:
    double cc,fq, t,st, dt1,st1, iFR;
    bool first;
    LARGE_INTEGER CC;

public:
    double dt, FR, iv, iv1;
    // delta time, FrameRate, interval, intervalFR

    HQTimer();
    bool update();
};

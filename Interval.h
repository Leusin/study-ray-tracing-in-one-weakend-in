#pragma once
#ifndef INTERVAL_H
#define INTERVAL_H

#include "RTWeekend.h"

struct Interval
{
    Interval()
        : Min(+Infinity), Max(-Infinity)
    {
    }

    Interval(double min, double max)
        : Min(min), Max(max)
    {
    }

    double Size() const
    {
        return Max - Min;
    }

    bool Contains(double value) const
    {
        return Min <= value && value <= Max;
    }

    static const Interval Empty;
    static const Interval Universe;

    double Min = 0.0;
    double Max = 0.0;
};

const Interval Interval::Empty(+Infinity, -Infinity);
const Interval Interval::Universe(-Infinity, +Infinity);

#endif
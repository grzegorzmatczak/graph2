#pragma once

#include <opencv2/opencv.hpp>
#include "qglobal.h"

struct ProcessingStruct
{
    cv::Mat frame;
    qint64 timestamp;
};
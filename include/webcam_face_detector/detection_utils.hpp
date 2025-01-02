#ifndef DETECTION_UTILS_HPP_
#define DETECTION_UTILS_HPP_

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <math.h>

#include <geometry_msgs/msg/pose_array.hpp>
#include <geometry_msgs/msg/pose.hpp>

namespace webcam_face_detector
{
    class FaceDetector
    {
        public:
        FaceDetector():cap(cv::VideoCapture(0))
        {}

        bool setup(std::string cascade_path);
        geometry_msgs::msg::PoseArray detect();

        private:
        cv::CascadeClassifier faceCascade;
        cv::VideoCapture cap;
        const double FOCAL_LENGTH = 800.0;
        const double FACE_SIZE = 15.0;
    };
}

#endif
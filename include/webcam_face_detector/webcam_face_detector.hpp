#ifndef WEBCAM_FACE_DETECTOR_HPP_
#define WEBCAM_FACE_DETECTOR_HPP_

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_array.hpp>
#include <string>
#include <chrono>

#include "detection_utils.hpp"

using namespace std::chrono_literals;

namespace webcam_face_detector
{
    class WebCamFaceDetector : public rclcpp::Node
    {
        public:
        explicit WebCamFaceDetector(const rclcpp::NodeOptions& option);

        void detection_callback();

        private:
        rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        std::shared_ptr<FaceDetector> face_detector;
        std::string cascade_path;
    };
}

#endif
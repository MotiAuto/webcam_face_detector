#include "webcam_face_detector/webcam_face_detector.hpp"

namespace webcam_face_detector
{
    WebCamFaceDetector::WebCamFaceDetector(const rclcpp::NodeOptions& option) : Node("WebCamFaceDetector", option)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::PoseArray>("/human", rclcpp::SystemDefaultsQoS());

        timer_ = this->create_wall_timer(1ms, std::bind(&WebCamFaceDetector::detection_callback, this));

        this->declare_parameter("cascade_path", "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml");
        this->get_parameter("cascade_path", cascade_path);

        face_detector = std::make_shared<FaceDetector>();

        const auto setup_result = face_detector->setup(cascade_path);

        if(setup_result)
        {
            RCLCPP_INFO(this->get_logger(), "Start WebCamFaceDetector");
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to setup FaceDetector");
        }
    }

    void WebCamFaceDetector::detection_callback()
    {
        const auto result = face_detector->detect();

        publisher_->publish(result);
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(webcam_face_detector::WebCamFaceDetector)
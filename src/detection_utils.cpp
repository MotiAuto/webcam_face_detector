#include "webcam_face_detector/detection_utils.hpp"

namespace webcam_face_detector
{
    bool FaceDetector::setup(std::string cascade_path)
    {
        if(!faceCascade.load(cascade_path))
        {
            return false;
        }

        if(!cap.isOpened())
        {
            return false;
        }

        return true;
    }

    geometry_msgs::msg::PoseArray FaceDetector::detect()
    {
        cv::Mat frame, gray;
        cap >> frame;
        if(frame.empty())
        {
            geometry_msgs::msg::PoseArray poses;
            poses.header.frame_id = "webcam";
            return poses;
        }

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(10, 10), cv::Size(500,500));

        if(faces.empty())
        {
            geometry_msgs::msg::PoseArray poses;
            poses.header.frame_id = "webcam";
            return poses;
        }
        else
        {
            geometry_msgs::msg::PoseArray poses;
            poses.header.frame_id = "webcam";
            
            for(const auto& face : faces)
            {
                const auto x = (face.x + face.width / 2.0) - 300;
                const auto y = (FOCAL_LENGTH * FACE_SIZE) / face.width;
                geometry_msgs::msg::Pose p;
                p.position.x = (x* 0.01) / 4.0;
                p.position.y = y * 0.01;
                p.position.z = 0.0;

                poses.poses.push_back(p);
            }

            return poses;
        }
    }
}
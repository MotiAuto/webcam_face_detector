cmake_minimum_required(VERSION 3.5)
project(webcam_face_detector)

find_package(ament_cmake_auto REQUIRED)
find_package(OpenCV REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_library(target_webcam_face_detector SHARED
  DIRECTORY src
)
include_directories(${OpenCV_INCLUDE_DIRS})
target_include_directories(target_webcam_face_detector
  SYSTEM PUBLIC
)

rclcpp_components_register_node(target_webcam_face_detector
  PLUGIN "webcam_face_detector::WebCamFaceDetector"
  EXECUTABLE webcam_face_detector_node
)
target_link_libraries(target_webcam_face_detector ${OpenCV_LIBRARIES})

ament_auto_package(
  INSTALL_TO_SHARE
)
#include <string>
#include <ros/ros.h>
#include "chilitagsdetector.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    //ROS initialization
    ros::init(argc, argv, "ros_markers");
    ros::NodeHandle rosNode;
    ros::NodeHandle _private_node("~");

    // load parameters
    string configFilename;
    _private_node.param<string>("markers_configuration", configFilename, "");
    string camera_frame;
    _private_node.param<string>("camera_frame_id", camera_frame, "camera");
    double defaultTagSize;
    _private_node.param<double>("default_marker_size", defaultTagSize, USE_CHILITAGS_DEFAULT_PARAM);
    bool omitOtherTags;
    _private_node.param<bool>("omit_other_tags", omitOtherTags, false);


    if (configFilename.empty() && omitOtherTags == true) {
        ROS_ERROR_STREAM("If a marker configuration file is not passed as a parameter,\n" <<
                         "omitOtherTags must not be set to true or no tags will be detected.");
        return(1);
    }

    // initialize the detector by subscribing to the camera video stream
    ChilitagsDetector detector(rosNode, camera_frame, configFilename, omitOtherTags,defaultTagSize);
    ROS_INFO("ros_markers is ready. Marker locations will be published on TF when detected.");
    ROS_INFO_STREAM("Camera frame is: " << camera_frame );
    ros::spin();

    return 0;
}


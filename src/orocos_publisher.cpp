/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
#include "std_msgs/String.h"
#include "sensor_msgs/JointState.h"
#include "geometry_msgs/Pose.h"
#include "orocos_publisher.hpp"
// %EndTag(MSG_HEADER)%

#include <sstream>

static int i = 0;
static RGM_ROBOT ur_ctrl;

void joint_chatterCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
  // ROS_INFO("I heard position: [%f %f %f %f %f %f]", msg->position[0], msg->position[1], msg->position[2]
  // , msg->position[3], msg->position[4], msg->position[5]);

  // ROS_INFO("I heard velocity: [%f %f %f %f %f %f]", msg->velocity[0], msg->velocity[1], msg->velocity[2]
  // , msg->velocity[3], msg->velocity[4], msg->velocity[5]);
  // ROS_INFO("I heard effect: [%f %f %f %f %f %f]", msg->effort[0], msg->effort[1], msg->effort[2]
  // , msg->effort[3], msg->effort[4], msg->effort[5]);

  for(i=0;i<6;i++){
    ur_ctrl.actual_position[i]  = msg->position[i];
    ur_ctrl.actual_velocity[i]  = msg->velocity[i];
    ur_ctrl.actual_torque[i]  = msg->effort[i];
   }


}


void command_chatterCallback(const geometry_msgs::Pose::ConstPtr& msg)
{
  // ROS_INFO("I heard position: [%f %f %f %f %f %f]", msg->position[0], msg->position[1], msg->position[2]
  // , msg->position[3], msg->position[4], msg->position[5]);

  // ROS_INFO("I heard velocity: [%f %f %f %f %f %f]", msg->velocity[0], msg->velocity[1], msg->velocity[2]
  // , msg->velocity[3], msg->velocity[4], msg->velocity[5]);
  // ROS_INFO("I heard effect: [%f %f %f %f %f %f]", msg->effort[0], msg->effort[1], msg->effort[2]
  // , msg->effort[3], msg->effort[4], msg->effort[5]);

  
    ur_ctrl.target_tcp_frame.point[0]  = msg->position.x;
    ur_ctrl.target_tcp_frame.point[1]  = msg->position.y;
    ur_ctrl.target_tcp_frame.point[2]  = msg->position.z;

    ur_ctrl.target_tcp_frame.orientation[0] = msg->orientation.x;
    ur_ctrl.target_tcp_frame.orientation[1] = msg->orientation.y;
    ur_ctrl.target_tcp_frame.orientation[2] = msg->orientation.z;
    ur_ctrl.target_tcp_frame.orientation[3] = msg->orientation.w;

}

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  const int jtNr = 6;
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
// %Tag(INIT)%
  ros::init(argc, argv, "talker");
  ros::init(argc, argv, "listener");
// %EndTag(INIT)%

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
// %Tag(NODEHANDLE)%
  ros::NodeHandle n1;
  ros::NodeHandle n2;
  ros::NodeHandle n3;
  ros::NodeHandle n4;
  ros::NodeHandle n5;
  ros::NodeHandle n6;

  ros::NodeHandle n;
// %EndTag(NODEHANDLE)%

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
// %Tag(PUBLISHER)%
  std::vector<ros::Publisher> chatter_pub;
  chatter_pub.push_back(n1.advertise<std_msgs::String>("chatter1", 1000));
  chatter_pub.push_back(n2.advertise<std_msgs::String>("chatter2", 1000));
  chatter_pub.push_back(n3.advertise<std_msgs::String>("chatter3", 1000));
  chatter_pub.push_back(n4.advertise<std_msgs::String>("chatter4", 1000));
  chatter_pub.push_back(n5.advertise<std_msgs::String>("chatter5", 1000));
  chatter_pub.push_back(n6.advertise<std_msgs::String>("chatter6", 1000));

  ros::Subscriber sub_jnt = n.subscribe("joint_states", 1, joint_chatterCallback);
  ros::Subscriber sub_tcp = n.subscribe("pc_command", 1, command_chatterCallback);


// %EndTag(PUBLISHER)%

// %Tag(LOOP_RATE)%
  ros::Rate loop_rate(10);
// %EndTag(LOOP_RATE)%

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
// %Tag(ROS_OK)%
  int count = 0;

  while (ros::ok())
  {
// %EndTag(ROS_OK)%
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
// %Tag(FILL_MESSAGE)%
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count<<" "<<chatter_pub.size();
    msg.data = ss.str();
// %EndTag(FILL_MESSAGE)%

// %Tag(ROSCONSOLE)%
    //ROS_INFO("%s", msg.data.c_str());
// %EndTag(ROSCONSOLE)%

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
// %Tag(PUBLISH)%
for(i=0;i<jtNr;i++){
      chatter_pub[i].publish(msg);
    }
// %EndTag(PUBLISH)%

// %Tag(SPINONCE)%
    ros::spinOnce();
// %EndTag(SPINONCE)%

// %Tag(RATE_SLEEP)%
    loop_rate.sleep();
// %EndTag(RATE_SLEEP)%
    ++count;
  }


  return 0;
}
// %EndTag(FULLTEXT)%

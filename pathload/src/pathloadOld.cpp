/*
 * @Author: YinPengFei
 * @Date: 2022-03-31 19:51:13
 * @LastEditTime: 2022-03-31 15:48:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ros/src/pathplay/src/pathload.cpp
 */
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <vector>
#include <iostream>
#include <fstream>
// #include <tf/transform_broadcaster.h>
// #include <tf/tf.h>

// int main(int argc, char **argv)
// {
//     ros::init(argc, argv, "showpath");

//     ros::NodeHandle ph;
//     ros::Publisher path_pub = ph.advertise<nav_msgs::Path>("trajectory", 1, true);

//     ros::Time current_time, last_time;
//     current_time = ros::Time::now();
//     last_time = ros::Time::now();

//     nav_msgs::Path path;
//     path.header.stamp = current_time;
//     path.header.frame_id = "pathpoint";

//     double x = 0.0;
//     double y = 0.0;
//     double th = 0.0;
//     double vx = 0.1;
//     double vy = -0.1;
//     double vth = 0.1;

//     ros::Rate loop_rate(1);
//     while (ros::ok())
//     {
//         current_time = ros::Time::now();
//         //compute odometry in a typical way given the velocities of the robot
//         double dt = 0.1;
//         double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
//         double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
//         double delta_th = vth * dt;

//         x += delta_x;
//         y += delta_y;
//         th += delta_th;

//         geometry_msgs::PoseStamped this_pose_stamped;
//         this_pose_stamped.pose.position.x = x;
//         this_pose_stamped.pose.position.y = y;

//         geometry_msgs::Quaternion goal_quat = tf::createQuaternionMsgFromYaw(th);
//         this_pose_stamped.pose.orientation.x = goal_quat.x;
//         this_pose_stamped.pose.orientation.y = goal_quat.y;
//         this_pose_stamped.pose.orientation.z = goal_quat.z;
//         this_pose_stamped.pose.orientation.w = goal_quat.w;

//         this_pose_stamped.header.stamp = current_time;
//         this_pose_stamped.header.frame_id = "odom";
//         path.poses.push_back(this_pose_stamped);

//         path_pub.publish(path);
//         ros::spinOnce(); // check for incoming messages

//         last_time = current_time;
//         loop_rate.sleep();
//     }

//     return 0;
// }
using namespace std;

vector<vector<float>> csvToVector(string filepath)
{
    ifstream inFile(filepath, ios::in);
    if (!inFile)
    {
        cout << "打开文件失败！" << endl;
        exit(1);
    }
    int i = 0;
    string line, field;

    int height = 12605, weight = 3;
    vector<vector<float>> pathpoints(height, vector<float>(weight));

    while (getline(inFile, line)) //getline(inFile, line)表示按行读取CSV文件中的数据
    {
        istringstream sin(line); //将整行字符串line读入到字符串流sin中

        getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
        pathpoints[i][0] = atof(field.c_str());

        getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
        pathpoints[i][1] = atof(field.c_str());

        getline(sin, field); //将字符串流sin中的字符读入到field字符串中，读完为止
        pathpoints[i][2] = atof(field.c_str());

        i++;
    }
    inFile.close();
    return pathpoints;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "showpath");           // node_name:showpath
    ros::NodeHandle sp1;                         // 创建句柄节点
    ros::Publisher path_pub = sp1.advertise<nav_msgs::Path>("trajectory", 100000, true);
    ros::Rate loop_rate(10);                     // 循环频率10Hz

    nav_msgs::Path now_path;
    geometry_msgs::PoseStamped pose;

    /*路径序列*/
    now_path.header.frame_id = "world";          // 设置坐标系  
    now_path.header.stamp = ros::Time::now();    // 设置时间戳   
    
    /*点的位置*/
    pose.header.stamp = ros::Time::now();        // 设置时间戳    
    pose.header.frame_id = "world";              // 设置参考系      

    /*读取地图数据*/ 
    string pathfile = "/home/yin/hybrid_astar_ws/src/pathload/waypoints/waypoints.csv";
    auto pathpoints = csvToVector(pathfile);     // csv列转化为数组

    while (ros::ok())
    {
        // cout << pathpoints.size() << endl;
        for (int i = 0; i < pathpoints.size(); i=i+100)
        {
            // cout << i << endl;
            pose.pose.position.x = pathpoints[i][0];
            pose.pose.position.y = pathpoints[i][1];
            pose.pose.position.z = 0;

            pose.pose.orientation.x = 0.0;
            pose.pose.orientation.y = 0.0;
            pose.pose.orientation.z = 0.0;
            now_path.poses.push_back(pose);
            // ROS_INFO("POSE WRITE IS OK!");
        }

        path_pub.publish(now_path);              // 发布读取的轨迹

        ros::spinOnce();                         // 循环一次退出 
        loop_rate.sleep();
    }

    return 0;
}

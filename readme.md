roslaunch car_model spawn_car.launch
rviz
roslaunch lqr_steering frenet_lqr.launch 


source devel/setup.sh
roslaunch car_model spawn_car.launch
roslaunch purepursuit splinepath.launch 
roslaunch purepursuit purepursuit.launch
rviz 中add /splinepoints /rvizpath  /smart（在rviz显示中，红色为小车运动轨迹，绿色为规划模块给出的轨迹）
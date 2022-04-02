/*
 * @Author: your name
 * @Date: 2021-10-13 10:43:57
 * @LastEditTime: 2021-10-13 17:33:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /quintic_lqr/include/frenet_path.h
 */
#ifndef _FRENET_PATH_H
#define _FRENET_PATH_H

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include "cpprobotics_types_double.h"

namespace cpprobotics {

class FrenetPath {
 public:
  // float cd = 0.0;
  // float cv = 0.0;
  // float cf = 0.0;

  /*
  cpprobotics_types_double.h
  using Vec_f = std::vector<double>;
  using Poi_f = std::array<double, 2>;
  using Vec_Poi = std::vector<Poi_f>;
  */

  Vec_f t;
  Vec_f x;
  Vec_f x_d;
  Vec_f x_dd;
  // Vec_f d_ddd;
  Vec_f y;
  Vec_f y_d;
  Vec_f y_dd;
  // Vec_f s_ddd;

  // Vec_f x;
  // Vec_f y;
  // Vec_f yaw;
  // Vec_f ds;
  // Vec_f c;

  Vec_f k;          // 曲率
  Vec_f threat;     // 航向角

  // float max_speed;
  // float max_accel;
  // float max_curvature;
};

using Vec_Path = std::vector<FrenetPath>;
}
#endif

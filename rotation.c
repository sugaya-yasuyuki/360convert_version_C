/* ********************************************************** rotation.c *** *
 * 回転行列に関する関数
 *
 * Copyright (C) 2025 Yasuyuki SUGAYA <sugaya.yasuyuki.jp@tut.jp>
 *
 *                                 Time-stamp: <2025-05-08 14:36:27 sugaya>
 * ************************************************************************* */
#include <math.h>
#include <Eigen/Dense>

/* ************************************************************************* *
 * 回転角度を度からラジアンに変換
 * ************************************************************************* */
double
DEG2RAD (double deg) {
  return deg * M_PI / 180.0;
}

/* ************************************************************************* *
 * 回転軸を指定した回転行列
 * ************************************************************************* */
Eigen::MatrixXd 
rotation_by_axis (const Eigen::VectorXd&	n,
		  double			angle) {
  Eigen::MatrixXd R(3, 3);
  double cos_a = cos(angle);
  double sin_a = sin(angle);
  
  R(0, 0) = cos_a + n(0) * n(0) * (1 - cos_a);
  R(0, 1) = n(0) * n(1) * (1 - cos_a) - n(2) * sin_a;
  R(0, 2) = n(2) * n(0) * (1 - cos_a) + n(1) * sin_a;
  R(1, 0) = n(0) * n(1) * (1 - cos_a) + n(2) * sin_a;
  R(1, 1) = cos_a + n(1) * n(1) * (1 - cos_a);
  R(1, 2) = n(1) * n(2) * (1 - cos_a) - n(0) * sin_a;
  R(2, 0) = n(2) * n(0) * (1 - cos_a) - n(1) * sin_a;
  R(2, 1) = n(1) * n(2) * (1 - cos_a) + n(0) * sin_a;
  R(2, 2) = cos_a + n(2) * n(2) * (1 - cos_a);

  return R;
}

/* ************************************************************************* *
 * X軸回りの回転行列
 * ************************************************************************* */
Eigen::MatrixXd
rotation_x (double angle) {
  Eigen::MatrixXd R = Eigen::MatrixXd::Identity(3, 3);
  R(1, 1) = cos(angle);
  R(1, 2) =-sin(angle);
  R(2, 1) = sin(angle);
  R(2, 2) = cos(angle);

  return R;
}

/* ************************************************************************* *
 * Y軸回りの回転行列
 * ************************************************************************* */
Eigen::MatrixXd
rotation_y (double angle) {
  Eigen::MatrixXd R = Eigen::MatrixXd::Identity(3, 3);
  R(0, 0) = cos(angle);
  R(0, 2) = sin(angle);
  R(2, 0) =-sin(angle);
  R(2, 2) = cos(angle);

  return R;
}

/* ************************************************************************* *
 * Z軸回りの回転行列
 * ************************************************************************* */
Eigen::MatrixXd
rotation_z (double angle) {
  Eigen::MatrixXd R = Eigen::MatrixXd::Identity(3, 3);
  R(0, 0) = cos(angle);
  R(0, 1) =-sin(angle);
  R(1, 0) = sin(angle);
  R(1, 1) = cos(angle);

  return R;
}

/* *************************************************** End of rotation.c *** */

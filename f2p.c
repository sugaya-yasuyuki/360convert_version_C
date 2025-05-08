/* *************************************************************** f2p.c *** *
 * 魚眼画像から透視投影画像への変換クラス
 *
 * Copyright (C) 2025 Yasuyuki SUGAYA <sugaya.yasuyuki.jp@tut.jp>
 *
 *                               Time-stamp: <2025-05-08 14:38:08 sugaya>
 * ************************************************************************* */
#include <math.h>
#include <Eigen/Dense>
#include "f2p.h"
#include "rotation.h"

F2P::F2P(int _iw, int _ih, int _ow, int _oh, int _interp_type) {
  iw = _iw;
  ih = _ih;
  ow = _ow;
  oh = _oh;
  interp_type = _interp_type;

  f = ih / M_PI;

  dst = cv::Mat (cv::Size(ow, oh), CV_8UC3);
  map_u = cv::Mat (cv::Size(ow, oh), CV_32FC1);
  map_v = cv::Mat (cv::Size(ow, oh), CV_32FC1);
}

F2P::~F2P() {
  
}

void
F2P::generate_map (double angle_u,
		   double angle_v,
		   double angle_z,
		   double scale) {
  // 画像面を回転する回転行列の計算
  Eigen::MatrixXd R = rotation_y(angle_u) * rotation_x(angle_v);
  Eigen::VectorXd axis = Eigen::VectorXd::Zero(3);
  axis(2) = 1.0;
  Eigen::MatrixXd Ri = rotation_by_axis (R * axis, angle_z);

  // 透視投影画像の各画素に対する画素値を全方位画像から取得する
  int owh = ow / 2;
  int ohh = oh / 2;
  int iwh = iw / 2;
  
  for (int v = 0; v < dst.rows; v++) {
    for (int u = 0; u < dst.cols; u++) {

      // 画素位置に対する３次元ベクトルを計算
      Eigen::VectorXd Xc(3);
      Xc(0) = u - owh;
      Xc(1) = v - ohh;
      Xc(2) = f;

      // 回転した画像面に対応するようにベクトルを回転
      Eigen::VectorXd X = Ri * R * Xc;

      // 3次元ベクトルを水平方向、垂直方向の角度に変換
      double theta = atan2(X(1), X(0));
      double phi   = atan2(sqrt (X(0) * X(0) + X(1) * X(1)), X(2));

      // 角度から全方位画像の画素位置を計算
      double r = (f / scale) * phi;
      map_u.at<float>(v, u) = r * cos (theta) + iwh - 0.5;
      map_v.at<float>(v, u) = r * sin (theta) + iwh - 0.5;
    }
  }
}

cv::Mat
F2P::generate_image (const cv::Mat&	src) {
  cv::remap (src, dst, map_u,
	     map_v, interp_type, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
  return dst;
}

/* ******************************************************** End of f2p.c *** */

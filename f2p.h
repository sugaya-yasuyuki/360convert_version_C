/* *************************************************************** F2P.h *** *
 * 魚眼画像から透視投影画像を生成するクラス ヘーダファイル
 *
 * Copyright (C) 2025 Yasuyuki SUGAYA <sugaya.yasuyuki.jp@tut.jp>
 *
 *                                 Time-stamp: <2025-05-08 14:57:23 sugaya>
 * ************************************************************************* */
#ifndef	__F2P_H__
#define	__F2P_H__

#include <opencv2/opencv.hpp>

class F2P {
 public:
  F2P(int _iw, int _ih, int _ow, int _oh, int _interp_type);
  ~F2P();
  
  void generate_map (double angle_u, double angle_v, double angle_z, double scale);
  cv::Mat generate_image (const cv::Mat& src);
  
 private:
  int iw;
  int ih;
  int ow;
  int oh;
  int interp_type;
  double f;
  cv::Mat dst;
  cv::Mat map_u;
  cv::Mat map_v;
};

#endif	/* __F2P_H__ */

/* ******************************************************** End of F2P.h *** */

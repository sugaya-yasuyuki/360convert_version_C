/* *************************************************************** E2P.h *** *
 * 正距円筒画像から透視投影画像を生成するクラス ヘーダファイル
 *
 * Copyright (C) 2025 Yasuyuki SUGAYA <sugaya.yasuyuki.jp@tut.jp>
 *
 *                                 Time-stamp: <2025-05-08 14:37:21 sugaya>
 * ************************************************************************* */
#ifndef	__E2P_H__
#define	__E2P_H__

#include <opencv2/opencv.hpp>

class E2P {
 public:
  E2P(int _iw, int _ih, int _ow, int _oh, int _interp_type);
  ~E2P();
  
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

#endif	/* __E2P_H__ */

/* ******************************************************** End of E2P.h *** */

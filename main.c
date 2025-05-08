/* ************************************************************** main.c *** *
 * 全方位画像から透視投影画像を生成するプログラム
 *
 * Copyright (C) 2025 Yasuyuki SUGAYA <sugaya.yasuyuki.jp@tut.jp>
 *
 *                                 Time-stamp: <2025-05-08 14:56:21 sugaya>
 * ************************************************************************* */
#include "getargs.h"
#include "rotation.h"
#include "e2p.h"
#include "f2p.h"

/* ************************************************************************* */
int
main (int argc, char* argv[]) {
  /* 引数のチェック*/
  Argument* arg;
  if (!getargs (argc, argv, &arg)) usage (arg, argv[0]);

  /* 入力画像の読み込み */
  cv::Mat src = cv::imread (arg->input_filename, cv::IMREAD_COLOR);

  /* 出力画像の大きさ決定 */
  if (arg->output_width == 0 && arg->output_height == 0) {
    double f = src.rows / M_PI;
    int w = 2.0 * tan(DEG2RAD(arg->fov_u) / 2.0) * f;
    int h = 2.0 * tan(DEG2RAD(arg->fov_v) / 2.0) * f;
    arg->output_width  = w;
    arg->output_height = h;
  }

  /* 変換 */
  cv::Mat dst;
  if (arg->image_type == 0) {
    E2P converter (src.cols, src.rows, arg->output_width, arg->output_height,
		   arg->interp_type);
    converter.generate_map (DEG2RAD(arg->angle_u),
			    DEG2RAD(arg->angle_v),
			    DEG2RAD(arg->angle_z),
			    arg->scale);
    dst = converter.generate_image (src);
  } else {
    F2P converter (src.cols, src.rows, arg->output_width, arg->output_height,
		   arg->interp_type);
    converter.generate_map (DEG2RAD(arg->angle_u),
			    DEG2RAD(arg->angle_v),
			    DEG2RAD(arg->angle_z),
			    arg->scale);
    dst = converter.generate_image (src);
  }
  cv::imwrite (arg->output_filename, dst);
  
  return 0;
}


/* ******************************************************* End of main.c *** */

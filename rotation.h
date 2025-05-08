/* ********************************************************** rotation.h *** *
 * 回転行列に関する関数 ヘーダファイル
 *
 * Copyright (C) 2025 Yasuyuki SUGAYA <sugaya.yasuyuki.jp@tut.jp>
 *
 *                                 Time-stamp: <2025-05-08 14:56:40 sugaya>
 * ************************************************************************* */
#ifndef	__ROTATION_H__
#define	__ROTATION_H__

#include <Eigen/Dense>

double DEG2RAD (double deg);
Eigen::MatrixXd rotation_by_axis (const Eigen::VectorXd&	n,
				  double			angle);
Eigen::MatrixXd rotation_x 	 (double angle);
Eigen::MatrixXd rotation_y 	 (double angle);
Eigen::MatrixXd rotation_z 	 (double angle);

  
#endif	/* __ROTATION_H__ */

/* *************************************************** End of rotation.h *** */

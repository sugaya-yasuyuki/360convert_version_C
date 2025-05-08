/* *********************************************************** getargs.h *** *
 * 引数解析関数 ヘッダファイル
 *
 * Copyright (C) 1998-2025 Yasuyuki SUGAYA <sugaya.yasuyuki.jp@tut.jp>
 *
 *                               Time-stamp: <2025-05-08 14:56:54 sugaya>
 * ************************************************************************* */
#ifndef	__COMMON_FUNC_GETARGS_H__
#define	__COMMON_FUNC_GETARGS_H__

/* ************************************************************************* *
 * 引数用の構造体
 * 	- プログラムに必要な引数に応じてメンバを変更してください -
 * ************************************************************************* */
typedef struct _Argument {
  char*	 input_filename;
  char*  output_filename;
  int    output_width;
  int    output_height;
  int    image_type;
  int	 interp_type;
  double fov_u;
  double fov_v;
  double angle_u;
  double angle_v;
  double angle_z;
  double scale;
} Argument;

/* ************************************************************************* *
 * 関数
 * ************************************************************************* */

void		usage		(Argument	*arg,
				 char		*cmd);         /* 使い方表示 */
void		version 	(Argument	*arg); /* バージョン情報表示 */
void		argument_free	(Argument	*arg);         /* メモリ解放 */
Argument*	argument_new 	(void);                  /* 引数構造体の生成 */
int		getargs 	(int		argc,        /* 引数解析関数 */
				 char		**argv,
				 Argument	**arg);

#endif	/* __COMMON_FUNC_GETARGS_H__ */

/* **************************************************** End of getargs.h *** */

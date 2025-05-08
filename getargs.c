/* *********************************************************** getargs.c *** *
 * 引数解析関数
 *
 * Copyright (C) 1998-2025 Yasuyuki SUGAYA <sugaya.yasuyuki.jp@tut.jp>
 *
 *                              Time-stamp: <2025-05-08 15:00:53 sugaya>
 * ************************************************************************* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getargs.h"

const char*  PROGRAM    = "360convert";
const char*  VERSION    = "1.0.0";
const double DEFAULT_UA = 0;
const double DEFAULT_VA = 0;
const double DEFAULT_ZA = 0;
const double DEFAULT_SCALE = 1.0;

/* 仕様表示 **************************************************************** */
void
usage (Argument	*arg,
       char	*cmd) {
  fprintf (stderr,
	   "\n"
	   "* ***************************************************************"
	   "********** *\n"
	   "* This program generates a perspective view from an omnidirectional image.\n"
	   "* ***************************************************************"
	   "********** *\n");
  fprintf (stderr,
	   "Usage:%s input output #fov_u #fov_v\n", cmd);
  fprintf (stderr,
	   "\t --image-type #: 0: Equirectangular, 1: Fisheye (Default 0)\n"
	   "\t --interp-type #: 0: Nearest, 1: Linear, 2: Qubic (Default 1)\n"
	   "\t --ow #: Output image width (Default 0 pixel)\n"
	   "\t --oh #: Output image height (Default 0 pixel)\n"	   	   
	   "\t --ua #: Angles of horizontal view point (Default 0 deg)\n"
	   "\t --va #: Angles of vertical view point (Default 0 deg)\n"
	   "\t --za #: Angles of image rotation (Default 0 deg)\n"
	   "\t -s #: Scale parameter (Default 1)\n"	   
	   "\t -h\t: Show Usage.\n"
	   "\t -v\t: Show Version.\n"
	   "* ***************************************************************"
	   "********** *\n");
  
  argument_free (arg);
  exit (1);
}

/* バージョン表示 ********************************************************** */
void
version (Argument	*arg) {
  fprintf (stderr, "%s Ver.%s\n", PROGRAM, VERSION);
  argument_free (arg);
  exit (1);
}

/* 引数用構造体の生成 ****************************************************** */
Argument*
argument_new (void) {
  Argument	*arg;

  arg = (Argument *) malloc (sizeof (Argument));

  arg->input_filename  = NULL;
  arg->output_filename = NULL;  
  arg->output_width    = 0;
  arg->output_height   = 0;
  arg->fov_u           = -1;
  arg->fov_v           = -1;
  arg->angle_u         = DEFAULT_UA;
  arg->angle_v         = DEFAULT_VA;
  arg->angle_z	       = DEFAULT_ZA;
  arg->scale	       = DEFAULT_SCALE;
  
  return arg;
}

/* 引数用構造体のメモリ解放 ************************************************ */
void
argument_free (Argument	*arg) {
  free (arg);
}

/* 引数のチェック ********************************************************** */
int
getargs (int		argc,
 	 char		**argv,
	 Argument	**arg) {
  int 	args;

  *arg = argument_new ();
  
  for (args = 1; args < argc; ++args) {
    if ((*argv[args] == '-') && *(argv[args]+1)) {
      if ((strcmp ("h", ++argv[args])) == 0) {
	usage (*arg, argv[0]);
      } else if ((strcmp ("v", argv[args])) == 0) {
	version (*arg);
      } else if ((strcmp ("-image-type", argv[args])) == 0) {
	if (++args >= argc) return 0;
	(*arg)->image_type = atoi(argv[args]);	
      } else if ((strcmp ("-interp-type", argv[args])) == 0) {
	if (++args >= argc) return 0;
	(*arg)->interp_type = atoi(argv[args]);	
      } else if ((strcmp ("-ua", argv[args])) == 0) {
	if (++args >= argc) return 0;
	(*arg)->angle_u = atof(argv[args]);
      } else if ((strcmp ("-va", argv[args])) == 0) {
	if (++args >= argc) return 0;
	(*arg)->angle_v = atof(argv[args]);
      } else if ((strcmp ("-za", argv[args])) == 0) {
	if (++args >= argc) return 0;
	(*arg)->angle_z = atof(argv[args]);
      } else if ((strcmp ("s", argv[args])) == 0) {
	if (++args >= argc) return 0;
	(*arg)->scale = atof(argv[args]);	
      }
    } else {
      if (!((*arg)->input_filename)) {
	(*arg)->input_filename = argv[args];
      } else if (!((*arg)->output_filename)) {
	(*arg)->output_filename = argv[args];
      } else if ((*arg)->fov_u == -1) {
	(*arg)->fov_u = atof(argv[args]);
      } else if ((*arg)->fov_v == -1) {
	(*arg)->fov_v = atof(argv[args]);
      } else {
	return 0;
      }
    }
  }
  if (!((*arg)->input_filename) ||
      !((*arg)->output_filename) ||
      (*arg)->fov_u == -1 ||
      (*arg)->fov_v == -1) return 0;
  
  return 1;
}

/* **************************************************** End of getargs.c *** */

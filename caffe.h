#ifndef CAFFE_H_
#define CAFFE_H_

#ifdef DCNN
void quiet_caffe(int argc, char *argv[]);
#else
#define quiet_caffe(argc, argv) ((void)0)
#endif

#endif /* CAFFE_H_ */

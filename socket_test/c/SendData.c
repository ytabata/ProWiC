#include <stdlib.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cv.h>
#include <highgui.h>
#include <ctype.h>


#include "SendData.h"

#define NLOOP 500
#define FPS 100
#define INTERVAL (1./FPS)

#define IMGNAME "sample.jpg"
IplImage *GetData()
{
  static IplImage *img = NULL;
  
  if( img == NULL ){
    img = cvLoadImage( IMGNAME, CV_LOAD_IMAGE_GRAYSCALE );
    if( img == NULL ){
      fprintf(stderr, "Error: cvLoadImage\n");
      //exit(EXIT_FAILURE);
    }
  }

  return IplImage;

  /* カメラ画像を使う時 */
  /* #define CAP_WIDTH 640 */
  /* #define CAP_HEIGHT 480 */
  /* CvCapture *capture = NULL; */
  /* // キャプチャサイズの設定 */
  /* cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, CAP_WIDTH); */
  /* cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, CAP_HEIGHT); */

  /* capture = cvCreateCameraCapture(0); */
  /* frame = cvQueryFrame(capture); */

}

struct send_result SendData(int sock, struct sockaddr *paddr, size_t len)
{
  struct send_result res;
  IplImage *frame = NULL;
  int i;
  long long int sum = 0;
  int ret;
  struct timeval tvbefore,tvafter;

  gettimeofday(&tvbefore,NULL);

  // データ転送開始
  for(i = 0; i < NLOOP; i++){
    frame = GetData();
#ifdef P_TCP
    ret = send(sock, frame, sizeof(IplImage), 0);
#else
    ret = sendto(sock, frame, sizeof(IplImage), 0, paddr, len);
#endif
    if( ret == -1 ){
      perror("send");
      //exit(EXIT_FAILURE);
    }else{
      sum += ret;
    }
  }

  gettimeofday(&tvafter,NULL);
  
  cvReleaseCapture(&capture);

  res.sum = sum;
  
}


#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/legacy/legacy.hpp>
#include "log.h"

#define FACE_WIDTH 100
#define FACE_HEIGHT 100

/**
 * 固有顔のロジックで顔認識を行うクラス
 */
class EigenFace {
public:
  EigenFace(const char* trainingDataFile);
  int recognize(IplImage* testFace);
private:
  int  findNearestNeighbor(float * projectedTestFace);
  IplImage ** faceImgArr;
  CvMat    *  personNumTruthMat;
  int nTrainFaces;
  int nEigens;
  IplImage * pAvgTrainImg;
  IplImage ** eigenVectArr;
  CvMat * eigenValMat;
  CvMat * projectedTrainFaceMat;
  CvMat * trainPersonNumMat;
};

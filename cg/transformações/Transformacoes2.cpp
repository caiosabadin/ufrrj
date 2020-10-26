#include <iostream>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
 
using namespace Eigen;
using namespace cv;
 
int main(int argc, char* argv[]) {

  if(argc!=7) {
    std::cerr << "ERRO. Chame o programa com os argumentos:" << std::endl;
    std::cerr << argv[0] << " x0 y0 comprimento angulo escala_x0 escala_y0" << std::endl;
    exit(-1);
  }

  int ret_x0 = 0, ret_y0 = 0, comprimento = 0;
  double angulo_radianos = 0.0;
  double escala_x0 = 0.0, escala_y0 = 0.0;

  sscanf(argv[1], "%d", &ret_x0);
  sscanf(argv[2], "%d", &ret_y0);
  sscanf(argv[3], "%d", &comprimento);
  sscanf(argv[4], "%lf", &angulo_radianos);
  sscanf(argv[5], "%lf", &escala_x0);
  sscanf(argv[6], "%lf", &escala_y0);

  angulo_radianos *= 3.1415 / 180;

  Vector3d p1(ret_y0, ret_x0, 1);
  Vector3d p2(ret_y0, ret_x0 + comprimento, 1);
  Vector3d p3(ret_y0 + comprimento, ret_x0, 1);
  Vector3d p4(ret_y0 + comprimento, ret_x0 + comprimento, 1);
  Vector3d d1, d2, d3, d4;

  Mat original = Mat::zeros(tam_img, tam_img, CV_8UC3);

  /* Os dois pontos são os vértices do retângulo, e a escalar são as cores */
  rectangle(original, Point(ret_x0, ret_y0), Point(ret_x0 + comprimento, ret_y0 + comprimento), Scalar(255,255,255), 1);

  /* Imagem transladada */
  Mat transladada = Mat::zeros(tam_img, tam_img, CV_8UC3);

  Matrix3d deslocamento;
  deslocamento << 1, 0, 0, 0, 1, 0, -ret_x0, -ret_y0, 1;

  d1 = p1.transpose() * deslocamento;
  d2 = p2.transpose() * deslocamento;
  d3 = p3.transpose() * deslocamento;
  d4 = p4.transpose() * deslocamento;

  line(transladada, Point(d1[0], d1[1]), Point(d2[0], d2[1]), Scalar(255,255,0), 1);
  line(transladada, Point(d1[0], d1[1]), Point(d3[0], d3[1]), Scalar(255,255,0), 1);
  line(transladada, Point(d2[0], d2[1]), Point(d4[0], d4[1]), Scalar(255,255,0), 1);
  line(transladada, Point(d3[0], d3[1]), Point(d4[0], d4[1]), Scalar(255,255,0), 1);

  /* Imagem girada */
  Mat girada = Mat::zeros(tam_img, tam_img, CV_8UC3);

  Matrix3d matriz_giro;
  matriz_giro << cos(angulo_radianos), sin(angulo_radianos), 0, -sin(angulo_radianos), cos(angulo_radianos), 0, 0, 0, 1;

  d1 = p1.transpose() * matriz_giro;
  d2 = p2.transpose() * matriz_giro;
  d3 = p3.transpose() * matriz_giro;
  d4 = p4.transpose() * matriz_giro;

  line(girada, Point(d1[0], d1[1]), Point(d2[0], d2[1]), Scalar(0,0,255), 1);
  line(girada, Point(d1[0], d1[1]), Point(d3[0], d3[1]), Scalar(0,0,255), 1);
  line(girada, Point(d2[0], d2[1]), Point(d4[0], d4[1]), Scalar(0,0,255), 1);
  line(girada, Point(d3[0], d3[1]), Point(d4[0], d4[1]), Scalar(0,0,255), 1);

  /* Imagem escalonada */
  Mat escalonada = Mat::zeros(tam_img, tam_img, CV_8UC3);

  Matrix3d matriz_escala;
  matriz_escala << escala_x0, 0, 0, 0, escala_y0, 0, 0, 0, 1;

  d1 = p1.transpose() * matriz_escala;
  d2 = p2.transpose() * matriz_escala;
  d3 = p3.transpose() * matriz_escala;
  d4 = p4.transpose() * matriz_escala;

  line(escalonada, Point(d1[0], d1[1]), Point(d2[0], d2[1]), Scalar(200,255,170), 1);
  line(escalonada, Point(d1[0], d1[1]), Point(d3[0], d3[1]), Scalar(200,255,170), 1);
  line(escalonada, Point(d2[0], d2[1]), Point(d4[0], d4[1]), Scalar(200,255,170), 1);
  line(escalonada, Point(d3[0], d3[1]), Point(d4[0], d4[1]), Scalar(200,255,170), 1);

  /* As três transformações aplicadas */
  Mat tudo = Mat::zeros(tam_img, tam_img, CV_8UC3);

  deslocamento << 1, 0, 0, 0, 1, 0, -ret_x0*escala_x0, -ret_y0*escala_y0, 1;

  d1 = p1.transpose() * matriz_escala * deslocamento * matriz_giro;
  d2 = p2.transpose() * matriz_escala * deslocamento * matriz_giro;
  d3 = p3.transpose() * matriz_escala * deslocamento * matriz_giro;
  d4 = p4.transpose() * matriz_escala * deslocamento * matriz_giro;

  line(tudo, Point(d1[0], d1[1]), Point(d2[0], d2[1]), Scalar(255,0,255), 1);
  line(tudo, Point(d1[0], d1[1]), Point(d3[0], d3[1]), Scalar(255,0,255), 1);
  line(tudo, Point(d2[0], d2[1]), Point(d4[0], d4[1]), Scalar(255,0,255), 1);
  line(tudo, Point(d3[0], d3[1]), Point(d4[0], d4[1]), Scalar(255,0,255), 1);


  /* Exibe as imagens geradas */
  namedWindow("Retangulo Original", WINDOW_NORMAL);
  imshow("Retangulo Original", original);

  namedWindow("Transladada", WINDOW_NORMAL);
  imshow("Transladada", transladada);

  namedWindow("Girada", WINDOW_NORMAL);
  imshow("Girada", girada);

  namedWindow("Escalonada", WINDOW_NORMAL);
  imshow("Escalonada", escalonada);

  namedWindow("Todas transformações", WINDOW_NORMAL);
  imshow("Todas transformações", tudo);
  
  waitKey(0);
  return 0;
}
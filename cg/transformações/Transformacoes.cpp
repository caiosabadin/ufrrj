#include <iostream>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
 
using namespace Eigen;
using namespace cv;
 
int main(int argc, char* argv[]) {

  if(argc!=8) {
    std::cerr << "ERRO. Chame o programa com os argumentos:" << std::endl;
    std::cerr << argv[0] << " x0 y0 comprimento angulo escala_x0 escala_y0 imagem.jpg" << std::endl;
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

	Mat imagem = imread(argv[7]);
	if ( imagem.empty() ){
		std::cerr << "Imagem não encontrada." << std::endl;
		exit(-1);
	}

  /* Declaração das imagens operacionadas */
  Mat cortada = Mat::zeros(imagem.rows, imagem.cols, CV_8UC3);
  Mat transladada = Mat::zeros(imagem.rows, imagem.cols, CV_8UC3);
  Mat girada = Mat::zeros(imagem.rows, imagem.cols, CV_8UC3);
  Mat escalonada = Mat::zeros(imagem.rows*escala_x0, imagem.cols*escala_y0, CV_8UC3);
  Mat tudo = Mat::zeros(imagem.rows*escala_x0, imagem.cols*escala_y0, CV_8UC3);

  int x_total = ret_x0 + comprimento;
  int y_total = ret_y0 + comprimento;

  for(int l=ret_x0;l<x_total;l++) {
    for(int c=ret_y0;c<y_total;c++) {
      // Cor do pixel na posição original
      Vec3b p = imagem.at<Vec3b>(l,c);

      // Posição do pixel na imagem original
      Vector3d p1(c, l, 1);

      // Auxiliar para calcular posições
      Vector3d d1;

      // Para mostrar o quadrado recortado da imagem, simplesmente manteremos o mesmo
      // ponto, exceto que ele será colocado numa imagem de fundo todo preto.
      cortada.at<Vec3b>(l,c) = p;

      // Recalcula, ponto a ponto da imagem, onde serão os novos pontos
      // transladados, e plota-os no respectivo Mat.
      Matrix3d deslocamento;
      deslocamento << 1, 0, 0, 0, 1, 0, -ret_x0, -ret_y0, 1;
      d1 = p1.transpose() * deslocamento;

      transladada.at<Vec3b>(d1(1,0), d1(0,0)) = p;

      // Recalcula, ponto a ponto da imagem, onde serão os novos pontos
      // rotacionados, e plota-os no respectivo Mat.
      Matrix3d matriz_giro;
      matriz_giro << cos(angulo_radianos), sin(angulo_radianos), 0, -sin(angulo_radianos), cos(angulo_radianos), 0, 0, 0, 1;
      d1 = p1.transpose() * matriz_giro;

      // Isso faz com que pixels vazios entre os pixels coloridos sejam
      // preenchidos
      girada.at<Vec3b>(d1(1,0), d1(0,0) -1) = p;
      girada.at<Vec3b>(d1(1,0), d1(0,0) +1) = p;
      girada.at<Vec3b>(d1(1,0) -1, d1(0,0)) = p;
      girada.at<Vec3b>(d1(1,0) +1, d1(0,0)) = p;

      // Recalcula, ponto a ponto da imagem, onde serão os novos pontos
      // escalonados, e plota-os no respectivo Mat.
      Matrix3d matriz_escala;
      matriz_escala << escala_x0, 0, 0, 0, escala_y0, 0, 0, 0, 1;
      d1 = p1.transpose() * matriz_escala;

      // Isso faz com que pixels vazios entre os pixels coloridos sejam
      // preenchidos
      for(int i = 0;i<escala_y0;i++)
        for(int j = 0;j<escala_x0;j++)
          escalonada.at<Vec3b>(d1(1,0) + i, d1(0,0) + j) = p;

      // Recalcula, ponto a ponto da imagem, onde serão os novos pontos
      // com todas as transformações, e plota-os no respectivo Mat.
      deslocamento << 1, 0, 0, 0, 1, 0, -ret_x0*escala_x0, -ret_y0*escala_y0, 1;
      d1 = p1.transpose() * matriz_escala * deslocamento * matriz_giro;

      // Isso faz com que pixels vazios entre os pixels coloridos sejam
      // preenchidos

      for(int k = 0;k<=escala_y0;k++)
        for(int j = 0;j<=escala_x0;j++)
          tudo.at<Vec3b>(d1(1,0)+k, d1(0,0) + j) = p;
      
      for(int k = escala_y0;k>=0;k--)
        for(int j = escala_x0;j>=0;j--)
          if((d1(0,0) - j) >= 0 && (d1(1,0) - k) >= 0)
            tudo.at<Vec3b>(d1(1,0)-k, d1(0,0) - j) = p;

      for(int k = escala_x0;k>=0;k--)
        for(int i = escala_y0;i>=0;i--)
          if((d1(1,0) - i) >= 0 && (d1(0,0) - k) >= 0)
            tudo.at<Vec3b>(d1(1,0) - i, d1(0,0) - k ) = p;

      for(int k = 0;k<=escala_x0;k++)
        for(int i = 0;i<=escala_y0;i++)
          tudo.at<Vec3b>(d1(1,0) + i, d1(0,0) + k) = p;
    }
  }

  namedWindow("Recortada", WINDOW_NORMAL);
  imshow("Recortada", cortada);

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
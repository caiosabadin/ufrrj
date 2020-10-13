#include "iostream"
#include "fstream"
#include "type_traits"
#include "cmath"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int max_y(vector<int> vet);
vector<vector<int>> calcular_histograma(Mat imagem_original);
void marcar_linha(Mat grafico, Vec3b cor, int coluna, int linha);
void projetar_histograma(vector<vector<int>> histograma, Mat imagem_original);

int main(void) {

	string nome_arquivo = "a.jpg";
	Mat imagem = imread(nome_arquivo);
	if ( imagem.empty() ){
		cerr << "Imagem " << nome_arquivo << " não encontrada." << endl;
		exit(-1);
	}

    /*
     * A diferença entre o blur e o median é que o median usa uma mediana de tamanho
     * inteiro, e o blur usa uma matriz. Por isso, para um passamos Size(), e, para
     * outro, apenas um inteiro resolve, no caso do terceiro parâmetro da função.
     */

    Mat imagem_blur;
	blur(imagem, imagem_blur, Size(5,5));

    Mat imagem_median;
	medianBlur(imagem, imagem_median, 11);

    projetar_histograma(calcular_histograma(imagem), imagem);
	
    /* Exibie as imagens
	namedWindow(nome_arquivo, WINDOW_NORMAL); 
	imshow(nome_arquivo, imagem );                
	
	namedWindow("Blur", WINDOW_NORMAL); 
	imshow("Blur", imagem_blur );                
	
	namedWindow("Median", WINDOW_NORMAL); 
	imshow("Median", imagem_median ); */                

	waitKey(0);
	return 0;
}

vector<vector<int>> calcular_histograma(Mat imagem_original) {
	
    /* 
     * Inicializa o vetor que receberá o histograma, com três diferentes canais, cada um
     * podendo ir de 0 a 255 cores (256 cores.)
     */
    vector<int> contraste(256, 0);
    vector<vector<int>> resultado(3, contraste);

    /* Percorre a imagem original, pixel a pixel */
	for(int r = 0; r < imagem_original.rows; r++) {
		for(int c = 0; c < imagem_original.cols; c++) {
            /* O vec3b vem como BGR, e não RGB */
			Vec3b p = imagem_original.at<Vec3b>(r,c);

            /* 
             * Se o rgb vier (209, 237, 217), abaixo virá:
             * Azul = 217
             * Verde = 237
             * Vermelho = 209
             * Porque, como falado, o Vec3b é BGR, não RGB.
             */
            int valor_px_azul = (int)p[0];
            int valor_px_verde = (int)p[1];
            int valor_px_vermelho = (int)p[2];

            /*
             * Se veio um azul = 217, vamos guardar no histograma que, para o canal
             * AZUL, valor 217, houve +1 pixel registrado, e assim em diante.
             */
            enum cor{canal_red, canal_green, canal_blue};
            resultado[canal_blue][valor_px_azul]++;
            resultado[canal_green][valor_px_verde]++;
            resultado[canal_red][valor_px_vermelho]++;
		}
    }

	return resultado;
}

void projetar_histograma(vector<vector<int>> histograma, Mat imagem_original) {
    enum cor{canal_red, canal_green, canal_blue};

    int max_x = 256;

    Mat imagem_azul = Mat::zeros( Size(max_x, max_y(histograma[canal_blue])), CV_8UC3);
    namedWindow("Azul", WINDOW_NORMAL);

    Mat imagem_verde = Mat::zeros( Size(max_x, max_y(histograma[canal_green])), CV_8UC3);
    namedWindow("Verde", WINDOW_NORMAL);

    Mat imagem_vermelha = Mat::zeros( Size(max_x, max_y(histograma[canal_red])), CV_8UC3);
    namedWindow("Vermelha", WINDOW_NORMAL);

    for(int i = 0;i < 256; i++) {
        int x_cartesiano = i;
        int y_cartesiano = histograma[canal_blue][i];

        cout << "X: " << x_cartesiano << ", H: " << y_cartesiano << endl;
        marcar_linha(imagem_azul, Vec3b(255, 200, 0), x_cartesiano, y_cartesiano);

        y_cartesiano = histograma[canal_red][i];
        cout << "X: " << x_cartesiano << ", H: " << y_cartesiano << endl;
        marcar_linha(imagem_vermelha, Vec3b(0, 0, 255), x_cartesiano, y_cartesiano);

        y_cartesiano = histograma[canal_green][i];
        cout << "X: " << x_cartesiano << ", H: " << y_cartesiano << endl;
        marcar_linha(imagem_verde, Vec3b(0, 255, 0), x_cartesiano, y_cartesiano);
    }

    /*for(int i = 0; i < 256; i++) {
        int x = i;
        int y = histograma[canal_blue][i];

        imagem_azul.at<Vec3b>(255-x, y) = Vec3b(255, 200, 0);
        namedWindow("Azul", WINDOW_NORMAL); 
        imshow("Azul", imagem_azul);

        waitKey(10000);


        /*y = histograma[canal_green][i];
        imagem_verde.at<Vec3b>(x, y) = Vec3b(0, 255, 0);

        y = histograma[canal_red][i];
        imagem_vermelha.at<Vec3b>(x, y) = Vec3b(0, 0, 255);

    }*/
 
    flip(imagem_azul, imagem_azul, 0);
    imshow("Azul", imagem_azul);
    imwrite("azul.jpg", imagem_azul);

    flip(imagem_verde, imagem_verde, 0);
    imshow("Verde", imagem_verde);
    imwrite("verde.jpg", imagem_verde);

    flip(imagem_vermelha, imagem_vermelha, 0);
    imshow("Vermelha", imagem_vermelha);
    imwrite("vermelha.jpg", imagem_vermelha);

    /* 
    imshow("Verde", imagem_verde);

     
    imshow("Vermelha", imagem_vermelha);

    //Vec3b ponto_azul = Vec3b(255, 0, 0);
    //Vec3b ponto_verde = Vec3b(0, 255, 0);
    //Vec3b ponto_vermelho = Vec3b(0, 0, 255);*/
}

void marcar_linha(Mat grafico, Vec3b cor, int coluna, int linha) {
    for(int i = 0;i<=linha;i++) {
        grafico.at<Vec3b>(i, coluna) = cor;
    }
}

int max_y(vector<int> vet) {
    int m = 0;
    int t = vet.size();
    for(int i = 0;i<t;i++) {
        if(vet[i] > m)
            m = vet[i];
    }
    return m;
}
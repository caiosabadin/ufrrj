#include "iostream"
#include "fstream"
#include "type_traits"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int get_max_y(vector<int> vet);
vector<vector<int>> calcular_histograma(Mat imagem_original);
void marcar_linha(Mat grafico, Vec3b cor, int coluna, int linha);
Mat projetar_cor(vector<vector<int>> histograma, string nome, int canal_cor, Vec3b cor);
void manipula_mouse(int event, int x, int y, int flags, void* userdata);

class Parametros {
    public:
        int cor;
        Mat imagem;
};

int main(void) {

	string nome_arquivo = "a.jpg";
	Mat imagem = imread(nome_arquivo);
	if ( imagem.empty() ){
		cerr << "Imagem " << nome_arquivo << " não encontrada." << endl;
		exit(-1);
	}

    int width = imagem.cols;
    int height = imagem.rows;
    int w = 400;
    int h = height * w / width;
        
    namedWindow("Original", WINDOW_NORMAL);
    resizeWindow("Original", w, h);
    imshow("Original", imagem);

    vector<vector<int>> histograma = calcular_histograma(imagem);

    enum cor{canal_red, canal_green, canal_blue};

    Mat img_azul = projetar_cor(histograma, "azul", canal_blue, Vec3b(255, 200, 0));
    Mat img_verde = projetar_cor(histograma, "verde", canal_green, Vec3b(0, 255, 0));
    Mat img_vermelha = projetar_cor(histograma, "vermelha", canal_red, Vec3b(0, 0, 255));

    Parametros p;
    p.cor = canal_blue;
    p.imagem = img_azul;

    Parametros p2;
    p2.cor = canal_green;
    p2.imagem = img_verde;

    Parametros p3;
    p3.cor = canal_red;
    p3.imagem = img_vermelha;

    Parametros p4;
    p4.cor = 3;
    p4.imagem = imagem;

    setMouseCallback("azul", manipula_mouse, &p);
    setMouseCallback("verde", manipula_mouse, &p2);
    setMouseCallback("vermelha", manipula_mouse, &p3);
    setMouseCallback("Original", manipula_mouse, &p4);

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

void manipula_mouse(int event, int x, int y, int flags, void* params) {

    /*
     * Params são parâmetros extras, passados pelo usuário. No caso, passamos &imagem,
     * que é um ponteiro para nossa imagem. Aí, aqui, instanciamos esse endereço dentro
     * da função manipuladora de mouse, fazendo, um typecast.
     */

    Parametros parametros = *(static_cast<Parametros *>(params));

    string cor = "";
    if (parametros.cor != 3) {
        if(parametros.cor == 2)
            cor = "\033[1;34m";
        else if(parametros.cor == 1)
            cor = "\033[1;32m";
        else
            cor = "\033[1;31m";

        cout << cor << "Ponto: " << "(" << x << ", " << (parametros.imagem.rows - y) << ")" << endl;
    } else {
        cor = "\033[1;37m";
        Vec3b p = parametros.imagem.at<Vec3b>(x,y);
        cout << cor << "Imagem original, pixel RGB: (" << (int)p[2] << ", " << (int)p[1] << ", " << (int)p[0] << ")" << endl;
    }
}

Mat projetar_cor(vector<vector<int>> histograma, string nome, int canal_cor, Vec3b cor) {
    int max_y = get_max_y(histograma[canal_cor]);
    int normalizador_x = ((max_y*1.5)/255);
    int max_x = 255*normalizador_x;

    Mat imagem = Mat::zeros( Size(max_x, max_y), CV_8UC3);
    namedWindow(nome, WINDOW_NORMAL);

    for(int i = 0, j = 0;i < max_x; i+=normalizador_x, j++) {
        int x_cartesiano = i;
        int y_cartesiano = histograma[canal_cor][j];

        for(int k = 0;k<normalizador_x;k++)
            marcar_linha(imagem, cor, x_cartesiano + k, y_cartesiano);
    }

    flip(imagem, imagem, 0);

    int width = imagem.cols;
    int height = imagem.rows;
    int w = 400;
    int h = height * w / width;
    
    resizeWindow(nome, w, h);
    imshow(nome, imagem);
    imwrite(nome + ".jpg", imagem);
    
    return imagem;
}

void marcar_linha(Mat grafico, Vec3b cor, int coluna, int linha) {
    for(int i = 0;i<=linha;i++) {
        grafico.at<Vec3b>(i, coluna) = cor;
    }
}

int get_max_y(vector<int> vet) {
    int m = 0;
    int t = vet.size();
    for(int i = 0;i<t;i++) {
        if(vet[i] > m)
            m = vet[i];
    }
    return m;
}
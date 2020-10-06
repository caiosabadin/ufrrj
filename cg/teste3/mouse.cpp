#include "iostream"
#include "fstream"
#include "iomanip"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void mouseCallback(int event, int x, int y, int flags, void *userdata);

int main(void) {

    string arquivo = "a.png";
    string nomeJanela = "Área de Trabalho";

    Mat imagem = imread(arquivo);
    if(imagem.empty()) {
        cerr << "Imagem " << arquivo << " não encontrada." << endl;
        exit(-1);
    }

    int larguraImagem = imagem.cols;
    int alturaImagem = imagem.rows;
    int larguraJanela = 800;
    int alturaJanela = (alturaImagem*larguraImagem) / larguraJanela;

    namedWindow(nomeJanela, WINDOW_NORMAL);
    resizeWindow(nomeJanela, larguraJanela, alturaJanela);
    setMouseCallback(nomeJanela, mouseCallback, &imagem);
    imshow(nomeJanela, imagem);

    Mat imagemTemporaria = imagem.clone();

    char ch;
    do {
        ch = waitKey(1);
        switch(ch) {
            case 'b':
            case 'B': {
                imagemTemporaria = imagemTemporaria > 128;
                break;
            }
            case 'r':
            case 'R': {
                imagemTemporaria = imagem.clone();
            }
        }
        imshow(nomeJanela, imagemTemporaria);
    } while(ch != 27);

	cout << endl;
	return 0;
}

/**
*** Function:
***
***    mouseCallBack
***
***		Function to handle mouse events
***
***	Parameters
***
***		event			: Show what the mouse is doing
***		x,y			: image position of mouse pointer
***		flags			: To show if <ALT>, <CTRL> or <SHIT> keys were pressed
***		userdata		: User data to pass to function
***
**/

void mouseCallback(int event, int x, int y, int flags, void *userdata) {
string msg = "";
int delta;
Mat tmp = *(static_cast<Mat *>(userdata));

	switch ( event ){
		case EVENT_MOUSEMOVE:
			msg = "Mouse moving";
			break;
		case EVENT_LBUTTONDOWN:
			msg = "Left Down";
			break;
		case EVENT_LBUTTONUP:
			msg = "Left Up";
			break;
		case EVENT_RBUTTONDOWN:
			msg = "Rigth Down";
			break;
		case EVENT_RBUTTONUP:
			msg = "Rigth UP";
			break;
		case EVENT_MBUTTONDOWN:
			msg = "Middle Down";
			break;
		case EVENT_MBUTTONUP:
			msg = "Middlw UP";
			break;
		case EVENT_LBUTTONDBLCLK:
			msg = "Double click Left";
			break;
		case EVENT_RBUTTONDBLCLK:
			msg = "Double click Rigth";
			break;
		case EVENT_MBUTTONDBLCLK:
			msg = "Double click Middle";
			break;
		case EVENT_MOUSEWHEEL:
			msg = "Mouse Wheel (+)";
			break;
		case EVENT_MOUSEHWHEEL:
			msg = "Mouse Wheel (-)";
			break;
	}
	Vec3b v = tmp.at<Vec3b>(y,x);
	cout << msg << ">> [" << 
			setw(3) << hex << event << "][" <<
			setw(3) << hex << flags << "]"<< 
			setw(3) << dec << delta <<
			setw(2) << "(" << setw(4) << x << "," << setw(4) << y << ")" <<
			" RGB(" 
					<< setw(3) << (int)(v[2]) << ", " 
					<< setw(3) << (int)(v[1]) << ", " 
					<< setw(3) << (int)(v[0]) << " )" 
			<< setw(11) << '\r' << flush;	
}
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <bits/stdc++.h>

int main(int argc, char **argv){

    //espaço de cores HSV
    // H (matriz)     |  0 - 179
    // S (saturação)  |  0 - 255
    // V (brilho)     |  0 - 255
    
    //Iniciando a captura em tempo real:
    cv::Mat img;
    cv::VideoCapture cap(0);

    while(true){
        //enquanto for verdadeiro, leia frames
        cap.read(img);

        //fazendo a inversao da imagem 
        cv::flip(img, img, 1);
        //verificando se ha frames, caso nao tenha, encerre
        if(img.empty()){
            std::cout << "camera nao inicializada!" << std::endl;
            break;
        }
        
        //transformando imagem capturada RGB em HSV
        cv::Mat capHSV;
        //entrada original, saida, conversao
        cv::cvtColor(img, capHSV, cv::COLOR_BGR2HSV);
        
        //range HSV para detectar vermelho
        std::vector<int> menorIntensidadeRed = {166, 84, 141};
        std::vector<int> maiorIntensidadeRed = {186, 255, 255};

        //range HSV para detectar azul
        std::vector<int> menorIntensidadeBlue = {97, 100, 117};
        std::vector<int> maiorIntensidadeBlue = {177, 255, 255};

        //range HSV para detectar amarelo
        std::vector<int> menorIntensidadeYellow = {23, 59, 119};
        std::vector<int> maiorIntensidadeYellow = {54, 255, 255};

        //mascara em torno dos objetos que possuem o range de cores predefinidas
        cv::Mat maskRed, maskBlue, maskYellow;

        //Limitando a imagem HSV para obter apenas cores de tons vermelhos
        cv::inRange(
            capHSV,
            menorIntensidadeRed,
            maiorIntensidadeRed,
            maskRed
        );
        //Limitando a imagem HSV para obter apenas cores de tons azuis
        cv::inRange(
            capHSV,
            menorIntensidadeBlue,
            maiorIntensidadeBlue,
            maskBlue
        );
        //Limitando a imagem HSV para obter apenas cores de tons amarelos
        cv::inRange(
            capHSV,
            menorIntensidadeYellow,
            maiorIntensidadeYellow,
            maskYellow
        );
       
        cv::Mat resCaptura;
        //Mascara Bitwise-AND e imagem original
        //A função bitwise_and calcula a conjuncao bit a bit por elemento de duas matrizes ou uma matriz e um escalar.
        cv::bitwise_and(img, img, resCaptura, maskRed=maskRed);
        cv::bitwise_and(img, img, resCaptura, maskBlue=maskBlue);
        cv::bitwise_and(img, img, resCaptura, maskYellow=maskYellow);
       
        //janela de saida tamanho default
        cv::namedWindow("webcam", cv::WINDOW_NORMAL);
        //janela de saida redimensionada
        cv::resizeWindow("webcam", 854, 480);
        //mostrando captura original
        cv::imshow("webcam", img);

        //janela de saida tamanho default
        cv::namedWindow("captura de cores", cv::WINDOW_NORMAL);
        //janela de saida redimensionada
        cv::resizeWindow("captura de cores", 854, 480);
        //mostrando deteccao de cores 
        cv::imshow("captura de cores", capHSV);

        //janela de saida tamanho default
        cv::namedWindow("resultado", cv::WINDOW_NORMAL);
        //janela de saida redimensionada
        cv::resizeWindow("resultado", 854, 480);
        //mostrando o resultado final da captura
        cv::imshow("resultado", resCaptura);

        int key = cv::waitKey(1);
        //caso pressione "q", encerre a captura de video
        if((key == 'q') || (key == 27)){
            break;
        }
    }
    cv::destroyAllWindows();
    return(0);
}
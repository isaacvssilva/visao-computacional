#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <bits/stdc++.h>

int main(int argc, char **argv){

    while(true){
        //carregando diretorio com a imagem que sera pre-processada
        std::string path = "./img/rocket.png";
        cv::Mat rocketRGB;
        rocketRGB = cv::imread(path);

        //pre-processamento: converter RGB em Grayscale
        cv::Mat rocketGray;
        //parametros: (imagem original, imagem resultante, operacao)
        cv::cvtColor(rocketRGB, rocketGray, cv::COLOR_RGB2GRAY);
        
        //visualizando as imagens no seu tamanho original
        cv::imshow("Imagem RGB", rocketRGB);
        cv::imshow("Imagem Grayscale", rocketGray);
        int key = cv::waitKey(1);
        //caso pressione "q" ou "esc", feche o programa
        if((key == 'q') || (key == 27)){
            break;
        }
    }
    return(0);
}
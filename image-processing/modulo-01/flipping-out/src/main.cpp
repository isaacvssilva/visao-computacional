#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <bits/stdc++.h>

int main(int argc, char **argv){

    while(true){
        //carregando diretorio com a imagem que sera pre-processada
        std::string path = "./img/flipped_seville.jpg";
        cv::Mat flipped_seville;
        flipped_seville = cv::imread(path);

        //rotacionando a imagem
        cv::Mat serville_rotated;
        //parametros: (imagem original, imagem resultante, operacao)
        cv::flip(flipped_seville, serville_rotated, 0);

        //visualizando as imagens no seu tamanho original
        cv::imshow("Imagem original", flipped_seville);
        cv::imshow("Imagem rotacionada", serville_rotated);
        int key = cv::waitKey(1);
        //caso pressione "q" ou "esc", feche o programa
        if((key == 'q') || (key == 27)){
            break;
        }
    }
    return(0);
}
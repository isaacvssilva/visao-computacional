#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <bits/stdc++.h>

int main(int argc, char **argv){

    while(true){
        //carregando diretorio com a imagem que sera pre-processada
        std::string path = "./img/red-channel.jpg";
        cv::Mat imgIn;
        imgIn = cv::imread(path);

        //pre-processamento
        
        //criando um vetor que ira conter os 3 planos da imagem (RGB)
        std::vector<cv::Mat> planosImg;
        //dividindo os planos. Parametros: (imagem original, imagem resultante)
        cv::split(imgIn, planosImg);

        //Inicializando os parametros do histograma para cada plano, se necessario
        cv::Mat R_hist, G_hist, B_hist;
        int histSize = 256;
        float rangeColor[] = {0, 256};
        const float* histRange[] = {rangeColor};

        /*calculando o histograma. 
            1º da função calcHist no planosImg[0] que é O(s) array(s) de origem, 
            2º argumento é o número de imagens 
            3º argumento é o número do canal da imagem que é 0 aqui, pois estamos apenas passando um canal único
            4º argumento é uma máscara a ser usada no array de origem (zeros indicando pixels a serem ignorados).
            5º argumento é o histograma de saída, no caso para a cor vermelha 
            6º argumento são dimensões do histograma que é 1 aqui.
            7º argumento é o número de compartimentos
            8º argumento é o intervalo do histograma
        */
       //para a cor vermelha é passado 2 no canal, que seria a 3ª posicao vetorial {B,G,R}
        cv::calcHist( &planosImg[2], 1, 0, cv::Mat(), R_hist, 1, &histSize, histRange, true, false);
      
        //criando imagem para exibir o histograma
        int hist_width = 256*2, hist_height = 256*2;
        cv::Mat imgHist(hist_width, hist_height, CV_8UC3, cv::Scalar(255, 255, 255));
        int bin_w = 2;

        //normalizando o histograma, para garantir que o mesmo se encaixe no grafico no intervalo indicado pelos parametros.
        //nesse caso, apenas para o canal RED
        cv::normalize(R_hist, R_hist, 0, imgHist.rows, cv::NORM_MINMAX, -1, cv::Mat());

        for(int i = 1; i < histSize; i++){
            //cor vermelha
            cv::line(
                imgHist, 
                cv::Point(bin_w * (i-1), hist_height - cvRound(R_hist.at<float>(i-1))), 
                cv::Point(bin_w * (i), hist_height - cvRound(R_hist.at<float>(i))),
                cv::Scalar(0, 0, 255), 2, 8, 0
            );
        }

        cv::imshow("Imagem original", imgIn);
        cv::imshow("Histograma - RED", imgHist);
        int key = cv::waitKey(1);
        //caso pressione "q" ou "esc", feche o programa
        if((key == 'q') || (key == 27)){
            break;
        }
    }
    return(0);
}
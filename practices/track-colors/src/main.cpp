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
        std::vector<int> menorIntensidadeRed = {161, 155, 84};
        std::vector<int> maiorIntensidadeRed = {179, 255, 255};

        //range HSV para detectar azul
        std::vector<int> menorIntensidadeBlue = {97, 100, 117};
        std::vector<int> maiorIntensidadeBlue = {117, 255, 255};

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

        //detectar contorno da cor identificada
        //vetor bidimensional para armazenar informacoes das bordas de cada cor (eixos X e Y)
        std::vector<std::vector<cv::Point>> contornoRed;
        std::vector<std::vector<cv::Point>> contornoBlue;
        std::vector<std::vector<cv::Point>> contornoYellow;

        std::vector<cv::Vec4i> hierarquiaRed;
        std::vector<cv::Vec4i> hierarquiaBlue;
        std::vector<cv::Vec4i> hierarquiaYellow;
        
        //passando dados de cada cor captada para os vetores contornos e hierarquia
        cv::findContours(maskRed.clone(), contornoRed, hierarquiaRed, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        cv::findContours(maskBlue.clone(), contornoBlue, hierarquiaBlue, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        cv::findContours(maskYellow.clone(), contornoYellow, hierarquiaYellow, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        std::vector<std::vector<cv::Point>> ladoRed;
        std::vector<std::vector<cv::Point>> ladoBlue;
        std::vector<std::vector<cv::Point>> ladoYellow;

        ladoRed = contornoRed;
        ladoBlue = contornoBlue;
        ladoYellow = contornoYellow;

        float perimetroRed, perimetroBlue, perimetroYellow;

        for(unsigned int i = 0; i < contornoRed.size(); i++){
        
            int areaRed = cv::contourArea(contornoRed[i]);
            perimetroRed = cv::arcLength(contornoRed[i], true);

            //transformando as linhas em um poligono com ajustes de precisao do comprimento
            cv::approxPolyDP(contornoRed[i], ladoRed[i], 0.03 * perimetroRed, true);
             //desenhando contorno(vermelho) em todos os tons em vermelho detectados na imagem da webcam 
            cv::drawContours(img, ladoRed, i, cv::Scalar(0, 0, 255));

            //desenhando retangulo sobre a cor encontrada (vermelho)
            std::vector<cv::Rect> retanguloRed;

            retanguloRed.resize(contornoRed.size());
            retanguloRed[i] = cv::boundingRect(ladoRed[i]);
            cv::rectangle(img, retanguloRed[i].tl(), retanguloRed[i].br(), cv::Scalar(0, 0, 255), 2);

            //exibir nome da cor identificada
            // if(ladoRed[i].size()){
            //     cv::putText(img, "Vermelho", cv::Point(retanguloRed[i].x, retanguloRed[i].y),cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255), 2);
            // }
        }

        for(unsigned int i = 0; i < contornoBlue.size(); i++){

            int areaBlue = cv::contourArea(contornoBlue[i]);
            perimetroBlue = cv::arcLength(contornoBlue[i], true);

            //transformando as linhas em um poligono com ajustes de precisao do comprimento
            cv::approxPolyDP(contornoBlue[i], ladoBlue[i], 0.03 * perimetroBlue, true);
             //desenhando contorno(azuamarelol) em todos os tons em azul detectados na imagem da webcam 
            cv::drawContours(img, ladoBlue, i, cv::Scalar(255, 0, 0));

            //desenhando retangulo sobre a cor encontrada (azul)
            std::vector<cv::Rect> retanguloBlue;

            retanguloBlue.resize(contornoBlue.size());
            retanguloBlue[i] = cv::boundingRect(ladoBlue[i]);
            cv::rectangle(img, retanguloBlue[i].tl(), retanguloBlue[i].br(), cv::Scalar(255, 0, 0), 2);

            // //exibir nome da cor identificada
            // if(ladoBlue[i].size()){
            //     cv::putText(img, "Azul", cv::Point(retanguloBlue[i].x, retanguloBlue[i].y),cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 0, 0), 2);
            // }
        }

        for(unsigned int i = 0; i < contornoYellow.size(); i++){

            int areaYellow = cv::contourArea(contornoYellow[i]);
            perimetroYellow = cv::arcLength(contornoYellow[i], true);

            //transformando as linhas em um poligono com ajustes de precisao do comprimento
            cv::approxPolyDP(contornoYellow[i], ladoYellow[i], 0.03 * perimetroYellow, true);
            //desenhando contorno(amarelo) em todos os tons em amarelo detectados na imagem da webcam 
            cv::drawContours(img, ladoYellow, i, cv::Scalar(0, 255, 217));

            //desenhando retangulo sobre a cor encontrada (amarelo)
            std::vector<cv::Rect> retanguloYellow;
            
            retanguloYellow.resize(contornoYellow.size());
            retanguloYellow[i] = cv::boundingRect(ladoYellow[i]);
            cv::rectangle(img, retanguloYellow[i].tl(), retanguloYellow[i].br(), cv::Scalar(0, 255, 217), 2);

            //exibir nome da cor identificada
            // if(ladoYellow[i].size()){
            //     cv::putText(img, "Amarelo", cv::Point(retanguloYellow[i].x, retanguloYellow[i].y),cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 217), 2);
            // }
        }

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

        // //janela de saida tamanho default
        // cv::namedWindow("captura de cores", cv::WINDOW_NORMAL);
        // //janela de saida redimensionada
        // cv::resizeWindow("captura de cores", 854, 480);
        // //mostrando deteccao de cores 
        // cv::imshow("captura de cores", capHSV);

        // //janela de saida tamanho default
        // cv::namedWindow("resultado", cv::WINDOW_NORMAL);
        // //janela de saida redimensionada
        // cv::resizeWindow("resultado", 854, 480);
        // //mostrando o resultado final da captura
        // cv::imshow("resultado", resCaptura);

        int key = cv::waitKey(1);
        //caso pressione "q", encerre a captura de video
        if((key == 'q') || (key == 27)){
            break;
        }
    }
    cv::destroyAllWindows();
    return(0);
}
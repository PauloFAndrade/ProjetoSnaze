#ifndef _GMANAGER_H_
#define _GMANAGER_H_

#include <vector>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h> //srand()
#include <time.h> //rand()
#include <thread>

#include "Maze.h" 
#include "Coordinate.h"
#include "Ia.h"


class GameManager{
    public:

        /**
         * @brief Mensagem de boas vindas e resumo dos dados coletados
         * 
         */
        void welcomeToParadise(){
            std::cout << "   SSSSSSSSSSSSSSS NNNNNNNN        NNNNNNNN               AAA               ZZZZZZZZZZZZZZZZZZZEEEEEEEEEEEEEEEEEEEEEE\n";
            std::cout << " SS:::::::::::::::SN:::::::N       N::::::N              A:::A              Z:::::::::::::::::ZE::::::::::::::::::::E\n";
            std::cout << "S:::::SSSSSS::::::SN::::::::N      N::::::N             A:::::A             Z:::::::::::::::::ZE::::::::::::::::::::E\n";
            std::cout << "S:::::S     SSSSSSSN:::::::::N     N::::::N            A:::::::A            Z:::ZZZZZZZZ:::::Z EE::::::EEEEEEEEE::::E\n";
            std::cout << "S:::::S            N::::::::::N    N::::::N           A:::::::::A           ZZZZZ     Z:::::Z    E:::::E       EEEEEE\n";
            std::cout << "S:::::S            N:::::::::::N   N::::::N          A:::::A:::::A                  Z:::::Z      E:::::E\n";
            std::cout << " S::::SSSS         N:::::::N::::N  N::::::N         A:::::A A:::::A                Z:::::Z       E::::::EEEEEEEEEE\n";
            std::cout << "  SS::::::SSSSS    N::::::N N::::N N::::::N        A:::::A   A:::::A              Z:::::Z        E:::::::::::::::E\n";
            std::cout << "    SSS::::::::SS  N::::::N  N::::N:::::::N       A:::::A     A:::::A            Z:::::Z         E:::::::::::::::E\n";
            std::cout << "       SSSSSS::::S N::::::N   N:::::::::::N      A:::::AAAAAAAAA:::::A          Z:::::Z          E::::::EEEEEEEEEE\n";
            std::cout << "            S:::::SN::::::N    N::::::::::N     A:::::::::::::::::::::A        Z:::::Z           E:::::E\n";
            std::cout << "            S:::::SN::::::N     N:::::::::N    A:::::AAAAAAAAAAAAA:::::A    ZZZ:::::Z     ZZZZZ  E:::::E       EEEEEE\n";
            std::cout << "SSSSSSS     S:::::SN::::::N      N::::::::N   A:::::A             A:::::A   Z::::::ZZZZZZZZ:::ZEE::::::EEEEEEEE:::::E\n";
            std::cout << "S::::::SSSSSS:::::SN::::::N       N:::::::N  A:::::A               A:::::A  Z:::::::::::::::::ZE::::::::::::::::::::E\n";
            std::cout << "S:::::::::::::::SS N::::::N        N::::::N A:::::A                 A:::::A Z:::::::::::::::::ZE::::::::::::::::::::E\n";
            std::cout << " SSSSSSSSSSSSSSS   NNNNNNNN         NNNNNNNAAAAAAA                   AAAAAAAZZZZZZZZZZZZZZZZZZZEEEEEEEEEEEEEEEEEEEEEE\n\n\n";
            std::cout << "\n\n";
            std::cout << "\t\t╔═════════════════════════════════════════════════════════════════════════════════════╗\n";
            std::cout << "\t\t                  Levels Loaded → "<<levels<< "  | Snake Lives → " <<lifes<<"  | Apples to eat → " << food << "\n";
            std::cout << "\t\t                     Clear all levels to win the game. Good Luck!!!\n";
            std::cout << "\t\t╚═════════════════════════════════════════════════════════════════════════════════════╝\n\n";
            std::cout << "\n\n𓆩*𓆪 Press <ENTER> to start the game 𓆩*𓆪\n";
            if(std::cin.get() == '\n'){};
        }

        /**
        * @brief Função Utilizada Como Cabeçalho de Alguns dos Erros Que Podem Ser Detectados
        * 
        */
        void printError(){
            std::cout << "╔═══════════════╗\n";
            std::cout << "      ERROR\n";
            std::cout << "╚═══════════════╝\n";
        }

        /**
         * @brief Voltar ao ponto inicial após colisão
         * 
         */
        void backInit(){
            std::cout << "𓆩*𓆪 Oh no! Anaconda crashed! \n";
            std::cout << "𓆩*𓆪 Press <ENTER> to try again.\n";
            std::cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n";
            std::cout << "Lives → ";
            for(int i{0};i<lifes;i++){
                std::cout << "❤️  ";
            }
            std::cout << "  | Food Eaten → " << eatenFood << " of " << food <<std::endl;
            std::cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n";
            if(std::cin.get() == '\n'){
                Planets[currentLevel].human.head.first =  Planets[currentLevel].human.posInit.first;
                Planets[currentLevel].human.head.second = Planets[currentLevel].human.posInit.second;
                Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first] = "గ"; 
                Planets[currentLevel].human.body.clear();
            }
        }

        /**
         * @brief Fim do jogo
         * 
         */
        void apocalipse(){
            std::cout << "              ┌───────── •✧✧• ──────────────────┐\n";
            std::cout << "                      SORRY! anaconda LOST!       \n";
            std::cout << "                       Thanks for playing!        \n";
            std::cout << "              └───────── •✧✧• ──────────────────┘\n";
            exit(0);
        }

        /**
         * @brief Tela de ajuda caso passe somente ./snaze na linha de comando
         * 
         */
        void Help(){
            std::cout << "╔══════════════════════════════════════════════════════════╗\n";
            std::cout << "                         Help Box\n";
            std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";
            std::cout << "╭─━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━─╮\n";
            std::cout << "|% ./snaze                                                  |\n";
            std::cout << "|Usage: snaze [<options>] <input_data_file>                 |\n"; 
            std::cout << "|  snaze options:                                           |\n"; 
            std::cout << "|     --food <num> Number of foods a snake should eat       |\n";        
            std::cout << "|                                                           |\n";
            std::cout << "|     --fps <num> Animation speed in fps (frames per second)|\n";
            std::cout << "|                                                           |\n";
            std::cout << "|     --lifes <num> Number of snake lives                   |\n";
            std::cout << "╰─━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━─╯\n";
        }   

        /**
         * @brief Verifica se um espaço do labirinto é uma fruta
         * 
         * @param check espaço do labirinto
         * @return true se for uma fruta
         * @return false se não for uma furta
         */
        bool isFruit(std::string check){
            if(check == "❉"){
                return true;
            }
            return false;
        }

        /**
         * @brief Avança para o próximo nível
         * 
         */
        void nextLevel(){
            std::cout << "\n\n𓆩*𓆪 Completed Level " << currentLevel+1 << " ( of " << levels <<") successfully\n";
            std::cout << "𓆩*𓆪 Press <ENTER> to start next level!\n";
            std::cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n";
            std::cout << "Lives → ";
            for(int i{0};i<lifes;i++){
                std::cout << "❤️  ";
            }
            std::cout << "  | Food Eaten → " << eatenFood << " of " << food <<std::endl;
            std::cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n";
            Planets[currentLevel].world[fruit.coord.second][fruit.coord.first] = "గ";
            Planets[currentLevel].printWorld(Planets[currentLevel].world.size()-1);
            if(currentLevel+1 == levels){
                std::cout << "              ┌───────── •✧✧• ──────────────────┐\n";
                std::cout << "                  CONGRATULATIONS anaconda WON!   \n";
                std::cout << "                       Thanks for playing!        \n";
                std::cout << "              └───────── •✧✧• ──────────────────┘\n";
                exit(0);
            }else if(std::cin.get() == '\n'){
                currentLevel++;
            }
            for(size_t i{0};i<Planets[currentLevel].human.body.size();i++){
                Planets[currentLevel].human.body.pop_back();
            }
            eatenFood = 0;
        }

        /**
         * @brief Aumenta o tamanho do corpo da cobra
         * 
         */
        void increaseBody(){
            std::pair<int, int>temp;
            Planets[currentLevel].human.body.push_back(temp);
            temp.first = 0;
            temp.second = 0;
        }

        /**
         * @brief Atualiza a posição da cobra no labirinto
         * 
         */
        void updatePosition(){
            if(!Planets[currentLevel].human.body.empty()){
                std::pair<int,int>prev;
                prev.first = Planets[currentLevel].human.body[0].first;
                prev.second = Planets[currentLevel].human.body[0].second;
                std::pair<int,int>aux;
                Planets[currentLevel].human.body[0].first = Planets[currentLevel].human.head.first;
                Planets[currentLevel].human.body[0].second = Planets[currentLevel].human.head.second;
                for(size_t i{1};i<Planets[currentLevel].human.body.size();i++){
                    aux.first = Planets[currentLevel].human.body[i].first;
                    aux.second = Planets[currentLevel].human.body[i].second;
                    Planets[currentLevel].human.body[i].first = prev.first;
                    Planets[currentLevel].human.body[i].second = prev.second;
                    prev.first = aux.first;
                    prev.second = aux.second;
                }
            }

            switch(Planets[currentLevel].human.dir){
                case INITIAL:
                    break;
                case LEFT:
                    Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first] = " ";
                    if(Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first-1])){
                        while(!ia.caminho.empty()){
                            ia.caminho.pop();
                        }
                        if(lifes == 1){
                            lifes = 0;
                            apocalipse();
                        }else{
                            lifes--;
                            backInit();
                        }
                    }else if(isFruit(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first-1])){
                        eatenFood++;
                        if(eatenFood == food){
                            nextLevel();
                        }else{
                            clearApple();
                            Planets[currentLevel].world[Planets[currentLevel].human.head.second][--Planets[currentLevel].human.head.first] = "గ";
                            increaseBody();
                        }
                    }else if(Planets[currentLevel].isBody()){
                        if(lifes == 1){
                            lifes = 0;
                            apocalipse();
                        }else{
                            lifes--;
                            backInit();
                        }
                    }else{
                        Planets[currentLevel].world[Planets[currentLevel].human.head.second][--Planets[currentLevel].human.head.first] = "గ";
                    }
                    break;
                case UP:
                    Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first] = " ";
                    if(Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second-1][Planets[currentLevel].human.head.first])){
                        while(!ia.caminho.empty()){
                            ia.caminho.pop();
                        }
                        if(lifes == 1){
                            lifes = 0;
                            apocalipse();
                        }else{
                            lifes--;
                            backInit();
                        }
                    }else if(isFruit(Planets[currentLevel].world[Planets[currentLevel].human.head.second-1][Planets[currentLevel].human.head.first])){
                        eatenFood++;
                        if(eatenFood == food){
                            nextLevel();
                        }else{
                            clearApple();
                            Planets[currentLevel].world[--Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first] = "గ";
                            increaseBody();
                        }
                        
                    }else if(Planets[currentLevel].isBody()){
                        if(lifes == 1){
                            lifes = 0;
                            apocalipse();
                        }else{
                            lifes--;
                            backInit();
                        }
                    }else{
                        Planets[currentLevel].world[--Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first] = "గ";
                    }
                    
                    break;
                case DOWN:
                    Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first] = " ";
                    if(Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second+1][Planets[currentLevel].human.head.first])){
                        while(!ia.caminho.empty()){
                            ia.caminho.pop();
                        }
                        if(lifes == 1){
                            lifes = 0;
                            apocalipse();
                        }else{
                            lifes--;
                            backInit();
                        }
                    }else if(isFruit(Planets[currentLevel].world[Planets[currentLevel].human.head.second+1][Planets[currentLevel].human.head.first])){
                        eatenFood++;
                        if(eatenFood == food){
                            nextLevel();
                        }else{
                            clearApple();
                            Planets[currentLevel].world[++Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first] = "గ";
                            increaseBody();
                        }
                    }else if(Planets[currentLevel].isBody()){
                        if(lifes == 1){
                            lifes = 0;
                            apocalipse();
                        }else{
                            lifes--;
                            backInit();
                        }
                    }else{
                        Planets[currentLevel].world[++Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first] = "గ";
                    }
                    break;
                case RIGHT:
                    Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first] = " ";
                    if(Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first+1])){
                        while(!ia.caminho.empty()){
                            ia.caminho.pop();
                        }
                        if(lifes == 1){
                            lifes = 0;
                            apocalipse();
                        }else{
                            lifes--;
                            backInit();
                        }
                    }else if(isFruit(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first+1])){
                        eatenFood++;
                        if(eatenFood == food){
                            nextLevel();
                        }else{
                            clearApple();
                            Planets[currentLevel].world[Planets[currentLevel].human.head.second][++Planets[currentLevel].human.head.first] = "గ";
                            increaseBody();
                        }
                    }else if(Planets[currentLevel].isBody()){
                        if(lifes == 1){
                            lifes = 0;
                            apocalipse();
                        }else{
                            lifes--;
                            backInit();
                        }
                    }else{
                        Planets[currentLevel].world[Planets[currentLevel].human.head.second][++Planets[currentLevel].human.head.first] = "గ";
                    }
                    break;
            }
        }

        /**
         * @brief Função apenas de teste onde utilizava teclado (ler a entrada do teclado e muda a direção da cobra)
         * 
         */
        void checkInput(){
            char position;
            std::cin >> position;
            if(position == 'a'){
                if(Planets[currentLevel].human.dir != RIGHT || Planets[currentLevel].human.body.empty()){
                    Planets[currentLevel].human.dir = LEFT;
                }
            }else if(position == 'w'){
                if(Planets[currentLevel].human.dir != DOWN || Planets[currentLevel].human.body.empty()){
                    Planets[currentLevel].human.dir = UP;
                }
            }else if(position == 's'){
                if(Planets[currentLevel].human.dir != UP || Planets[currentLevel].human.body.empty()){
                    Planets[currentLevel].human.dir = DOWN;
                }
            }else if(position == 'd'){
                if(Planets[currentLevel].human.dir != LEFT || Planets[currentLevel].human.body.empty()){
                    Planets[currentLevel].human.dir = RIGHT;
                }
            }
        }
        
        /**
         * @brief Limpa o espaço da comida para gerar outra posteriormente
         * 
         */
        void clearApple(){
            Planets[currentLevel].world[fruit.coord.second][fruit.coord.first] = " ";
            fruit.coord.first = 0;
            fruit.coord.second = 0;
        }

        bool checkApple(){
            if(Planets[currentLevel].world[fruit.coord.second][fruit.coord.first] == "▄" || Planets[currentLevel].world[fruit.coord.second][fruit.coord.first] == "." || Planets[currentLevel].world[fruit.coord.second][fruit.coord.first] == "గ"){
                return false;
            }
            return true;
        }

        /**
         * @brief Cria uma maça
         * 
         */
        void makeApple(){
            srand(time(NULL));
            while(!checkApple()){
                fruit.coord.first = rand()%Planets[currentLevel].cols;
                fruit.coord.second = rand()%Planets[currentLevel].rows;
            }
            Planets[currentLevel].world[fruit.coord.second][fruit.coord.first] = "❉";
        }

        /**
         * @brief Leitura dos dados iniciais do jogo
         * 
         * @param qtd 
         * @param argv 
         * @return true 
         * @return false 
         */
        bool prepareBigBang(int qtd, const char** argv){
            if(qtd == 1){
                std::cout << "You Forgot The God's Book, cof cof, Input File*\n";
                Help();
                return false;
            }
            std::string aux (argv[1]);
            if(qtd == 2 && aux.find(".dat") != std::string::npos){
                std::cout << "𓆩*𓆪 You didn't choose the parameters (--fps), (--food), (--lifes) so we will use the default (5), (10) and (5) respectively.\n";
                nameFile = aux;
            }else{
                for(int i{0};i<qtd;i++){
                    std::string analyze(argv[i]);
                    if(strcmp(argv[i],"--fps")==0){
                        try{
                            fps = std::stoi(argv[i+1]);
                            i++;
                        }catch(const std::invalid_argument & e){
                            system("clear");
                            printError();
                            std::cout << "𓆩*𓆪 We Were Unable To Continue The Game Because \"";
                            std::cout << argv[i+1] << "\" Is Not A Number\n";
                            exit(0);
                        }
                    }else if(strcmp(argv[i],"--food")==0){
                        try{
                            food = std::stoi(argv[i+1]);
                            i++;
                        }catch(const std::invalid_argument & e){
                            system("clear");
                            printError();
                            std::cout << "𓆩*𓆪 We Were Unable To Continue The Game Because \"";
                            std::cout << argv[i+1] << "\" Is Not A Number\n";
                            exit(0);
                        }
                    }else if(strcmp(argv[i],"--lifes")==0){
                        try{
                            lifes = std::stoi(argv[i+1]);
                            i++;
                        }catch(const std::invalid_argument & e){
                            system("clear");
                            printError();
                            std::cout << "𓆩*𓆪 We Were Unable To Continue The Game Because \"";
                            std::cout << argv[i+1] << "\" Is Not A Number\n";
                            exit(0);
                        }
                    }else if(analyze.find(".dat") != std::string::npos/*i==qtd-1*/){
                        nameFile = argv[i];
                    }else if(analyze.find("/snaze") == std::string::npos ){
                        system("clear");
                        printError();
                        std::cout << "𓆩*𓆪 You Passed A Non-Existent Parameter -> \""<<argv[i]<<"\"\n";
                        exit(0);
                    }
                }
            }

            preparePlanets();
            return true;
        }

        /**
         * @brief Inicia o jogo
         * 
         */
        void BigBang(){
            while(playing){
                makeApple();
                ia.setTarget(fruit);
                ia.setStart(Planets[currentLevel].human.head);
                Planets[currentLevel].printWorld(Planets[currentLevel].world.size()-1);
                ia.startGrid(Planets[currentLevel]);
                
                bool reset = false;
                while(!ia.caminho.empty()){
                    reset = false;
                    if(ia.caminho.top().linha == Planets[currentLevel].human.head.second && ia.caminho.top().coluna == Planets[currentLevel].human.head.first+1){//direita
                        if(Planets[currentLevel].human.dir == LEFT && Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first-1])){
                            if(!Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second+1][Planets[currentLevel].human.head.first])){
                                Planets[currentLevel].human.dir = DOWN;
                                while(!ia.caminho.empty()){
                                    ia.caminho.pop();
                                }
                                reset=true;
                            }else if(!Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second-1][Planets[currentLevel].human.head.first])){
                                Planets[currentLevel].human.dir = UP;
                                while(!ia.caminho.empty()){
                                    ia.caminho.pop();
                                }
                                reset=true;
                            }
                        }else if(Planets[currentLevel].human.dir != LEFT || Planets[currentLevel].human.body.empty()){
                            Planets[currentLevel].human.dir = RIGHT;
                        }
                    }else if(ia.caminho.top().linha == Planets[currentLevel].human.head.second && ia.caminho.top().coluna == Planets[currentLevel].human.head.first - 1){//esquerda
                        if(Planets[currentLevel].human.dir == RIGHT && Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first+1])){
                            if(!Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second+1][Planets[currentLevel].human.head.first])){
                                Planets[currentLevel].human.dir = DOWN;
                                while(!ia.caminho.empty()){
                                    ia.caminho.pop();
                                }
                                reset=true;
                            }else if(!Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second-1][Planets[currentLevel].human.head.first])){
                                Planets[currentLevel].human.dir = UP;
                                while(!ia.caminho.empty()){
                                    ia.caminho.pop();
                                }
                                reset=true;
                            }
                        }else if(Planets[currentLevel].human.dir != RIGHT || Planets[currentLevel].human.body.empty()){
                            Planets[currentLevel].human.dir = LEFT;
                        }
                    }else if(ia.caminho.top().linha == Planets[currentLevel].human.head.second-1 && ia.caminho.top().coluna == Planets[currentLevel].human.head.first){//cima
                        if(Planets[currentLevel].human.dir == DOWN && Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second+1][Planets[currentLevel].human.head.first])){
                            if(!Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first+1])){
                                Planets[currentLevel].human.dir = RIGHT;
                                while(!ia.caminho.empty()){
                                    ia.caminho.pop();
                                }
                                reset=true;
                            }else if(!Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first-1])){
                                Planets[currentLevel].human.dir = LEFT;
                                while(!ia.caminho.empty()){
                                    ia.caminho.pop();
                                }
                                reset=true;
                            }
                        }else if(Planets[currentLevel].human.dir != DOWN || Planets[currentLevel].human.body.empty()){
                            Planets[currentLevel].human.dir = UP;
                        }
                    }else if(ia.caminho.top().linha == Planets[currentLevel].human.head.second+1 && ia.caminho.top().coluna == Planets[currentLevel].human.head.first){//baixo
                        if(Planets[currentLevel].human.dir == UP && Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second-1][Planets[currentLevel].human.head.first])){
                            if(!Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first+1])){
                                Planets[currentLevel].human.dir = RIGHT;
                                while(!ia.caminho.empty()){
                                    ia.caminho.pop();
                                }
                                reset=true;
                            }else if(!Planets[currentLevel].isWall(Planets[currentLevel].world[Planets[currentLevel].human.head.second][Planets[currentLevel].human.head.first-1])){
                                Planets[currentLevel].human.dir = LEFT;
                                while(!ia.caminho.empty()){
                                    ia.caminho.pop();
                                }
                                reset=true;
                            }
                        }else if(Planets[currentLevel].human.dir != UP || Planets[currentLevel].human.body.empty()){
                            Planets[currentLevel].human.dir = DOWN;
                        }
                    }
                    if(reset==true){
                        std::cout << std::endl;
                        updatePosition();
                        Planets[currentLevel].printWorld(Planets[currentLevel].world.size()-1);
                        ia.setTarget(fruit);
                        ia.setStart(Planets[currentLevel].human.head);
                        ia.drawGrid(ia.grid);
                    }else{
                        ia.caminho.pop();
                        updatePosition();
                    }
                    std::cout << "\n\n▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n";
                    std::cout << "Lives → ";
                    for(int i{0};i<lifes;i++){
                        std::cout << "❤️  ";
                    }
                    std::cout << "  | Food Eaten → " << eatenFood << " of " << food <<std::endl;
                    std::cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n";
                    Planets[currentLevel].printWorld(Planets[currentLevel].world.size()-1);
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000/fps));
                }
                ia.grid.clear();
                ia.node.clear();
            }
        }   
        
        void engGame();
    
    private:
        void preparePlanets(){
            std::ifstream initialFile;
            std::string iline;
            std::string intermediate;  

            initialFile.open(nameFile);
            if(initialFile.is_open()){
                while(getline(initialFile,iline)){
                    std::stringstream check1(iline);
                    try{
                        Maze littlePlanet;
                        getline(check1, intermediate, ' ');
                        littlePlanet.rows = std::stoi(intermediate);
                        getline(check1, intermediate, ' ');
                        littlePlanet.cols = std::stoi(intermediate);
                        Planets.push_back(littlePlanet);
                        for(int i{0};i<Planets[levels].rows;i++){
                            getline(initialFile,iline);
                            Planets[levels].makeWorld(iline);
                        }
                        Planets[levels].makeWorldBetter();
                        levels++;
                    }
                    catch(const std::exception& e)
                    {   
                        std::cerr << e.what() << '\n';
                    }
                }
            }else{
                printError();
                std::cout << "Não Foi Possível Abrir o Arquivo\n";
                exit(0);
            }
            initialFile.close();
        }
        
        
        Coordinate fruit;
        
        int fps=5;
        int lifes=5;
        int food=10;
        int eatenFood = 0;

        std::vector<Maze> Planets; 

        int currentLevel=0;
        int levels=0;

        std::string nameFile;

        bool playing = true;

        IA ia;
};

#endif
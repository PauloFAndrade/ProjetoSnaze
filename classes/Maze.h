#ifndef _MAZE_H_
#define _MAZE_H_

#include "Snake.h"

class Maze{
    public:

        /**
         * @brief Função para checar se uma coordenada do labirinto é um corpo
         * 
         * @return true se for um corpo
         * @return false se não for
         */
        bool isBody(){
            for(size_t i{0};i<human.body.size();i++){
                switch(human.dir){
                    case INITIAL:
                        break;
                    case LEFT:
                        if(human.body[i].first == human.head.first-1 && human.body[i].second == human.head.second){
                            return true;
                        }
                        break;
                    case RIGHT:
                        if(human.body[i].first == human.head.first+1 && human.body[i].second == human.head.second){
                            return true;
                        }
                        break;
                    case UP:
                        if(human.body[i].first == human.head.first && human.body[i].second == human.head.second-1){
                            return true;
                        }
                        break;
                    case DOWN:
                        if(human.body[i].first == human.head.first && human.body[i].second == human.head.second+1){
                            return true;
                        }
                        break;    
                }
            }
            return false;
        }

        /**
         * @brief Função para checar se uma parte do labirinto é uma parede
         * 
         * @param check pedaço do labirinto
         * @return true se for parede
         * @return false se não for
         */
        bool isWall(std::string check){
            if(check == "▄"){
                return true;
            }
            return false;
        }

        /**
         * @brief Função para imprimir o labirinto
         * 
         * @param lines tamanho
         */
        void printWorld(int lines){
            for(int i{0};i<=lines;i++){
                for(int j{0};j<cols;j++){
                    if(world[i][j] == "."){
                        std::cout << "  ";
                    }else if(world[i][j] == "గ"){
                        std::cout << "గ ";
                    }else if(world[i][j] == "❉"){
                        std::cout << "❉ ";
                    }else if(world[i][j] == "▄"){
                        std::cout << "▄ ";
                    }else{
                        bool aux = false;
                        for(size_t k{0};k<human.body.size();k++){
                            if(human.body[k].first == j && human.body[k].second == i){
                                std::cout << "o ";
                                aux = true;
                            }
                        }
                        if(!aux){
                            std::cout <<"  ";
                        }
                    }
                }
                std::cout << std::endl;
            }
        }

        /**
         * @brief Função que cria uma grid para análise posterior do caminho
         * 
         * @param line linha para ser criada
         */
        void makeWorld(std::string line){
            std::vector<std::string>temp;
            for(auto& c : line) {
                std::string aux(1, c);
                temp.push_back(aux);
            }
            world.push_back(temp);
        }

        /**
         * @brief função que melhora graficamente a grid do labirinto
         * 
         */
        void makeWorldBetter(){
            std::vector<std::string>temp;
            for(int i{0};i<rows;i++){
                for(int j{0};j<cols;j++){
                    if(world[i][j] == "#"){
                        world[i][j] = "▄";
                    }else if(world[i][j] == "*"){
                        world[i][j] = "గ";
                        human.head.first = j;
                        human.head.second = i;
                        human.posInit.first = j;
                        human.posInit.second = i;
                    }else if(world[i][j] == "." || world[i][j] == " "){

                    }else{
                        std::cout << "POORLY FORMATED LABYRINTH PLEASE CHECK THE ENTRY FILE\n";
                        exit(0);
                    }
                }    
            }
            //printWorld(world.size()-1);
            std::cout << std::endl;
        }

        int level=0;
        int rows=0;
        int cols=0;
        std::vector<std::vector<std::string>> world;
        Snake human;
};

#endif
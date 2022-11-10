#ifndef _IA_H_
#define _IA_H_

#include "Direction.h"
#include "Node.h"
#include "Path.h"
#include "Maze.h"
#include "Coordinate.h"

#include <vector>
#include <algorithm>
#include <stack>

#include "Maze.h"

class IA{
    public: 


        std::vector<std::vector<int>>grid;
        std::pair<int,int>target;
        std::pair<int,int>start;

        /**
         * @brief Adiciona o alvo que queremos chegar (destino = comida)
         * 
         * @param target 
         */
        void setTarget(Coordinate target){
            linhaAlvo = target.coord.second;
            colunaAlvo = target.coord.first;
        }

        /**
         * @brief utilizada para casos em que não há caminho, decide uma jogada aleatória
         * 
         */
        void randomPlay(){
            srand(time(NULL));
            int aux = rand() % 3;
            Path random;
            if(aux == 0){
                random.linha = start.second-1; //CIMA
                random.coluna = start.first;
                caminho.push(random);
            }
            if(aux == 1){
                random.linha = start.second;
                random.coluna = start.first+1; //DIREITA
                caminho.push(random);
            }
            if(aux == 2){
                random.linha = start.second+1; //BAIXO
                random.coluna = start.first;
                caminho.push(random);
            }
            if(aux == 3){
                random.linha = start.second;
                random.coluna = start.first-1;
                caminho.push(random);
            }
        }

        /**
         * @brief Adiciona o local de saido ao procurar caminho
         * 
         */
        void setStart(std::pair<int,int>start){
            linhaInicial = start.second;
            colunaInicial = start.first;
        }

        /**
         * @brief Inicia a grid 
         * 
         * @param aux labirinto atual
         */
        void startGrid(Maze aux){
            for(int i{0};i<aux.rows;i++){
                std::vector<int>temp;  
                for(int j{0};j<aux.cols;j++){
                    if(aux.world[i][j] == "❉"){
                        temp.push_back(1);
                    }else if(aux.world[i][j] == "."){
                        temp.push_back(0);
                    }else if(aux.world[i][j] == "▄"){
                        temp.push_back(0);
                    }else if(aux.world[i][j] == "గ"){
                        temp.push_back(1);
                    }else{
                        bool check = false;
                        for(size_t k{0};k<aux.human.body.size();k++){
                            if(aux.human.body[k].first == j && aux.human.body[k].second == i){
                                temp.push_back(0);
                                check = true;
                            }
                        }
                        if(!check){
                            temp.push_back(1);
                        }
                    }
                }
                grid.push_back(temp);
            }

            startNodes(aux);
        }
        
        /**
         * @brief Verifica se é andável
         * 
         * @param i linha
         * @param j coluna
         * @return int 1 ou 0 indicando verdadeiro ou falso
         */
        int isWalkable(std::vector<std::vector<int>>grid,int i,int j){
            if(grid[i][j]==1){
                return 1;
            }
            return 0;
        }

        /**
         * @brief imprime a grid
         * 
         */
        void drawGrid(std::vector<std::vector<int>>grid){
            size_t i,j;
            for(i=0;i<grid.size();i++){
                for(j=0;j<grid[0].size();j++){
                    if(i==0){
                        std::cout << "▄" << " ";
                        continue;
                    }else if(j==0){
                        std::cout << "▄" << " ";
                        continue;
                    }else if(i==grid.size()-1){
                        std::cout << "▄" << " ";
                        continue;
                    }else if(j==grid.size()-1){
                        std::cout << "▄" << " ";
                        continue;
                    }else if(i==linhaInicial&&j==colunaInicial){
                        std::cout << "S ";
                        continue;
                    }else if(i==linhaAlvo&&j==colunaAlvo){
                        std::cout << "G ";
                        continue;
                    }else if(grid[i][j]==4){
                        std::cout << "X ";
                        continue;
                    }else if(grid[i][j]==1){
                        std::cout << "  ";
                        continue;
                    }else if(grid[i][j]==0){
                        std::cout << "▄" << " ";
                        continue;
                    }
                }
                std::cout<<"\n";
            }
        }

        /**
         * @brief Inicia cada node da grid
         * 
         * @param aux grid atual
         */
        void startNodes(Maze aux){
            size_t i,j;
            for(i=0;i<grid.size();i++){
                std::vector<Node>aux;
                for(j=0;j<grid[0].size();j++){
                    Node temp; 
                    temp.walkable = isWalkable(grid,i,j);
                    temp.listaAberta = 0;
                    temp.listaFechada = 0;
                    temp.g = 0;
                    temp.h = 0;
                    temp.f = temp.g+temp.h;
                    temp.parenteLinha = 0;
                    temp.parenteColuna = 0;
                    aux.push_back(temp);
                }
                node.push_back(aux);
            }
            pathFinder(aux);
        }

        /**
         * @brief Cálculo do valor da distância entre dois pontos
         * 
         * @param linha1 linha ponto 1
         * @param coluna1 coluna ponto 1
         * @param linha2  linha ponto 2
         * @param coluna2  coluna ponto  2
         * @return int distancia
         */
        int heuristic(int linha1,int coluna1,int linha2, int coluna2){
            int linhah = (abs(linha2-linha1)*10);
            int colunah = (abs(coluna2-coluna1)*10);
            return std::max(linhah,colunah);
        }


        /**
         * @brief Função para achar o caminho até a comida
         * 
         * @param aux labirinto atual
         */
        void pathFinder(Maze aux){
            size_t i,j;
            size_t linhaatual = linhaInicial;
            size_t colunaatual = colunaInicial;
            node[linhaatual][colunaatual].h = heuristic(linhaatual,colunaatual,linhaAlvo,colunaAlvo);
            node[linhaatual][colunaatual].f = node[linhaatual][colunaatual].g+node[linhaatual][colunaatual].h;
            node[linhaatual][colunaatual].listaAberta=1;
            
            size_t contBreak = 0;
            size_t linhaBreak = 0;
            size_t colunaBreak = 0;
            bool isBreak = false;

            while(linhaatual!=linhaAlvo || colunaatual!=colunaAlvo){
                if(linhaatual==linhaBreak && colunaatual == colunaBreak){
                    contBreak++;
                }else{
                    linhaBreak = linhaatual;
                    colunaBreak = colunaatual;
                }
                if(contBreak>1){
                    randomPlay();
                    isBreak = true;
                    break;
                }
                int menorF =10000;
                for(i=0;i<grid.size();i++){
                    for(j=0;j<grid[0].size();j++){
                        if(node[i][j].listaAberta ==1){
                            if(node[i][j].f<=menorF){
                                linhaatual = i;
                                colunaatual = j;
                                menorF = node[linhaatual][colunaatual].f;
                            }
                        }
                    }
                }
                node[linhaatual][colunaatual].listaAberta = 0;
                node[linhaatual][colunaatual].listaFechada = 1;
                
                if(node[linhaatual-1][colunaatual].walkable == 1 && node[linhaatual-1][colunaatual].listaFechada == 0){
                    if(node[linhaatual-1][colunaatual].listaAberta==0){
                        node[linhaatual-1][colunaatual].listaAberta = 1;
                        node[linhaatual-1][colunaatual].listaFechada = 0;
                        node[linhaatual-1][colunaatual].parenteLinha = linhaatual;
                        node[linhaatual-1][colunaatual].parenteColuna = colunaatual;
                        node[linhaatual-1][colunaatual].g = node[linhaatual][colunaatual].g + 10;
                        node[linhaatual-1][colunaatual].h = heuristic((linhaatual-1),(colunaatual),linhaAlvo,colunaAlvo);
                        node[linhaatual-1][colunaatual].f = node[linhaatual-1][colunaatual].g + node[linhaatual-1][colunaatual].h; 
                    }   
                }
                if(node[linhaatual+1][colunaatual].walkable == 1 && node[linhaatual+1][colunaatual].listaFechada == 0){
                    if(node[linhaatual+1][colunaatual].listaAberta==0){
                        node[linhaatual+1][colunaatual].listaAberta = 1;
                        node[linhaatual+1][colunaatual].listaFechada = 0;
                        node[linhaatual+1][colunaatual].parenteLinha = linhaatual;
                        node[linhaatual+1][colunaatual].parenteColuna = colunaatual;
                        node[linhaatual+1][colunaatual].g = node[linhaatual][colunaatual].g + 10;
                        node[linhaatual+1][colunaatual].h = heuristic((linhaatual-1),(colunaatual),linhaAlvo,colunaAlvo);
                        node[linhaatual+1][colunaatual].f = node[linhaatual+1][colunaatual].g + node[linhaatual+1][colunaatual].h; 
                    }
                }
                if(node[linhaatual][colunaatual-1].walkable == 1 && node[linhaatual][colunaatual-1].listaFechada == 0){
                    if(node[linhaatual][colunaatual-1].listaAberta==0){
                        node[linhaatual][colunaatual-1].listaAberta = 1;
                        node[linhaatual][colunaatual-1].listaFechada = 0;
                        node[linhaatual][colunaatual-1].parenteLinha = linhaatual;
                        node[linhaatual][colunaatual-1].parenteColuna = colunaatual;
                        node[linhaatual][colunaatual-1].g = node[linhaatual][colunaatual].g + 10;
                        node[linhaatual][colunaatual-1].h = heuristic((linhaatual),(colunaatual-1),linhaAlvo,colunaAlvo);
                        node[linhaatual][colunaatual-1].f = node[linhaatual][colunaatual-1].g + node[linhaatual][colunaatual-1].h; 
                    } 
                }
                if(node[linhaatual][colunaatual+1].walkable == 1 && node[linhaatual][colunaatual+1].listaFechada == 0){
                    if(node[linhaatual][colunaatual+1].listaAberta==0){
                        node[linhaatual][colunaatual+1].listaAberta = 1;
                        node[linhaatual][colunaatual+1].listaFechada = 0;
                        node[linhaatual][colunaatual+1].parenteLinha = linhaatual;
                        node[linhaatual][colunaatual+1].parenteColuna = colunaatual;
                        node[linhaatual][colunaatual+1].g = node[linhaatual][colunaatual].g + 10;
                        node[linhaatual][colunaatual+1].h = heuristic((linhaatual-1),(colunaatual),linhaAlvo,colunaAlvo);
                        node[linhaatual][colunaatual+1].f = node[linhaatual][colunaatual+1].g + node[linhaatual][colunaatual+1].h; 
                    } 
                }
                if(node[linhaatual][colunaatual].walkable == 1 && node[linhaatual][colunaatual].listaFechada == 0){
                    if(node[linhaatual][colunaatual].listaAberta==0){
                        node[linhaatual][colunaatual].listaAberta = 1;
                        node[linhaatual][colunaatual].listaFechada = 0;
                        node[linhaatual][colunaatual].parenteLinha = linhaatual;
                        node[linhaatual][colunaatual].parenteColuna = colunaatual;
                        node[linhaatual][colunaatual].g = node[linhaatual][colunaatual].g + 10;
                        node[linhaatual][colunaatual].h = heuristic(linhaatual,colunaatual,linhaAlvo,colunaAlvo);
                        node[linhaatual][colunaatual].f = node[linhaatual][colunaatual].g + node[linhaatual][colunaatual].h; 
                    }  
                }
            }
            linhaatual = linhaAlvo;
            colunaatual = colunaAlvo;

            Path alvo;
            alvo.linha = linhaAlvo;
            alvo.coluna = colunaAlvo;
            if(isBreak==false){
                caminho.push(alvo);
            }
            while((linhaatual!=linhaInicial || colunaatual!=colunaInicial)&&isBreak==false){
                Path aux;
                aux.linha = node[linhaatual][colunaatual].parenteLinha;
                aux.coluna = node[linhaatual][colunaatual].parenteColuna;
                aux.f = node[linhaatual][colunaatual].f;
                linhaatual = aux.linha;
                colunaatual = aux.coluna;
                grid[linhaatual][colunaatual] = 4;
                caminho.push(aux);
            }
            if(isBreak==false){
                caminho.pop();
            }
        }
        
        /**
         * @brief Módulo de um número
         * 
         * @param a número para ser aplicado o módulo
         * @return int módulo do "a"
         */
        int mod(int a){
            if(a<0){
                return -(a);
            }else{
                return a;
            }
        }

        /**
         * @brief Calcula o custo de H utilizado no algoritmo A*
         * 
         * @param currentLine linha atual
         * @param currentCol coluna atual
         * @param endLine linha destino
         * @param endCol coluna destino
         * @return int custo H
         */
        int CalcCostH(int currentLine,int currentCol,int endLine, int endCol){
            int modX = mod(currentLine - endLine);
            int modY = mod(currentCol - endCol);
            return modX + modY;
        }

        size_t linhaAlvo = target.second;
        size_t colunaAlvo = target.first;
        size_t linhaInicial = start.second;
        size_t colunaInicial = start.first;

        std::vector<std::vector<Node>> node;
        std::vector<Node*> openList;
        std::vector<Node*> closedList;
        std::stack<Path>caminho;
};

#endif
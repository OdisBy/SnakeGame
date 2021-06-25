#include "ruliam.h"

bool gameOver;
bool arrow = false;

enum eDirecao { PARADO = 0, ESQUERDA, DIREITA, CIMA, BAIXO};            //Criar enumeração com nome das variaveis de movimento, recebem valores +1 para cada espaço na direita;
eDirecao dir;

//Variaveis da cobra
int x, y;
int tailX[100], tailY[100];
int rabo = 0;
int bufferRaboX[100];
int bufferRaboY[100];
int bufferX;
int bufferY;


//Variaveis globais
float contador;
int score;
int bufferFrutaX;
int bufferFrutaY;
bool diferenteZero = true;


//Variaveis mapa
int largura = 50;
int altura = 20;
int obstaculoX[10];
int obstaculoY[10];
int obsQuantidade = 5;
int frutaX, frutaY;
bool obsPos = false;
char paredeChar = 219;
char obstaculoChar = 254;
char comida = 4;



void Config(){           //Caso jogador queira mudar as configurações do jogo
    Cls();

    cout << "Voce entrou nas configuracoes do jogo da cobrinha!" << endl << "Caso queira mudar a configuracao pressione enter, caso nao aperte qualquer outra tecla!" << endl;
    cin.ignore();


    system("cls");
    cout << "Tamanho do tabuleiro = 20x50 (altura, largura)" << endl;
    char tmp = getch();
        if(tmp == '\r'){
            cout << "Novo tamanho(altura, largura): ";
            cin >> altura;
            cin >> largura;
        }

    Cls();
    cout << "Teclas de movimento: W A S D (mais rapido), caso pressione enter mudara para as arrows keys!" << endl;
    tmp = getch();
    if(tmp == '\r'){
        Cls();
        cout << "Agora as teclas de movimento são as flechinhas do teclado!";
        arrow = true;
    }
    Cls();
    cout << "Quantidade de obstaculos: Atual = 5. Pressione enter para mudar!";
    tmp = getch();
    if(tmp == '\r'){
        Cls();
        cout << "Quantos obstaculos você deseja?" << endl;
        cin >> obsQuantidade;
    }
}


void FrutaGerar(){          //Gera as frutas
    srand((unsigned) time(0));
    frutaX = (rand() % largura) + 1;
    frutaY = (rand() % altura) + 1;

    if(frutaX == largura-1 || frutaY == altura || frutaY < 2 || frutaX == 1){         //Verifica se não está fora do mapa
        frutaX = (rand() % largura) + 1;
        frutaY = (rand() % altura) + 1;
    }

    for(int i = 0; i < obsQuantidade; i++){
        if(obstaculoX[i] == frutaX && obstaculoY[i] == frutaY){     //Verifica se não esta na msm posição de um obstaculo
            frutaX = (rand() % largura) + 1;
            frutaY = (rand() % altura) + 1;
        }
    }
}


void Obstaculos(){                          //Cria obstaculos
    srand((unsigned) time(NULL));
    for(int i = 0; i < obsQuantidade; i++){
        obstaculoX[i] = (rand() % largura) + 1;
        obstaculoY[i] = (rand() % altura) + 1;

        if(obstaculoX[i] == frutaX && obstaculoY[i] == frutaY){     //Verifica se não esta na msm posição de uma fruta
            obstaculoX[i] = (rand() % largura);
            obstaculoY[i] = (rand() % altura);
        }


        for(int j = 0; j < obsQuantidade; j++){             //verifica se não está onde tem outro objeto já
            if(obstaculoX[i] == obstaculoX[j] && obstaculoY[i] == obstaculoY[j]){
                obstaculoX[i] = (rand() % largura);
                obstaculoY[i] = (rand() % altura);
            }
        }

        if(obstaculoX[i] == largura-1 || obstaculoY[i] == altura || obstaculoY[i] < 2 || obstaculoX[i] < 2){         //Verifica se não está fora do mapa
            obstaculoX[i] = (rand() % largura);
            obstaculoY[i] = (rand() % altura);
        }
    }

}

void Inicio(){                  //Void de inicio do jogo, setando configs e posições
    gameOver = false;
    srand((unsigned) time(0));
    FrutaGerar();
    Obstaculos();
    bufferFrutaX = frutaX;
    bufferFrutaY = frutaY;
    y = altura/2;
    x = largura/2;
    bufferX = x;
    bufferY = y;

}

void DrawMap(){                 //Desenha o mapa e os obstaculos
    for (int i = 0; i < largura; i++){      //Printa parede cima e baixo
        gotoxy(i, 0);
        cout << paredeChar;
        gotoxy(i, altura);
        cout << paredeChar;
    }

    cout << endl;

    for(int i = 1; i < altura+1; i++){      //Printa parede da esquerda e da direita
        gotoxy(0, i);
        cout << paredeChar;
        gotoxy(largura-1, i);
        cout << paredeChar;
        cout << endl;
    }

    for (int i = 0; i < obsQuantidade; i++){
        gotoxy(obstaculoX[i], obstaculoY[i]);
        cout << obstaculoChar;
    }

    gotoxy(frutaX, frutaY);
    setConsoleColour(BRIGHT_RED);
    cout << comida;
    setConsoleColour(WHITE);

    gotoxy(x, y);
    setConsoleColour(DARK_GREEN);
    cout << "O";
    setConsoleColour(WHITE);
}

void Draw(){        //Desenha cobra e fruta


    if(bufferFrutaX != frutaX || bufferFrutaY != frutaY){
        gotoxy(frutaX, frutaY);
        setConsoleColour(BRIGHT_RED);
        cout << comida;
        setConsoleColour(WHITE);

        gotoxy(bufferFrutaX, bufferFrutaY);
        cout << " ";
        bufferFrutaX = frutaX;
        bufferFrutaY = frutaY;
    }

    if (bufferX != x || bufferY != y){
        gotoxy(bufferX, bufferY);
        cout << " ";
        gotoxy(x, y);

        setConsoleColour(DARK_GREEN);
        cout << "O";
        setConsoleColour(WHITE);

        bufferX = x;
        bufferY = y;
    }

    for(int k = 0; k < rabo; k++){
        if(bufferRaboX[k] != tailX[k] || bufferRaboY[k] != tailY[k]){
            gotoxy(tailX[k], tailY[k]);
            setConsoleColour(BRIGHT_GREEN);
            cout << "o";
            setConsoleColour(WHITE);

            diferenteZero = true;

            if(bufferRaboX[k] == 0 || bufferRaboY[k] == 0){
                diferenteZero = false;
            }
            if (diferenteZero == true){
                gotoxy(bufferRaboX[k], bufferRaboY[k]);
                cout << " ";

            }

            bufferRaboX[k] = tailX[k];
            bufferRaboY[k] = tailY[k];
        }
    }


}


void Movimento(){          //Setando movimento com edir

    if (_kbhit())               //Pegar tecla pressionada;
    {
        if(arrow == false){              //Caso não for usar as setinhas
            switch (_getch())
            {
                case 'a':
                    dir = ESQUERDA;
                    break;
                case 'd':
                    dir = DIREITA;
                    break;
                case 'w':
                    dir = CIMA;
                    break;
                case 's':
                    dir = BAIXO;
                    break;
                default:
                    break;
            }
        }

            else{
                switch (_getch()){      //Caso use as setinhas
                    case KEY_LEFT:
                        dir = ESQUERDA;
                        break;
                    case KEY_RIGHT:
                        dir = DIREITA;
                        break;
                    case KEY_UP:
                        dir = CIMA;
                        break;
                    case KEY_DOWN:
                        dir = BAIXO;
                        break;
                    default:
                        break;
                }
            }
        }
}


void Logica(){
    switch (dir)                        //Dir com direções
    {
        case ESQUERDA:
            x--;
            break;
        case DIREITA:
            x++;
            break;
        case CIMA:
            y--;
            break;
        case BAIXO:
            y++;
            break;
        default:
            break;
    }

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = bufferX;
    tailY[0] = bufferY;
    for (int i = 1; i < rabo; i++)      //Rabo seguir a cobrinha
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if(x == frutaX && y == frutaY){         //Gerar nova fruta aleatória
        FrutaGerar();
        rabo++;
        score+=5;
    }

    for(int i = 1; i < rabo; i++){                  //Caso encoste no próprio rabo morre
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if(x == largura-1 || y == altura || y == 0 || x == 0)       //Bater nas paredes morre
        gameOver = true;

    for(int i = 0; i < obsQuantidade; i++){
        if(x == obstaculoX[i] && y == obstaculoY[i])
            gameOver = true;
    }

}

void ScorePontuacao(){
    PT();
    gotoxy(largura+2, altura/2);
    cout << "Contador: " << int(contador) << " segundo(s)";
    gotoxy(largura+2, (altura/2)+1);
    cout << "Pontuação: " << score;
}

int main(){
    ShowConsoleCursor(false);
    cout << "Bem vindo ao jogo da cobrinha do Ruliam" << endl;
    cout << "Para comecar o jogo aperte qualquer tecla" << endl << "Caso queira mudar alguma configuração pressione c" << endl;
    char tmp = getch();
    if(tmp == 'c')
        Config();

    Cls();

    Inicio();
    DrawMap();

    while(!gameOver){
        Movimento();
        Logica();
        Draw();
        Sleep(200);
        contador += 0.2;
        ScorePontuacao();
    }

    gotoxy(largura+2, (altura/2)+2);
    Pause();

    Cls();

    cout << "Fim do jogo!" << endl;
    cout << "Sua pontuacao total foi: " << int(contador)+score;
    cout << endl;

    return 0;
}

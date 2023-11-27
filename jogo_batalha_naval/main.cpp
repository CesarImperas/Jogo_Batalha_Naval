// Caio Cesar 24/11/23
// Jogo Batalha Naval

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

// Cabeçalho de funções (programa saber que elas existem)
int main();

// Função para limpar tela
void limpaTela(){
    system("CLS");
}

// Função para preencher o tabuleiro com água
void preencheTabuleiro(char tabuleiro[10][10], char mascara[10][10]){
    // Auxiliares de navegação
    int linha, coluna;

    // Preenche o tabuleiro com água ('A')
    for (linha = 0; linha < 10; linha++){
        for (coluna = 0; coluna < 10; coluna++){
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
        }
    }
}

// Função para exibir o tabuleiro
void exibeTabuleiro(char mascara[10][10], char tabuleiro[10][10], bool exibeGabarito){
    // Colorir as letras (azul, verde, e a cor normal do terminal)
    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    string red = "\e[0;31m";
    string normal = "\e[0m";

    // Auxiliares de navegação
    int linha, coluna;

    // Marcar as colunas
    int cont;
    for(cont = 0; cont < 10; cont++){
        // Espaço para alinhamento
        if(cont == 0){
            cout << "      ";
        }
        cout << cont << " ";
    }

    // Marcar as colunas (seta '|')
    cout << endl;
    for(cont = 0; cont < 10; cont++){
        // Espaço para alinhamento
        if(cont == 0){
            cout << "      ";
        }
        cout << "|" << " ";
    }

    // Quebra de linha no começo
    cout << endl;

    // Exibe o tabuleiro
    for (linha = 0; linha < 10; linha++){
        cout << linha << " -- ";
        for (coluna = 0; coluna < 10; coluna++){
            // Trocar a cor da letra exibida
            switch(mascara[linha][coluna]){
                case 'A':
                    cout << blue << " " << mascara[linha][coluna] << normal;
                    break;
                case 'B':
                    cout << green << " " << mascara[linha][coluna] << normal;
                    break;
                case 'M':
                    cout << red << " " << mascara[linha][coluna] << normal;
                    break;
                default:
                    cout << " " << mascara[linha][coluna];
                    break;
            }     
        }

        // Quando finaliza a linha, da uma quebra de linha
        cout << endl;
    }

    if(exibeGabarito){
        cout << "\nAbaixo o gabarito das posicoes de cada item no jogo!\n" << endl;

        // Marcar as colunas
        int cont;
        for(cont = 0; cont < 10; cont++){
            // Espaço para alinhamento
            if(cont == 0){
                cout << "      ";
            }
            cout << cont << " ";
        }

        // Marcar as colunas (seta '|')
        cout << endl;
        for(cont = 0; cont < 10; cont++){
            // Espaço para alinhamento
            if(cont == 0){
                cout << "      ";
            }
            cout << "|" << " ";
        
        }
        // Quebra de linha no começo
        cout << endl;
        // Exibe o tabuleiro
        for (linha = 0; linha < 10; linha++){
            cout << linha << " -- ";
            for (coluna = 0; coluna < 10; coluna++){
                // Trocar a cor da letra exibida
                switch(tabuleiro[linha][coluna]){
                    case 'A':
                        cout << blue << " " << tabuleiro[linha][coluna] << normal;
                        break;
                    case 'B':
                        cout << green << " " << tabuleiro[linha][coluna] << normal;
                        break;
                    case 'M':
                        cout << red << " " << tabuleiro[linha][coluna] << normal;
                        break;
                    default:
                        cout << " " << tabuleiro[linha][coluna];
                        break;
                }     
            }
            // Quando finaliza a linha, da uma quebra de linha
            cout << endl;
        }
        // Quebra de linha
        cout << endl;
    }
}

// Função para preencher com minas
void preencheMinas(char tabuleiro[10][10]){
    /// Variáveis gerais
    int linhaMina, colunaMina;                                      // Linha e coluna para colocar as minas
    int quantidadeMina = 5, quantidadePreenchida = 0;               // Quantidade máxima e preenchida por minas
    int cont;                                                       // Contador

    // Laço para preencher com minas
    while(quantidadePreenchida < quantidadeMina){
        // Coloca minas
        for(cont = 0; cont < quantidadeMina; cont++){
            linhaMina = rand() % quantidadeMina;
            colunaMina = rand() % quantidadeMina;

            // Verificar se ele está susbstituindo uma água
            if(tabuleiro[linhaMina][colunaMina] == 'A'){
                // Insere uma mina
                tabuleiro[linhaMina][colunaMina] = 'M';

                // Atualiza o contador
                quantidadePreenchida += 1;
            }      
        }
    }
}

// Função para preencher com barcos o tabuleiro
void preencheBarcos(char tabuleiro[10][10]){
    /// Variáveis gerais
    int quantidadeBarco = 10, quantidadePreenchida = 0;             // Quantida máxima e verificar se ocorreu o preenchimento de todos os barcos
    int cont;                                                       // Contador
    int linhaBarco, colunaBarco;                                    // Linha e coluna para colocar o barco
    
    // Laço para preencher todos os barcos
    while(quantidadePreenchida < quantidadeBarco){
        // Coloca barcos
        for(cont = 0; cont < quantidadeBarco; cont++){
            linhaBarco = rand() % quantidadeBarco;
            colunaBarco = rand() % quantidadeBarco;

            // Verificar se ele está susbstituindo uma água
            if(tabuleiro[linhaBarco][colunaBarco] == 'A'){
                // Insere um barco
                tabuleiro[linhaBarco][colunaBarco] = 'B';

                // Atualiza o contador
                quantidadePreenchida += 1;
            }      
        }
    }
}

// Função que verifica tiro e pontos
void verificaTiro(char tabuleiro[10][10], int linhaJogada, int colunaJogada, int *pontos, string *mensagem){    
    // Verificar quantos pontos adquiriu
    switch(tabuleiro[linhaJogada][colunaJogada]){
        case 'B':
            *mensagem = "\nParabens, voce acertou um BARCO! (+10 pontos)";
            *pontos += 10;
            break;
        case 'A':
            *mensagem = "\nAcertou a AGUA, nao ganhou pontos!";
            break;
        case 'M':
            *mensagem = "\nInfelizmente atingiu uma MINA! (-15 pontos)";
            *pontos -= 15;
            break;
    }
}

// Função do jogo
void jogo(string nomeJogador){
    // Matriz com char
    char tabuleiro[10][10], mascara[10][10];                // Tabuleiro do jogo e sua máscara
    int linhaJogada, colunaJogada;                          // Posições escolhidas pelo jogador
    int pontos = 0;                                         // Pontuação do jogador
    int opcao;                                              // Opções do fim do jogo
    int tentativas = 0, maximoTentativas = 10;               // Tentativas e o máximo de tentativas do jogador 
    string mensagem = "\nBem-vindo(a) ao Batalha Naval!";   // Mensagem a ser exibido na tela

    // Preencher o tabuleiro
    preencheTabuleiro(tabuleiro, mascara);

    // Preencher com barcos o tabuleiro
    preencheBarcos(tabuleiro);

    // Preencher com minas o tabuleiro
    preencheMinas(tabuleiro);

    // Loop até o jogo acabar
    while (tentativas < maximoTentativas && pontos >= 0){
        // Limpar a tela
        limpaTela();

        // Exibe o tabuleiro (e passa parâmetro true - quer exibir gabartio | false - se NÃO quer exibir o gabarito)
        exibeTabuleiro(mascara, tabuleiro, false);

        cout << mensagem << endl;
        cout << "\nPontos: " << pontos << endl;
        cout << "Tentativas restantes: " << maximoTentativas - tentativas << endl;

        cout << "\nPor favor, " << nomeJogador << ", digite uma linha entre 0 e 9 (ambos inclusos): ";
        cin >> linhaJogada;
        cout << "Agora, digite uma coluna tambem entre 0 e 9 (ambos inclusos): ";
        cin >> colunaJogada;

        // Verificação de posição e se ja foi selecionada
        while((linhaJogada < 0 || colunaJogada < 0) || (linhaJogada > 9 || colunaJogada > 9) || mascara[linhaJogada][colunaJogada] != '*'){
            cout << "\nPor favor, " << nomeJogador << ", digite uma linha VALIDA: ";
            cin >> linhaJogada;
            cout << "Agora, digite uma coluna VALIDA: ";
            cin >> colunaJogada;
        }

        // Atualizar os pontos
        verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, &mensagem);

        // Realiza um "furo" entre a camada do tabuleiro máscara, e o tabuleiro real com a água
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;
    }

    // Limpar a tela
    limpaTela();

    // Mensagem dependendo da pontuação
    if(pontos < 0){
        // Mensagem se perdeu
        cout << "Infelizmente, " << nomeJogador << ", voce perdeu o jogo por pontos negativos!" << "\nPontos: " << pontos << "\n" << endl;
    }else{
        // Mensagem se não perdeu por pontos
        cout << "Parabens, " << nomeJogador << ", voce obteve " << pontos << " pontos!\n" << endl;
    }
    
    // Exibe tabuleiro final do jogador + gabarito
    exibeTabuleiro(mascara, tabuleiro, true);

    // Opção de retorno ou sair do jogo
    cout << "Fim de jogo, o que deseja fazer?";
    cout << "\n1 - Jogar novamente";
    cout << "\n2 - Ir para o menu inicial";
    cout << "\n3 - Sair do jogo\n";
    cout << "\nEscolha uma opcao e tecla ENTER: ";
    cin >> opcao;

    // Escolhas
    switch(opcao){
        case 1:
            limpaTela();
            jogo(nomeJogador);
            break;
        case 2:
            limpaTela();
            main();
            break;
        case 3:
            limpaTela();
            cout << "Ate mais! <3";
            break;
    }
}

// Função menu
int main(){
    // Criar números aleatórios (SEM REPETIÇÃO)
    srand((unsigned)time(NULL));

    // Opção escolhida pelo usuário
    int opcao = 0;

    // Nome do jogador
    string nomeJogador;                                     

    while (opcao < 1 || opcao > 3){
        cout << "Bem-vindo(a) ao jogo Batalha Naval!";
        cout << "\n1 - Jogar";
        cout << "\n2 - Sobre";
        cout << "\n3 - Sair\n";
        cout << "\nEscolha uma opcao e tecla ENTER: ";

        cin >> opcao;

        // Limpar a tela
        limpaTela();

        switch (opcao){
        case 1:
            cout << "Antes de comecar o jogo, digite seu nome: ";
            cin >> nomeJogador;
            // Início do jogo
            jogo(nomeJogador);
            break;
        case 2:
            // Informações do jogo
            cout << "Informacoes do jogo!" << endl;
            cout << "Jogo desenvolvido por Caio Cesar 24/11/23 utilizando linguagem C++" << endl;
            cout << "\nBatalha naval consiste em acertar barcos (dado um mapa com coordenadas (X,Y)), e conseguir ao final do jogo, uma pontuacao o mais proximo do maximo.";
            cout << "\nContudo, o seu pior inimigo sao as minas (bombas) instaladas no mapa, que caso acerte, sua pontuacao eh diminuida, ate chegar em 0";
            cout << "\nou quando suas tentativas acabarem, o jogo eh finalizado." << endl;
            cout << "\nTabuleiro 10x10";
            cout << "\nTentativas: 10 | Pontuacoes: +10 (Barco) / 0 (Agua) / -15 (Minas)";
            cout << "\nAo todo mapa, sao dispostos 10 barcos e 5 minas, boa sorte!" << endl;
            cout << "\nJogo feito como parte de projetos do curso da Udemy, e que se necessario, passara por melhorias ao longo do tempo, muito obrigado e ate a proxima!\n";
            cout << "\nContato: github.com/CesarImperas" << endl;
            cout << "\n1 - Voltar";
            cout << "\n2 - Sair\n";
            cout << "\nEscolha uma opcao e tecle ENTER: ";
            cin >> opcao;

            // Retornar ao menu, ou fechar o jogo
            if(opcao == 1){
                    limpaTela();
                    main();
                }else{
                    limpaTela();
                    cout << "Ate mais! <3" << endl;
                }

            break;
        case 3:
            // Sair do jogo
            cout << "Ate mais!" << endl;
            break;
        }
    }
    return 0;
}
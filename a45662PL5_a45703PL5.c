#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"funcionalidades.h"

int main()
{
    int formatoLeitura, gerirOuIniciar, gerirConcurso, escolha, quantia=0, d[3], m[3], f[3], LinhasPerguntas[9], i=0, suficientes=1, tamanhoNomeJogador;
    int numPosPerguntaTXT, resp[4], numResposta, desistiu = 0, tam, garantido=0, valorPorCerta = 0, facilCont=0, medioCont=0, dificilCont=0, numPergunta;
    char palavraProcurada[257], nomeJogador[100], dif[20], respostaJogador[10], resposta[10];
    char *pos, ch;

    PERGUNTAS p[N] = {}; // Array de perguntas
    JOGADOR j[1000] = {}; // Array de jogadores (e respetivas quantias ganhas)

    linha();
    printf("\t\t\t★  - QUEM QUER SER MILIONÁRIO - ★\n");
    linha();
    printf("• Em que formato gostaria que as perguntas fossem lidas?\n\n");
    printf("↪  1. TEXTO\n");
    printf("↪  2. BINÁRIO\n\n");
    printf("Opção -> ");
    do
    {
        if (scanf("%d", &formatoLeitura) != 1) 
        {
            limpaInput();
            printf(" ✘  Input inválido! Digite algo válido: ");
            continue;
        }
        /*   ↓  Lê os ficheiros pretendidos na forma de texto ou binário  ↓   */
        switch (formatoLeitura)
        {
        case 1:
            leTXT(p, "db.txt");
            break;
        case 2:
            leBin(p, "db.bin");
            break;
        default:
            printf(" ✘  Opção inválida! Digite algo válido: ");
            break;
        }
    }while(formatoLeitura != 1 && formatoLeitura != 2);

    do // Estará sempre a repetir até o user decidir sair do programa (OPÇÃOP 0 NO MENU PRINCIPAL)
    {
        linha();
        printf("___________________________| ⇒  - MENU PRINCIPAL - ⇐  |_____________________________\n\n");
        printf("• Escolha uma das opções disponíveis: \n\n");
        printf("↪  1. GERIR CONCURSO\n");
        printf("↪  2. INICIAR CONCURSO\n\n");
        printf("↪  0. SAIR\n\n");
        printf("Opção -> ");
        /*   ↓  Faz a verificação do input, só aceitanto 0, 1 ou 2  ↓   */
        while(scanf("%d", &gerirOuIniciar) != 1)
        {
            limpaInput();
            printf(" ✘  Input inválido! Digite algo válido: ");
        }
        while(gerirOuIniciar < 0 || gerirOuIniciar > 2)
        {
            limpaInput();
            printf(" ✘  Opção inválida! Digite algo válido: ");
            while(scanf("%d", &gerirOuIniciar) != 1)
            {
                limpaInput();
                printf(" ✘  Input inválido! Digite algo válido: ");
            }
        }
        linha();
        /*   ↓  GERIR CONCURSO  ↓   */
        if(gerirOuIniciar == 1) 
        {
            do
            {
                printf("___________________________| ⇒  - GERIR CONCURSO - ⇐  |_____________________________\n\n");
                printf("• Escolha uma das opções disponíveis: \n\n");
                printf("↪  1. LISTAR QUESTÕES\n");
                printf("↪  2. PROCURAR QUESTÕES\n");
                printf("↪  3. ADICIONAR QUESTÃO\n");
                printf("↪  4. ELIMINAR QUESTÃO\n");
                printf("↪  5. VOLTAR AO MENU PRINCIPAL\n\n");
                printf("Opção -> ");
                /*   ↓  Verifica input, só aceitanto 1, 2, 3, 4 ou 5  ↓   */
                while(scanf("%d", &gerirConcurso) != 1)
                {
                    limpaInput();
                    printf(" ✘  Input inválido! Digite algo válido --> ");
                }
                while(gerirConcurso < 1 || gerirConcurso > 5)
                {
                    limpaInput();
                    printf(" ✘  Opção inválida! Digite algo válido --> ");
                    while(scanf("%d", &gerirConcurso) != 1)
                    {
                        limpaInput();
                        printf(" ✘  Input inválido! Digite algo válido --> ");
                    }
                } 
                switch (gerirConcurso)
                {
                case 1:
                    do
                    {
                        linha();
                        printf("__________________| ⇒  - GERIR CONCURSO / LISTAR QUESTÕES - ⇐  |___________________\n\n");
                        limpaInput();

                        mostraArray(p, N); // Lista as questões
                        escolha = repetirAcao(); // Pergunta ao user se quer repetir a ação
                    } while (escolha == 1);
                    break;
                case 2:
                    do
                    {
                        linha();
                        printf("__________________| ⇒  - GERIR CONCURSO / PROCURAR QUESTÕES - ⇐  |__________________\n\n");
                        limpaInput();

                        printf("• Escreva uma palavra / frase e será remetido para a(s) pergunta(s) que a(s) contêm.\n");
                        printf("🔎 -> ");
                        fgets(palavraProcurada, 100, stdin);
                        pos = strchr(palavraProcurada, '\n');
                        *pos = '\0';

                        printf("\n");
                        indicePergunta(palavraProcurada, p); // Mostra todas as perguntas que contêm a letra/palavra/frase pretendida
                        escolha = repetirAcao(); // Pergunta ao user se quer repetir a ação
                    } while (escolha == 1);
                    break;
                case 3:
                    facilCont=0, medioCont=0, dificilCont=0;
                    linha();
                    printf("_________________| ⇒  - GERIR CONCURSO / ADICIONAR QUESTÕES - ⇐  |__________________\n\n");
                    printf("• Nesta secção pode criar novas questões, adicionando-as ao programa.\n");
                    printf("• Das 150 perguntas no total, deve haver 50 de cada dificuldade.\n\n");
                    printf("   Feita a contagem, relembramos que existem:\n");
                    /*   ↓  Avisa o user sobre quantas perguntas de cada dificuldade já estão "registadas"  ↓   */
                    for(i=0; i<N && strlen(p[i].questao)>0; i++)
                    {
                        if(strcmp("facil", p[i].dificuldade) == 0)
                            facilCont++;
                        if(strcmp("medio", p[i].dificuldade) == 0)
                            medioCont++;
                        if(strcmp("dificil", p[i].dificuldade) == 0)
                            dificilCont++;
                    }
                    printf("  ➙  %d FÁCEIS\n", facilCont);
                    printf("  ➙  %d MÉDIAS\n", medioCont);
                    printf("  ➙  %d DIFÍCEIS\n\n", dificilCont);
                    limpaInput();

                    adicionaPerguntaIO(p); // Adiciona pergunta(s)

                    gravaBin(p, "db.bin"); // Grava as alterações cometidas
                    gravaTXT(p, "db.txt");
                    break;
                case 4:
                    linha();
                    printf("__________________| ⇒  - GERIR CONCURSO / ELIMINAR QUESTÕES - ⇐  |__________________\n\n");
                    printf("❗ -> CASO O IDENTIFICADOR SE REPITA, SERÁ REMOVIDA A PERGUNTA CUJO MESMO APARECER\n");
                    printf("  PRIMEIRO NA LISTA (EM CASO DE DÚVIDA VERIFICAR OPÇÃO 1.LISTAR QUESTÕES).\n\n");
                    limpaInput();

                    removePerguntaIO(p); // Remove pergunta(s)

                    gravaBin(p, "db.bin"); // Grava as alterações cometidas
                    gravaTXT(p, "db.txt");
                default:
                    break;
                }
                if(gerirConcurso != 5)
                    linha();
            }while(gerirConcurso != 5);
        }

        /*   ↓  INICIAR CONCURSO  ↓   */
        if(gerirOuIniciar == 2)
        {
            i=0, desistiu = 0, numResposta=0, quantia = 0, facilCont=0, medioCont=0, dificilCont=0, suficientes = 0;
            
            leTXTJOGADOR(j, "resultados.txt"); // Lê o que está no ficheiro resultados.txt (histórico de jogadores e quantias ganhas)
            limpaInput();

            printf("________________|  ⇒  - CONCURSO - QUEM QUER SER MILIONÁRIO - ⇐   |_________________\n\n\n");
            printf("• NOME DO JOGADOR: ");
            fgets(nomeJogador, 257, stdin);
            pos = strchr(nomeJogador, '\n');
            *pos = '\0';
            tamanhoNomeJogador = strlen(nomeJogador);
            while(tamanhoNomeJogador == 0)
            {
                printf(" ✘  Nome vazio! Indique outro: ");
                fgets(nomeJogador, 257, stdin);
                pos = strchr(nomeJogador, '\n');
                *pos = '\0';
                tamanhoNomeJogador = strlen(nomeJogador);
            }

            infos();

            /* Conta quantas questões de nível fácil/médio/difícil existem */
            for(i=0; i<N && strlen(p[i].questao)>0; i++)
            {
                if(strcmp("facil", p[i].dificuldade) == 0)
                    facilCont++;
                if(strcmp("medio", p[i].dificuldade) == 0)
                    medioCont++;
                if(strcmp("dificil", p[i].dificuldade) == 0)
                    dificilCont++;
            }

            if(facilCont >2  && medioCont > 2 && dificilCont > 2)
            {    
                suficientes = 1;
                /* Sorteia as linhas do db.txt (dentro das perguntas possíveis existentes), q correspondem às perguntas que farão parte do concurso */
                Randoms(facilCont, 1, f, 3); 
                Randoms(facilCont+medioCont, facilCont+1, m, 3); 
                Randoms(facilCont+medioCont+dificilCont, facilCont+medioCont+1, d, 3);  
                juntaArrays(f, m, d, LinhasPerguntas); // Junta todas as linhas das perguntas no array LinhasPerguntas

                /*Tirar comentário se se quiser ver quais foram as linhas referentes às perguntas escolhidas
                printf("As perguntas (db.txt) que foram 'sorteadas' foram as referentes às seguintes linhas: ");
                for(int p=0; p<9; p++)
                    printf("%d ", LinhasPerguntas[p]);*/

                printf("\n\n");   
                linha();
                i=0;
                while(i<9 && desistiu != 1 && numResposta == 0) // Executa o loop enquanto o número de perguntas for menor que nove e o jogador não tiver desistido e a resposta estiver correta, 
                {                                                                               
                    numPosPerguntaTXT = LinhasPerguntas[i]-1; // A posição da pergunta é igual ao número da linha - 1 
                    ch = 65;

                    /*   ↓  Consoante o patamar em que se está, são definidos diferentes valores para o dinheiro garantido quando o jogador perde e para o valor ganho por resposta certa  ↓   */
                    numPergunta = i+1;
                    if(numResposta == 0) // O 0 está associado com a resposta certa
                    {
                        if(numPergunta == 1)
                        {
                            garantido = 0;
                            valorPorCerta = 100;
                        }
                        if(numPergunta == 2)
                            valorPorCerta = 200;
                        if(numPergunta == 4)
                        {
                            printf("❰ PRIMEIRO PATAMAR DE SEGURANÇA -> 500 EUROS ❱\n");
                            garantido = 500;
                            valorPorCerta = 1500;
                        }
                        if(numPergunta == 7)
                        {
                            printf("❰ SEGUNDO PATAMAR DE SEGURANÇA -> 5000 EUROS ❱\n");
                            garantido = 5000;
                            valorPorCerta = 5000;
                        }

                        quantia += valorPorCerta; // à quantia é adicionado o valor da respetiva resposta certa
                    }
                    printf("\n");

                    /*   ↓  SUMÁRIO DO JOGO  ↓   */
                    printf("➙  SALDO ATUAL: %d EUROS.\n", quantia-valorPorCerta);
                    printf("➙  SE ACERTAR FICARÁ COM: %d euros\n", quantia);
                    printf("➙  SE ERRAR/DESISTIR FICARÁ COM: %d euros\n\n", garantido);

                    /*   ↓  TRANSFORMAÇÃO PARA MAIÚSCULA (ESTÉTICA)  ↓   */
                    if(strcmp(p[numPosPerguntaTXT].dificuldade, "facil") == 0)
                        strcpy(dif, "FÁCIL");
                    if(strcmp(p[numPosPerguntaTXT].dificuldade, "medio") == 0)
                        strcpy(dif, "MÉDIO");
                    if(strcmp(p[numPosPerguntaTXT].dificuldade, "dificil") == 0)
                        strcpy(dif, "DIFÍCIL");

                    printf("• PERGUNTA %d (%s): %s\n", numPergunta, dif, p[numPosPerguntaTXT].questao); // Faz a pergunta
        
                    Randoms(3, -1, resp, 4); // sorteia 4 números de 0 a 3 e coloca no array resp
                    printf("\n");


                    /* A cada resposta possível (A,B,C,D) é atribuido cada número do array resp (constituido por 0, 1, 2, 3) */
                    for(int k=0; k<4; k++)
                    {
                        printf("%c. ", ch);
                        /* Tirar comentário se pretender ver a ordem sorteada para as perguntas (0 = resposta certa)
                        printf("%d ", resp[k]);*/
                        if(resp[k] == 0)
                            printf("%s", p[numPosPerguntaTXT].respostaCerta); // na letra que estiver associada com o número 0, é imprimida a respost certa
                        else if(resp[k] == 1)
                            printf("%s", p[numPosPerguntaTXT].respostaErrada1); // nas restantes letras que estievrem associadas com os restantes números (1, 2, 3), são imprimidas respostas erradas
                        else if(resp[k] == 2)                               
                            printf("%s", p[numPosPerguntaTXT].respostaErrada2);
                        else if(resp[k] == 3)
                            printf("%s", p[numPosPerguntaTXT].respostaErrada3);
                        printf("\n");
                        ch += 1;
                    }
                    printf("X. (CASO QUEIRA DESISTIR)\n\n");
                    /*   ↓  Faz a validação da opção escolhida pelo user, aceitanto apenas A, B, C, D ou X (Case insensitive para facilitar o user) ↓   */
                    do
                    {
                        printf("↪ OPÇÃO: ");
                        fgets(resposta, 257, stdin);
                        pos = strchr(resposta, '\n');
                        *pos = '\0';
                        tam = strlen(resposta);
                        minuscula(resposta, respostaJogador);
                        if (tam == 0)
                            printf(" ✘ Opção vazia!!\n");
                        if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0)
                            printf(" ✘ Opção inválida!!\n");
                    } while ((strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0) || tam == 0);

                    /*   ↓  VERIFICA-SE QUAL É O NÚMERO ASSOCIADO À LETRA RESPONDIDA E, CONSEQUENTEMENTE SE É OU NÃO A RESPOSTA CERTA  ↓   */
                    if(strcmp(respostaJogador, "a") == 0)
                        numResposta = resp[0]; 
                    else if(strcmp(respostaJogador, "b") == 0)
                        numResposta = resp[1];
                    else if(strcmp(respostaJogador, "c") == 0)
                        numResposta = resp[2];
                    else if(strcmp(respostaJogador, "d") == 0)
                        numResposta = resp[3];
                    else
                        desistiu = 1;

                    printf("\n");
                    linha();
                    //sleep(1.1);
                    i++;
                }
            }
            printf("\n");

            /*   ↓  Imprime mensangens consoante rumo do jogo  ↓   */
            if(desistiu == 1)
            {
                quantia = garantido;
                printf("➤  %s DESISTIU. LEVA PARA CASA: %d EUROS\n", nomeJogador, garantido);
                printf("✓  RESPOSTA CERTA: '%s'.\n", p[numPosPerguntaTXT].respostaCerta);
            }
            else if(numResposta != 0)
            {
                quantia = garantido;
                printf("➤  %s ERROU A PERGUNTA. LEVA PARA CASA: %d EUROS\n", nomeJogador, garantido);
                printf("✓  RESPOSTA CERTA: '%s'.\n", p[numPosPerguntaTXT].respostaCerta);
            }
            else if(suficientes == 0)
            {
                linha();
                printf("\n➤  NÃO HÁ PERGUNTAS SUFICIENTES PARA INICIAR O CONCURSO (MÍNIMO é 3 DE CADA DIFICULDADE)!\n");
            }
            else
                printf(" ♛  PARABÉNS, %s! GANHOU O PRÉMIO MÁXIMO! RECEBE: 20.000 EUROS !!! ♛\n", nomeJogador);
            
            adicionaJogadorIO(j, nomeJogador, quantia);
            gravaTXTJOGADOR(j, "resultados.txt");
        }
    }while(gerirOuIniciar != 0);
    printf("*\t\t\t     Trabalho elaborado por:\t\t\t\t   *\n");
    printf("\t        Guilherme Teixeira (45667) e Marco Bernardes (45703)\n");
    printf("\t     ENGENHARIA INFORMÁTICA - PROGRAMAÇÃO - 1ºANO - 2020/2021\n");
    linha();
    return 0;
}
#include <iostream>
#include <string>
// #include <vector> // Não utilizado, array C-style em uso
#include <limits>      // Para std::numeric_limits
#include <cstdlib>     // Para system("cls") / system("clear")
#include <algorithm>   // Para std::min, std::swap
#include <ctime>       // Para clock() e CLOCKS_PER_SEC
//APS 1 OBS: A APS 2 SE ENCONTRA NO FIM DA APS 1

// Estrutura para armazenar dados do aluno
struct Aluno {
    int identificador; // Chave primária para identificação do aluno
    std::string nome;
    float media;
    bool aprovado; // Definido como true se media >= 7.0
};

// Define o tamanho máximo do vetor de alunos
const int TAMANHO_VETOR = 50;

Aluno alunos[TAMANHO_VETOR]; // Array para armazenar os dados dos alunos
int quantidadeAlunos = 0; // Contador do número de alunos atualmente no vetor

// Protótipos das funções
bool VetorEstaOrdenado();

void Ordenar();

void quicksort_helper(Aluno arr[], int baixo, int alto); // Função auxiliar para o Quicksort


void LimparBufferEPausar(const std::string &mensagemPausa = "Pressione ENTER para continuar...") {
    std::cout << mensagemPausa;
    // Ignora caracteres restantes na linha de entrada atual.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Aguarda nova entrada (pressionar ENTER).
    std::cin.get();
}


void LimparNewlineAposCin() {
    if (std::cin.fail()) {
        // Se a última leitura falhou (ex: entrada não numérica para int)
        std::cin.clear(); // Limpa as flags de erro do std::cin.
    }
    // Descarta o restante da linha no buffer de entrada.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// retorna o índice do aluno se encontrado, caso contrário -1.
int BuscaSequencial(int id) {
    for (int i = 0; i < quantidadeAlunos; ++i) {
        if (alunos[i].identificador == id) {
            return i; // Aluno encontrado no índice i.
        }
    }
    return -1; // Aluno não encontrado.
}

// Realiza busca binária por um aluno usando o identificador.
// Pré-condição: o vetor 'alunos' deve estar ordenado por 'identificador'.
// Retorna o índice do aluno se encontrado, caso contrário -1.
int BuscaBinaria(int id) {
    int inicio = 0;
    int fim = quantidadeAlunos - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2; // Evita overflow para 'inicio + fim' grandes.
        if (alunos[meio].identificador == id) {
            return meio; // Aluno encontrado no índice meio.
        }
        if (alunos[meio].identificador < id) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1; // aluno não encontrado.
}

// adiciona um novo aluno ao vetor
void AdicionarAluno() {
    system("cls");
    std::cout << "===========================================\n";
    std::cout << "            ADICIONAR ALUNO                \n";
    std::cout << "===========================================\n";

    if (quantidadeAlunos >= TAMANHO_VETOR) {
        std::cout << "Vetor de alunos lotado! Não é possível adicionar mais alunos.\n";
        LimparBufferEPausar();
        return;
    }

    int id;
    std::string nomeAluno;
    float mediaAluno;

    std::cout << "Digite o identificador do aluno: ";
    std::cin >> id;

    if (std::cin.fail()) {
        // Validação da entrada do identificador.
        LimparNewlineAposCin();
        std::cout << "Identificador inválido! Deve ser um número.\n";
        LimparBufferEPausar();
        return;
    }
    LimparNewlineAposCin(); // remove newline após leitura do inteiro.

    if (BuscaSequencial(id) != -1) {
        // verifica se o identificador já existe.
        std::cout << "Aluno com identificador " << id << " já existe no sistema!\n";
        LimparBufferEPausar();
        return;
    }

    std::cout << "Digite o nome do aluno: ";
    std::getline(std::cin, nomeAluno); // Lê o nome completo (permite espaços).

    std::cout << "Digite a media do aluno: ";
    std::cin >> mediaAluno;

    if (std::cin.fail()) {
        // Validação da entrada da média.
        LimparNewlineAposCin();
        std::cout << "Média inválida! Deve ser um número.\n";
        LimparBufferEPausar();
        return;
    }
    LimparNewlineAposCin(); // Remove newline após leitura do float.

    // Adiciona o novo aluno ao vetor.
    alunos[quantidadeAlunos].identificador = id;
    alunos[quantidadeAlunos].nome = nomeAluno;
    alunos[quantidadeAlunos].media = mediaAluno;
    alunos[quantidadeAlunos].aprovado = (mediaAluno >= 7.0f); // Define status de aprovação.
    quantidadeAlunos++;

    std::cout << "Aluno adicionado com sucesso!\n";
    LimparBufferEPausar();
}

// exibe os dados de um aluno específico.
void ExibirDadosAluno(const Aluno &aluno) {
    std::cout << "\n--- Dados do Aluno ---\n"
            << "Identificador: " << aluno.identificador << "\n"
            << "Nome:          " << aluno.nome << "\n"
            << "Media:         " << aluno.media << "\n"
            << "Situacao:      " << (aluno.aprovado ? "Aprovado" : "Reprovado") << "\n";
}

// usuário buscar um aluno por identificador(matricula).
void BuscarAluno() {
    system("cls");
    std::cout << "===========================================\n";
    std::cout << "            BUSCAR ALUNO                   \n";
    std::cout << "===========================================\n";

    if (quantidadeAlunos == 0) {
        std::cout << "Nenhum aluno cadastrado para pesquisar.\n";
        LimparBufferEPausar();
        return;
    }

    int idPesquisa;
    std::cout << "Digite o identificador do aluno a ser buscado: ";
    std::cin >> idPesquisa;

    if (std::cin.fail()) {
        LimparNewlineAposCin();
        std::cout << "Identificador de pesquisa inválido!\n";
        LimparBufferEPausar();
        return;
    }
    LimparNewlineAposCin();

    int opcaoBusca;
    std::cout << "\nEscolha o método de busca:\n";
    std::cout << "[1] Busca Sequencial\n";
    std::cout << "[2] Busca Binária\n";
    std::cout << "Opção: ";
    std::cin >> opcaoBusca;

    if (std::cin.fail()) {
        LimparNewlineAposCin();
        std::cout << "Opção de busca inválida!\n";
        LimparBufferEPausar();
        return;
    }
    LimparNewlineAposCin();

    int posicao = -1;

    if (opcaoBusca == 1) {
        posicao = BuscaSequencial(idPesquisa);
    } else if (opcaoBusca == 2) {
        if (!VetorEstaOrdenado()) {
            // Busca binária requer vetor ordenado.
            std::cout << "\nAtenção: Para a busca binária, o vetor precisa estar ordenado.\n";
            std::cout << "Deseja ordenar o vetor agora? (1-Sim / 0-Não): ";
            int respostaOrdenar;
            std::cin >> respostaOrdenar;

            if (std::cin.fail()) {
                LimparNewlineAposCin();
                std::cout << "Resposta inválida!\n";
                LimparBufferEPausar();
                return;
            }
            LimparNewlineAposCin();

            if (respostaOrdenar == 1) {
                Ordenar(); // Chama a função de ordenação.
            } else {
                std::cout << "Busca binária cancelada pois o vetor não está ordenado.\n";
                LimparBufferEPausar();
                return;
            }
        }
        // Realiza busca binária se o vetor estiver (ou foi) ordenado.
        if (VetorEstaOrdenado()) {
            posicao = BuscaBinaria(idPesquisa);
        } else {
            std::cout << "Vetor ainda não está ordenado. Busca binária não pode ser realizada.\n";
        }
    } else {
        std::cout << "Opção de método de busca inválida!\n";
        LimparBufferEPausar();
        return;
    }

    if (posicao != -1) {
        ExibirDadosAluno(alunos[posicao]);
    } else {
        std::cout << "\nAluno com identificador " << idPesquisa << " não encontrado.\n";
    }
    LimparBufferEPausar();
}

// Verifica se o vetor 'alunos' está ordenado pelo campo 'identificador'.
// Retorna true se ordenado ou se contiver 0 ou 1 elemento, false caso contrário.
bool VetorEstaOrdenado() {
    for (int i = 0; i < quantidadeAlunos - 1; ++i) {
        if (alunos[i].identificador > alunos[i + 1].identificador) {
            return false; // Elementos fora de ordem encontrados.
        }
    }
    return true; // Vetor está ordenado.
}

// Função auxiliar recursiva para o algoritmo Quicksort.
// Particiona e ordena o subarray arr[baixo..alto].
void quicksort_helper(Aluno arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pivo_id = arr[alto].identificador; // Escolhe o último elemento como pivô.
        int i = (baixo - 1); // Índice do menor elemento.

        for (int j = baixo; j <= alto - 1; j++) {
            // Se o elemento atual é menor ou igual ao pivô.
            if (arr[j].identificador <= pivo_id) {
                i++; // Incrementa o índice do menor elemento.
                std::swap(arr[i], arr[j]); // Troca arr[i] e arr[j].
            }
        }
        std::swap(arr[i + 1], arr[alto]); // Coloca o pivô na posição correta.
        int p_idx = i + 1; // Índice de partição (posição final do pivô).

        quicksort_helper(arr, baixo, p_idx - 1); // Ordena sub-array à esquerda do pivô.
        quicksort_helper(arr, p_idx + 1, alto); // Ordena sub-array à direita do pivô.
    }
}

// usuário ordena o vetor de alunos pelo identificador.
void Ordenar() {
    system("cls");
    std::cout << "===========================================\n";
    std::cout << "            ORDENAR ALUNOS                 \n";
    std::cout << "===========================================\n";

    if (quantidadeAlunos < 2) {
        std::cout << "Não há alunos suficientes para ordenar (necessário pelo menos 2).\n";
        LimparBufferEPausar();
        return;
    }

    if (VetorEstaOrdenado()) {
        std::cout << "O vetor já está ordenado por identificador.\n";
        LimparBufferEPausar();
        return;
    }

    int opcaoMetodo;
    std::cout << "Escolha o método de ordenação (pelo identificador):\n";
    std::cout << "[1] Insertion Sort\n";
    std::cout << "[2] Selection Sort\n";
    std::cout << "[3] Quicksort\n";
    std::cout << "Opção: ";
    std::cin >> opcaoMetodo;

    if (std::cin.fail()) {
        LimparNewlineAposCin();
        std::cout << "Opção de método de ordenação inválida!\n";
        LimparBufferEPausar();
        return;
    }
    LimparNewlineAposCin();

    clock_t inicio = clock(); // contagem do tempo de ordenação.

    switch (opcaoMetodo) {
        case 1: {
            // Insertion Sort
            std::cout << "Executando Insertion Sort...\n";
            for (int i = 1; i < quantidadeAlunos; ++i) {
                Aluno chave = alunos[i];
                int j = i - 1;
                while (j >= 0 && alunos[j].identificador > chave.identificador) {
                    alunos[j + 1] = alunos[j];
                    j--;
                }
                alunos[j + 1] = chave;
            }
            break;
        }
        case 2: {
            // Selection Sort
            std::cout << "Executando Selection Sort...\n";
            for (int i = 0; i < quantidadeAlunos - 1; ++i) {
                int idx_min = i;
                for (int j = i + 1; j < quantidadeAlunos; ++j) {
                    if (alunos[j].identificador < alunos[idx_min].identificador) {
                        idx_min = j;
                    }
                }
                if (idx_min != i) {
                    std::swap(alunos[i], alunos[idx_min]);
                }
            }
            break;
        }
        case 3: {
            // Quicksort
            std::cout << "Executando Quicksort...\n";
            quicksort_helper(alunos, 0, quantidadeAlunos - 1); // Chama função auxiliar.
            break;
        }
        default:
            std::cout << "Método de ordenação inválido!\n";
            LimparBufferEPausar();
            return;
    }

    double duracao = double(clock() - inicio) / CLOCKS_PER_SEC; // Calcula duração.
    std::cout << "Ordenação concluída em " << duracao << " segundos.\n";

    int limiteExibicao = std::min(quantidadeAlunos, 5); // Exibe os primeiros 5 para verificação.
    if (limiteExibicao > 0) {
        std::cout << "Primeiros " << limiteExibicao << " identificadores (após ordenação): ";
        for (int i = 0; i < limiteExibicao; ++i) {
            std::cout << alunos[i].identificador << (i < limiteExibicao - 1 ? ", " : "\n");
        }
    }
    LimparBufferEPausar();
}

// exibe os alunos com base em diferentes critérios de média
void ExibirAlunos() {
    system("cls");
    std::cout << "===========================================\n";
    std::cout << "            EXIBIR ALUNOS                  \n";
    std::cout << "===========================================\n";

    if (quantidadeAlunos == 0) {
        std::cout << "Nenhum aluno cadastrado para exibir.\n";
        LimparBufferEPausar();
        return;
    }

    int opcaoCriterio;
    std::cout << "Escolha o critério de exibição:\n";
    std::cout << "[1] Alunos aprovados (média >= 7)\n";
    std::cout << "[2] Alunos reprovados (média < 7)\n";
    std::cout << "[3] Alunos com média >= 9\n";
    std::cout << "[4] Alunos com média <= 5\n";
    std::cout << "[5] Todos os alunos\n";
    std::cout << "Opção: ";
    std::cin >> opcaoCriterio;

    if (std::cin.fail()) {
        LimparNewlineAposCin();
        std::cout << "Opção de critério inválida!\n";
        LimparBufferEPausar();
        return;
    }
    LimparNewlineAposCin();

    system("cls"); // limpar a tela
    std::cout << "-----------------------------------------------------------------\n";
    std::cout << "ID   | NOME DO ALUNO                | MÉDIA | SITUAÇÃO \n";
    std::cout << "-----------------------------------------------------------------\n";

    bool encontrouAlgum = false;
    switch (opcaoCriterio) {
        case 1: // alunos aprovados.
            for (int i = 0; i < quantidadeAlunos; ++i) {
                if (alunos[i].aprovado) {
                    printf("%-4d | %-28s | %-5.2f | %s\n", alunos[i].identificador, alunos[i].nome.c_str(),
                           alunos[i].media, "Aprovado");
                    encontrouAlgum = true;
                }
            }
            break;
        case 2: //  alunos reprovados.
            for (int i = 0; i < quantidadeAlunos; ++i) {
                if (!alunos[i].aprovado) {
                    printf("%-4d | %-28s | %-5.2f | %s\n", alunos[i].identificador, alunos[i].nome.c_str(),
                           alunos[i].media, "Reprovado");
                    encontrouAlgum = true;
                }
            }
            break;
        case 3: // alunos com média >= 9.
            for (int i = 0; i < quantidadeAlunos; ++i) {
                if (alunos[i].media >= 9.0f) {
                    printf("%-4d | %-28s | %-5.2f | %s\n", alunos[i].identificador, alunos[i].nome.c_str(),
                           alunos[i].media, (alunos[i].aprovado ? "Aprovado" : "Reprovado"));
                    encontrouAlgum = true;
                }
            }
            break;
        case 4: // alunos com média <= 5.
            for (int i = 0; i < quantidadeAlunos; ++i) {
                if (alunos[i].media <= 5.0f) {
                    printf("%-4d | %-28s | %-5.2f | %s\n", alunos[i].identificador, alunos[i].nome.c_str(),
                           alunos[i].media, (alunos[i].aprovado ? "Aprovado" : "Reprovado"));
                    encontrouAlgum = true;
                }
            }
            break;
        case 5: // Exibe todos os alunos.
            for (int i = 0; i < quantidadeAlunos; ++i) {
                printf("%-4d | %-28s | %-5.2f | %s\n", alunos[i].identificador, alunos[i].nome.c_str(), alunos[i].media,
                       (alunos[i].aprovado ? "Aprovado" : "Reprovado"));
                encontrouAlgum = true;
            }
            break;
        default:
            std::cout << "Critério de exibição inválido!\n";
            LimparBufferEPausar();
            return;
    }

    if (!encontrouAlgum) {
        std::cout << "Nenhum aluno encontrado para o critério selecionado.\n";
    }
    std::cout << "-----------------------------------------------------------------\n";
    LimparBufferEPausar();
}

// mostra o menu principal do programa.
void MostrarMenu() {
    system("cls");
    std::cout << "===========================================\n";
    std::cout << "      SISTEMA DE GERENCIAMENTO DE ALUNOS    \n";
    // std::cout << "         (Compatível com Dev-C++)         \n"; // Comentário sobre compatibilidade opcional
    std::cout << "===========================================\n";
    std::cout << "[1] Adicionar Aluno\n";
    std::cout << "[2] Buscar Aluno\n";
    std::cout << "[3] Ordenar Alunos (por Identificador)\n";
    std::cout << "[4] Exibir Alunos\n";
    std::cout << "[0] Sair do Programa\n";
    std::cout << "===========================================\n";
    std::cout << "Escolha uma opção: ";
}

// função principal do programa.
int main() {
    int opcaoMenu;
    do {
        MostrarMenu();
        std::cin >> opcaoMenu;

        if (std::cin.fail()) {
            // valida a entrada do menu.
            LimparNewlineAposCin();
            std::cout << "Opção inválida! Por favor, digite um número.\n";
            LimparBufferEPausar("Pressione ENTER para tentar novamente...");
            continue;
        }

        switch (opcaoMenu) {
            case 1:
                AdicionarAluno();
                break;
            case 2:
                BuscarAluno();
                break;
            case 3:
                Ordenar();
                break;
            case 4:
                ExibirAlunos();
                break;
            case 0:
                std::cout << "Saindo do programa...\n";
                break;
            default:
                LimparNewlineAposCin(); // limpa newline da opção inválida do menu.
                std::cout << "Opção inválida!\n";
                LimparBufferEPausar();
                break;
        }
    } while (opcaoMenu != 0);

    return 0;
}


////////////////////// APS 2 ///////////////////////////////////
///
///
///
///
///
///
///
#include <iostream>
#include <vector>
#include <string>      // incluído para std::string, embora não usado diretamente em globais/structs aqui
#include <limits>      // para std::numeric_limits
#include <algorithm>   // para std::find, std::swap, std::binary_search, std::lower_bound
#include <cctype>      // para toupper
#include <cstdlib>     // para system("cls")

// variáveis globais
int op;                         // armazena a escolha do usuário no menu
std::vector<int> vet;           // vetor para armazenar inteiros
const size_t tam_MAX = 50;      // tamanho máximo do vetor (usando const para compatibilidade com C++98)


bool verificarSeVetorEstaOrdenado(const std::vector<int>& v); // declaração para substituto do std::is_sorted

// exibe a contagem atual de elementos no vetor.
void MostrarContagem() {
    std::cout << "\n------------------------------------\n";
    std::cout << "Total de elementos no vetor: " << vet.size() << "/" << tam_MAX << std::endl;
    std::cout << "------------------------------------\n";
}

// exibe o menu principal do programa.
void MostrarMenu() {
    system("cls"); // limpa o console (específico para windows)
    std::cout << "===========================================\n";
    std::cout << "                 PROGRAMA                 \n";
    std::cout << "===========================================\n";
    std::cout << "[1] ADICIONAR\n"
              << "[2] BUSCAR\n"
              << "[3] ORDENAR\n"
              << "[4] REMOVER\n"
              << "[5] EXIBIR VETOR\n"
              << "[0] SAIR\n";
    std::cout << "===========================================\n";
    MostrarContagem();
    std::cout << "OPCAO: ";
}

// pausa a execução e aguarda o usuário pressionar enter.
// assume que o buffer de entrada está relativamente limpo antes desta chamada.
void espera() {
    std::cout << "\nPressione ENTER para continuar...";
    // consome o restante da linha atual, efetivamente aguardando o enter.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// adiciona números ao vetor com base nas faixas especificadas
void Add() {
    char continuar;
    do {
        system("cls");
        std::cout << "===========================================\n";
        std::cout << "             ADICIONAR NUMEROS            \n";
        std::cout << "===========================================\n";

        if (vet.size() >= tam_MAX) {
            std::cout << "Vetor ja esta lotado.\n";
            MostrarContagem();
            espera();
            return; // sai da função Add se o vetor estiver cheio
        }

        int num_ad_i;
        std::cout << "Digite o numero a adicionar: ";
        std::cin >> num_ad_i;
        // limpar o buffer de entrada
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // verifica se o número está dentro das faixas permitidas.
        bool determinado =
            (num_ad_i >= 1 && num_ad_i <= 20) ||
            (num_ad_i >= 50 && num_ad_i <= 60) ||
            (num_ad_i >= 100 && num_ad_i <= 120);

        if (!determinado) {
            std::cout << "Nao e possivel adicionar nessa faixa.\n";
            MostrarContagem();
        } else {
            // verifica se o número já existe
            std::vector<int>::iterator it = std::find(vet.begin(), vet.end(), num_ad_i);
            if (it != vet.end()) {
                std::cout << "Numero ja presente no vetor!\n";
                MostrarContagem();
            } else {
                vet.push_back(num_ad_i);
                std::cout << "Numero " << num_ad_i << " adicionado com sucesso!\n";
                MostrarContagem();
            }
        }

        // pergunta se o usuário quer adicionar outro número.
        if (vet.size() < tam_MAX) {
            std::cout << "\nDeseja continuar adicionando? (S/N): ";
            std::cin >> continuar;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cout << "Vetor atingiu a capacidade maxima.\n";
            espera();
            break; // sai do loop pois o vetor está cheio
        }
    } while (toupper(continuar) == 'S' && vet.size() < tam_MAX);
}

// ordena o vetor usando o algoritmo bubble sort.
void BubbleSort(std::vector<int> &v) {
    int n = static_cast<int>(v.size()); // converte para int para os limites do loop
    bool trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                trocou = true;
            }
        }
        if (!trocou) break; //se nenhum par de elementos foi trocado, o vetor está ordenado.
    }
}

// ordena o vetor usando o algoritmo insertion sort.
void InsertionSort(std::vector<int> &v) {
    int n = static_cast<int>(v.size()); // converte para int para os limites do loop
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        // move os elementos de v[0..i-1] que são maiores que a chave
        // para uma posição à frente da sua posição atual.
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

// função auxiliar para verificar se um vetor está ordenado.

bool verificarSeVetorEstaOrdenado(const std::vector<int>& v) {
    if (v.size() < 2) {
        return true; // vetor vazio ou com um único elemento é considerado ordenado.
    }
    for (size_t i = 0; i < v.size() - 1; ++i) {
        if (v[i] > v[i + 1]) {
            return false; // encontrou um par fora de ordem.
        }
    }
    return true; // todos os elementos estão em ordem não decrescente
}

// permite ao usuário ordenar o vetor usando um mét
void Ordenar() {
    system("cls");
    std::cout << "===========================================\n";
    std::cout << "               ORDENAR VETOR               \n";
    std::cout << "===========================================\n";

    if (vet.empty()) {
        std::cout << "Vetor vazio. Nao ha nada para ordenar.\n";
        espera();
        return;
    }

    if (verificarSeVetorEstaOrdenado(vet)) {
        std::cout << "O vetor ja esta ordenado.\n";
        espera();
        return;
    }

    int metodo;
    std::cout << "Escolha o metodo de ordenacao:\n"
              << "[1] BubbleSort\n"
              << "[2] Insertion Sort\n"

              << "Opcao: ";
    std::cin >> metodo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (metodo == 1) {
        BubbleSort(vet);
        std::cout << "Vetor ordenado com BubbleSort.\n";
    } else if (metodo == 2) {
        InsertionSort(vet);
        std::cout << "Vetor ordenado com Insertion Sort.\n";
    } else {
        std::cout << "Opcao invalida. Ordenacao cancelada.\n";
    }
    espera();
}

// permite ao usuário buscar um valor no vetor
int Buscar() {
    system("cls");
    std::cout << "===========================================\n";
    std::cout << "                BUSCAR VALOR               \n";
    std::cout << "===========================================\n";

    if (vet.empty()) {
        std::cout << "Vetor vazio. Nao ha numeros para buscar.\n";
        espera();
        return 0;
    }

    int tipo;
    std::cout << "Escolha o tipo de pesquisa:\n"
              << "[1] Pesquisa Sequencial\n"
              << "[2] Pesquisa Binaria\n"
              << "Opcao: ";
    std::cin >> tipo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int idBUSCA;
    std::cout << "Digite o valor para busca: ";
    std::cin >> idBUSCA;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tipo == 1) { // busca sequencial
        bool encontrado = false;
        for (size_t i = 0; i < vet.size(); i++) {
            if (vet[i] == idBUSCA) {
                std::cout << "Valor " << idBUSCA << " encontrado na posicao " << i << ".\n";
                encontrado = true;
                break; // valor encontrado, não é necessário continuar o loop.
            }
        }
        if (!encontrado) {
            std::cout << "Valor nao encontrado.\n";
        }
    } else if (tipo == 2) { // busca binária

        if (!verificarSeVetorEstaOrdenado(vet)) {
            std::cout << "Para a pesquisa binaria, o vetor precisa estar ordenado.\n"
                      << "Deseja ordenar o vetor agora? (S/N): ";
            char resp;
            std::cin >> resp;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (toupper(resp) == 'S') {
                Ordenar(); // chama a função Ordenar principal que escolhe metodo

                if (!verificarSeVetorEstaOrdenado(vet)) { // verifica se a ordenação foi bem sucedida ou cancelada
                    std::cout << "Vetor nao foi ordenado. Pesquisa binaria cancelada.\n";
                    espera();
                    return 0;
                }
            } else {
                std::cout << "Pesquisa binaria cancelada.\n";
                espera();
                return 0;
            }
        }
        // realiza busca binária se o vetor estiver ordenado.
        if (std::binary_search(vet.begin(), vet.end(), idBUSCA)) {

            std::vector<int>::iterator it = std::lower_bound(vet.begin(), vet.end(), idBUSCA);
            int pos = static_cast<int>(it - vet.begin()); // calcula o índice a partir do iterador.
            std::cout << "Valor " << idBUSCA << " encontrado na posicao " << pos << ".\n";
        } else {
            std::cout << "Valor nao encontrado.\n";
        }
    } else {
        std::cout << "Opcao de pesquisa invalida.\n";
    }
    espera();
    return 0;
}

// permite ao usuário remover elementos do vetor por valor ou posição.
void Remover() {
    system("cls");
    std::cout << "===========================================\n";
    std::cout << "              REMOVER VALOR                \n";
    std::cout << "===========================================\n";

    if (vet.empty()) {
        std::cout << "Vetor vazio. Nao ha nada para remover.\n";
        MostrarContagem();
        espera();
        return;
    }

    std::cout << "Conteudo atual do vetor:\n";
    for (size_t i = 0; i < vet.size(); i++) {
        std::cout << "[" << i << "] = " << vet[i] << "\n";
    }
    MostrarContagem();

    int opcao;
    std::cout << "\nEscolha como deseja remover:\n"
              << "[1] Remover por valor\n"
              << "[2] Remover por posicao\n"
              << "Opcao: ";
    std::cin >> opcao;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (opcao == 1) { // remover por valor
        int valor;
        std::cout << "Digite o valor a ser removido: ";
        std::cin >> valor;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        std::vector<int>::iterator it = std::find(vet.begin(), vet.end(), valor);
        if (it != vet.end()) {
            vet.erase(it); // apaga o elemento encontrado.
            std::cout << "Valor " << valor << " removido com sucesso!\n";
        } else {
            std::cout << "Valor nao encontrado no vetor.\n";
        }
    } else if (opcao == 2) { // remover por posição
        int posicao;
        // garante que vet.size() - 1 não seja negativo se o vetor estiver vazio
        std::cout << "Digite a posicao a ser removida (0 a " << (vet.empty() ? 0 : vet.size() - 1) << "): ";
        std::cin >> posicao;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // valida a posição.
        if (posicao >= 0 && posicao < static_cast<int>(vet.size())) {
            int valor_removido = vet[static_cast<size_t>(posicao)]; // acessa o elemento antes de apagar
            vet.erase(vet.begin() + posicao); // apaga o elemento na posição dada.
            std::cout << "Valor " << valor_removido << " na posicao " << posicao << " removido com sucesso!\n";
        } else {
            std::cout << "Posicao invalida.\n";
        }
    } else {
        std::cout << "Opcao invalida!\n";
    }
    MostrarContagem();
    espera();
}

// exibe todos os elementos atualmente no vetor.
void ExibirVetor() {
    system("cls");
    std::cout << "===========================================\n";
    std::cout << "               EXIBIR VETOR                \n";
    std::cout << "===========================================\n";
    if (vet.empty()) {
        std::cout << "Vetor vazio.\n";
    } else {
        std::cout << "Conteudo atual do vetor:\n";
        for (size_t i = 0; i < vet.size(); i++) {
            std::cout << "[" << i << "] = " << vet[i] << "\n";
        }
    }
    MostrarContagem(); // exibe a contagem ao mostrar o vetor
    espera();
}

// função principal
int main() {


    do {
        MostrarMenu();
        std::cin >> op;

        // validação básica de entrada para a escolha do menu.
        if (std::cin.fail()) {
            std::cin.clear(); // limpa o buffer de erro.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descarta a entrada inválida.
            std::cout << "Entrada invalida! Por favor, digite um numero para a opcao.\n";
            espera();
            op = -1;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpa o newline após entrada válida de inteiro.


        switch (op) {
            case 1: Add(); break;
            case 2: Buscar(); break;
            case 3: Ordenar(); break;
            case 4: Remover(); break;
            case 5: ExibirVetor(); break;
            case 0:
                system("cls");
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opcao invalida!\n";
                espera();
        }
    } while (op != 0);

    return 0; //
}
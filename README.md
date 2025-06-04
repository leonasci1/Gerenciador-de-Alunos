README: Sistema de Gerenciamento de Alunos
Este programa em C++ foi desenvolvido para gerenciar um cadastro simples de alunos, permitindo operações básicas como adicionar, buscar, ordenar e exibir informações dos estudantes. O código foi estruturado para ser compatível com compiladores C++ mais antigos (padrão C++98/03), visando facilitar a compilação em ambientes como o Dev-C++.

Funcionalidades Implementadas
Adicionar Aluno:

Permite o cadastro de um novo aluno, solicitando:
Identificador: Um número inteiro único para cada aluno (chave primária).
Nome: Nome completo do aluno.
Média: Média final do aluno.
O status de Aprovado (média >= 7.0) é definido automaticamente com base na média fornecida.
O sistema verifica se o identificador já está em uso e se há espaço disponível no vetor de alunos (capacidade máxima de 50 alunos).
Buscar Aluno:

Permite ao usuário localizar um aluno através do seu Identificador.
Oferece duas opções de método de busca:
Busca Sequencial: Percorre o vetor de alunos comparando cada identificador.
Busca Binária: Método mais eficiente que exige que o vetor de alunos esteja ordenado por identificador. Se o vetor não estiver ordenado, o programa informa e oferece a opção de ordená-lo antes de prosseguir com a busca.
Ordenar Alunos:

Organiza o vetor de alunos em ordem crescente com base no Identificador.
O usuário pode escolher entre três algoritmos de ordenação:
Insertion Sort
Selection Sort
Quicksort (implementado com uma função auxiliar para evitar o uso de std::function e lambdas do C++11, garantindo compatibilidade).
O sistema verifica previamente se o vetor já se encontra ordenado.
Exibir Alunos:

Apresenta uma listagem dos alunos cadastrados, formatada para fácil leitura.
O usuário pode escolher diferentes critérios para filtrar a exibição:
Todos os alunos cadastrados.
Apenas alunos aprovados (média >= 7.0).
Apenas alunos reprovados (média < 7.0).
Alunos com média igual ou superior a 9.0.
Alunos com média igual ou inferior a 5.0.
Estrutura do Código e Detalhes de Implementação
Linguagem: C++ (adaptado para compatibilidade com o padrão C++98/03).
Estrutura de Dados: Os dados de cada aluno são armazenados em uma struct Aluno contendo os campos identificador (int), nome (std::string), media (float) e aprovado (bool). Um array global estático (Aluno alunos[50]) é utilizado para armazenar os registros.
Interface com o Usuário: O programa utiliza um menu textual simples e interativo para que o usuário possa selecionar as operações desejadas.
Validação de Entrada: Foram implementadas rotinas para validar as entradas numéricas do usuário e para limpar o buffer de entrada (std::cin), tornando o programa mais robusto a entradas inesperadas.
Modularização: O código é dividido em funções para cada uma das principais funcionalidades, facilitando a leitura, o entendimento e a manutenção.
Compatibilidade: O foco na compatibilidade com C++98/03 visa permitir que o código seja compilado e executado em ambientes de desenvolvimento mais antigos ou com configurações padrão que não habilitam recursos de C++ mais modernos por default (como algumas versões do Dev-C++).
Como Compilar e Executar
Compilação:
Utilize um compilador C++ que suporte o padrão C++98/03 (a maioria dos compiladores, como g++ ou o MinGW do Dev-C++, o fará por padrão para código escrito dessa forma).
Não são necessárias flags de compilação para habilitar recursos de C++11 ou posteriores.
Exemplo de comando de compilação com g++:
Bash

g++ nome_do_arquivo.cpp -o nome_do_executavel
Execução:
Após a compilação bem-sucedida, execute o arquivo gerado.
No Windows: nome_do_executavel.exe
No Linux/macOS: ./nome_do_executavel

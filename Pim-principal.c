#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PAGINAS 100
#define MAX_DE_CARACTERES 50
#define MAX_DE_RECEBIMENTOS 100

#define USERNAME "admin"
#define PASSWORD "12345"

// Estrutura para registros de produtos
struct Record {
    char id[MAX_DE_CARACTERES];
    char fruta[MAX_DE_CARACTERES];
    char codigo[MAX_DE_CARACTERES];
    char preco[MAX_DE_CARACTERES];
    int quantidade;
    char pagamento[MAX_DE_CARACTERES];
};

// Estrutura para recebimentos
struct Recebimento {
    char data[MAX_DE_CARACTERES];
    char idProduto[MAX_DE_CARACTERES];
    char valor[MAX_DE_CARACTERES];
    int quantidade;
};

// Função de login
void login() {
    char username[MAX_DE_CARACTERES];
    char password[MAX_DE_CARACTERES];

    printf("Bem-vindo! Por favor, faca login.\n");

    while (1) {
        printf("Nome de usuario: ");
        if (fgets(username, sizeof(username), stdin) == NULL) {
            printf("Erro ao ler o nome de usuario. Tente novamente.\n");
            continue;
        }
        username[strcspn(username, "\n")] = '\0';

        printf("Senha: ");
        if (fgets(password, sizeof(password), stdin) == NULL) {
            printf("Erro ao ler a senha. Tente novamente.\n");
            continue;
        }
        password[strcspn(password, "\n")] = '\0';

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            printf("Login bem-sucedido!\n");
            break;
        } else {
            printf("Nome de usuario ou senha incorretos. Tente novamente.\n");
        }
    }
}

// Função para salvar os dados no arquivo pim-principal.csv
void salvarDados(struct Record paginas[], int numPaginas) {
    FILE *file = fopen("pim-principal.csv", "w");
    if (file != NULL) {
        for (int i = 0; i < numPaginas; i++) {
            fprintf(file, "%s,%s,%s,%s,%d,%s\n", paginas[i].id, paginas[i].fruta, paginas[i].codigo,
                    paginas[i].preco, paginas[i].quantidade, paginas[i].pagamento);
        }
        fclose(file);
        printf("Dados salvos no arquivo 'pim-principal.csv'.\n");
    } else {
        printf("Erro ao abrir o arquivo 'pim-principal.csv' para salvar os dados.\n");
    }
}

// Função para adicionar um novo registro
void adicionarRegistro(struct Record paginas[], int *numPaginas) {
    if (*numPaginas >= MAX_PAGINAS) {
        printf("Limite de registros atingido.\n");
        return;
    }

    struct Record novoRegistro;

    printf("Digite o ID do produto: ");
    fgets(novoRegistro.id, sizeof(novoRegistro.id), stdin);
    novoRegistro.id[strcspn(novoRegistro.id, "\n")] = '\0';

    printf("Digite o nome da fruta: ");
    fgets(novoRegistro.fruta, sizeof(novoRegistro.fruta), stdin);
    novoRegistro.fruta[strcspn(novoRegistro.fruta, "\n")] = '\0';

    printf("Digite o codigo do produto: ");
    fgets(novoRegistro.codigo, sizeof(novoRegistro.codigo), stdin);
    novoRegistro.codigo[strcspn(novoRegistro.codigo, "\n")] = '\0';

    printf("Digite o preco do produto: ");
    fgets(novoRegistro.preco, sizeof(novoRegistro.preco), stdin);
    novoRegistro.preco[strcspn(novoRegistro.preco, "\n")] = '\0';

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoRegistro.quantidade);
    while (getchar() != '\n');

    /*printf("Digite a forma de pagamento: ");
    fgets(novoRegistro.pagamento, sizeof(novoRegistro.pagamento), stdin);
    novoRegistro.pagamento[strcspn(novoRegistro.pagamento, "\n")] = '\0';*/

    paginas[*numPaginas] = novoRegistro;
    (*numPaginas)++;

    salvarDados(paginas, *numPaginas);
    printf("Registro adicionado com sucesso!\n");
}

// Função para listar todos os registros
void listarRegistros(struct Record paginas[], int numPaginas) {
    printf("Lista de registros:\n");
    for (int i = 0; i < numPaginas; i++) {
        printf("Registro %d:\n", i + 1);
        printf("ID: %s\n", paginas[i].id);
        printf("Fruta: %s\n", paginas[i].fruta);
        printf("Codigo: %s\n", paginas[i].codigo);
        printf("Preco: %s\n", paginas[i].preco);
        printf("Quantidade em estoque: %d\n", paginas[i].quantidade);
        printf("-----------------------------\n");
    }
}

// Função para pesquisar registro por ID
void pesquisarPorID(struct Record paginas[], int numPaginas) {
    char id[MAX_DE_CARACTERES];
    printf("Digite o ID do produto a ser pesquisado: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < numPaginas; i++) {
        if (strcmp(paginas[i].id, id) == 0) {
            printf("Produto encontrado:\n");
            printf("ID: %s\n", paginas[i].id);
            printf("Fruta: %s\n", paginas[i].fruta);
            printf("Codigo: %s\n", paginas[i].codigo);
            printf("Preco: %s\n", paginas[i].preco);
            printf("Quantidade: %d\n", paginas[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}

// Função para editar um registro
void editarRegistro(struct Record paginas[], int numPaginas) {
    char id[MAX_DE_CARACTERES];
    printf("Digite o ID do produto a ser editado: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < numPaginas; i++) {
        if (strcmp(paginas[i].id, id) == 0) {
            printf("Produto encontrado. Digite os novos dados:\n");
            printf("Digite o novo nome da fruta: ");
            fgets(paginas[i].fruta, sizeof(paginas[i].fruta), stdin);
            paginas[i].fruta[strcspn(paginas[i].fruta, "\n")] = '\0';

            printf("Digite o novo codigo do produto: ");
            fgets(paginas[i].codigo, sizeof(paginas[i].codigo), stdin);
            paginas[i].codigo[strcspn(paginas[i].codigo, "\n")] = '\0';

            printf("Digite o novo preco do produto: ");
            fgets(paginas[i].preco, sizeof(paginas[i].preco), stdin);
            paginas[i].preco[strcspn(paginas[i].preco, "\n")] = '\0';

            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &paginas[i].quantidade);
            while (getchar() != '\n');

            printf("Digite a nova forma de pagamento: ");
            fgets(paginas[i].pagamento, sizeof(paginas[i].pagamento), stdin);
            paginas[i].pagamento[strcspn(paginas[i].pagamento, "\n")] = '\0';

            salvarDados(paginas, numPaginas);
            printf("Registro editado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}

// Função para mostrar quantidade total em estoque
void mostrarQuantidadeTotalEstoque(struct Record paginas[], int numPaginas) {
    int totalEstoque = 0;
    printf("Quantidade total em estoque de cada fruta:\n");
    for (int i = 0; i < numPaginas; i++) {
        printf("Fruta: %s | Quantidade: %d\n", paginas[i].fruta, paginas[i].quantidade);
        totalEstoque += paginas[i].quantidade;
    }
    printf("\nQuantidade total em estoque de todas as frutas: %d\n", totalEstoque);
}

// Função para alterar quantidade em estoque
void alterarQuantidade(struct Record paginas[], int numPaginas) {
    char id[MAX_DE_CARACTERES];
    printf("Digite o ID do produto para alterar a quantidade: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < numPaginas; i++) {
        if (strcmp(paginas[i].id, id) == 0) {
            printf("Produto encontrado. A quantidade atual e: %d\n", paginas[i].quantidade);
            printf("Digite a nova quantidade: ");
            scanf("%d", &paginas[i].quantidade);
            while (getchar() != '\n');
            salvarDados(paginas, numPaginas);
            printf("Quantidade alterada com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}

// Função para retirar produtos do estoque
void retirarProdutoEstoque(struct Record paginas[], int numPaginas) {
    char id[MAX_DE_CARACTERES];
    printf("Digite o ID do produto a ser retirado: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int quantidadeRetirada;
    int encontrado = 0;

    for (int i = 0; i < numPaginas; i++) {
        if (strcmp(paginas[i].id, id) == 0) {
            printf("Produto encontrado. A quantidade atual e: %d\n", paginas[i].quantidade);
            printf("Digite a quantidade a ser retirada: ");
            scanf("%d", &quantidadeRetirada);
            while (getchar() != '\n');

            if (quantidadeRetirada > paginas[i].quantidade) {
                printf("Quantidade solicitada e maior do que a quantidade em estoque.\n");
            } else {
                paginas[i].quantidade -= quantidadeRetirada;
                salvarDados(paginas, numPaginas);
                printf("Retirada de %d unidade(s) de %s realizada com sucesso!\n", quantidadeRetirada, paginas[i].fruta);
            }

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}

// Função para salvar um recebimento
void salvarRecebimento(struct Recebimento recebimentos[], int numRecebimentos) {
    FILE *file = fopen("recebimentos.csv", "a");
    if (file != NULL) {
        for (int i = 0; i < numRecebimentos; i++) {
            fprintf(file, "%s,%s,%s,%d\n", recebimentos[i].data, recebimentos[i].idProduto, recebimentos[i].valor, recebimentos[i].quantidade);
        }
        fclose(file);
        printf("Recebimentos registrados com sucesso!\n");
    } else {
        printf("Erro ao salvar o recebimento.\n");
    }
}

// Função para adicionar recebimentos de múltiplos produtos
void adicionarRecebimento(struct Record paginas[], int numPaginas) {
    struct Recebimento recebimentos[MAX_DE_RECEBIMENTOS];
    int numRecebimentos = 0;

    printf("Digite a data do recebimento (dd/mm/aaaa): \n");
    fgets(recebimentos[numRecebimentos].data, sizeof(recebimentos[numRecebimentos].data), stdin);
    recebimentos[numRecebimentos].data[strcspn(recebimentos[numRecebimentos].data, "\n")] = '\0';

    while (1) {
        char idProduto[MAX_DE_CARACTERES];
        int quantidade;
        char valor[MAX_DE_CARACTERES];

        printf("\nDigite o ID do produto recebido: \n");
        fgets(idProduto, sizeof(idProduto), stdin);
        idProduto[strcspn(idProduto, "\n")] = '\0';

        int encontrado = 0;
        for (int i = 0; i < numPaginas; i++) {
            if (strcmp(paginas[i].id, idProduto) == 0) {
                printf("Produto encontrado: %s - %s\n", paginas[i].id, paginas[i].fruta);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Produto com ID '%s' não encontrado. Tente novamente.\n", idProduto);
            continue;
        }

        printf("Digite o valor recebido: \n");
        fgets(valor, sizeof(valor), stdin);
        valor[strcspn(valor, "\n")] = '\0';

        printf("Digite a quantidade recebida: \n");
        scanf("%d", &quantidade);
        while (getchar() != '\n');  // Limpar buffer de entrada

        // Armazenar o recebimento
        strncpy(recebimentos[numRecebimentos].idProduto, idProduto, sizeof(recebimentos[numRecebimentos].idProduto));
        strncpy(recebimentos[numRecebimentos].valor, valor, sizeof(recebimentos[numRecebimentos].valor));
        recebimentos[numRecebimentos].quantidade = quantidade;
        numRecebimentos++;

        // Perguntar se o usuário deseja adicionar mais recebimentos
        char continuar;
        printf("Deseja adicionar outro produto ao recebimento? (s/n): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n');  // Limpar buffer de entrada

        if (continuar == 'n' || continuar == 'N') {
            break;
        }
    }

    // Salvar todos os recebimentos
    salvarRecebimento(recebimentos, numRecebimentos);
}

// Função para listar recebimentos
void listarRecebimentos() {
    FILE *file = fopen("recebimentos.csv", "r");
    if (file != NULL) {
        char linha[200];
        printf("Lista de recebimentos:\n");
        while (fgets(linha, sizeof(linha), file)) {
            printf("%s", linha);
        }
        fclose(file);
    } else {
        printf("Nenhum recebimento registrado.\n");
    }
}

// Função para ler o arquivo CSV
void lerCSV(FILE *file, struct Record paginas[], int *numPaginas) {
    char linha[200];
    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]", paginas[*numPaginas].id,
               paginas[*numPaginas].fruta, paginas[*numPaginas].codigo, paginas[*numPaginas].preco,
               &paginas[*numPaginas].quantidade, paginas[*numPaginas].pagamento);
        (*numPaginas)++;
    }
}

// Função principal
int main() {
    setlocale(LC_ALL, "pt_BR");

    login(); // Chama a função de login antes de qualquer outra operação

    struct Record paginas[MAX_PAGINAS];
    int numPaginas = 0;

    FILE *file = fopen("pim-principal.csv", "r");
    if (file != NULL) {
        lerCSV(file, paginas, &numPaginas);
        fclose(file);
    }

    while (1) {
        int opcao;
        printf("\nMenu Principal:\n");
        printf("1. Adicionar novo registro\n");
        printf("2. Listar todos os registros\n");
        printf("3. Pesquisar registro por ID\n");
        printf("4. Editar registro\n");
        printf("5. Mostrar quantidade total em estoque\n");
        printf("6. Alterar quantidade em estoque\n");
        printf("7. Adicionar recebimento\n");
        printf("8. Listar recebimentos\n");
        printf("9. Retirar produto do estoque\n");
        printf("10. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
        case 1:
            adicionarRegistro(paginas, &numPaginas);
            break;
        case 2:
            listarRegistros(paginas, numPaginas);
            break;
        case 3:
            pesquisarPorID(paginas, numPaginas);
            break;
        case 4:
            editarRegistro(paginas, numPaginas);
            break;
        case 5:
            mostrarQuantidadeTotalEstoque(paginas, numPaginas);
            break;
        case 6:
            alterarQuantidade(paginas, numPaginas);
            break;
        case 7: {
            struct Recebimento recebimento;

            printf("Digite a data do recebimento (dd/mm/aaaa): \n");
            fgets(recebimento.data, sizeof(recebimento.data), stdin);
            recebimento.data[strcspn(recebimento.data, "\n")] = '\0';

            printf("Digite o ID do produto recebido: \n");
            fgets(recebimento.idProduto, sizeof(recebimento.idProduto), stdin);
            recebimento.idProduto[strcspn(recebimento.idProduto, "\n")] = '\0';

            printf("Digite o valor recebido: \n");
            fgets(recebimento.valor, sizeof(recebimento.valor), stdin);
            recebimento.valor[strcspn(recebimento.valor, "\n")] = '\0';

            printf("Digite a quantidade recebida: \n");
            scanf("%d", &recebimento.quantidade);
            while (getchar() != '\n');

            salvarRecebimento(&recebimento);
            break;
        }
        case 8:
            listarRecebimentos();
            break;
        case 9:
            retirarProdutoEstoque(paginas, numPaginas);
            break;
        case 10:
            printf("Saindo...\n");
            return 0;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 800
#define DEPTH 8


// Estrutura para representar um nó na árvore de expressões
typedef struct Node {
    char type; // 'c' para constante, 'x' para coordenada x, 'y' para coordenada y, '+' para add, '*' para mult
    double value; // Valor para constantes
    struct Node *left;
    struct Node *right;
} Node;

// Função para gerar um número aleatório entre -1 e 1
double random_double() {
    return (double)rand() / RAND_MAX * 2.0 - 1.0;
}

// Função para criar um nó constante
Node* create_constant_node() {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = 'c';
    node->value = random_double();
    node->left = node->right = NULL;
    return node;
}

// Função para criar um nó de coordenada (x ou y)
Node* create_coordinate_node(char type) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->left = node->right = NULL;
    return node;
}

// Função para criar um nó de operação (add ou mult)
Node* create_operation_node(char type, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->left = left;
    node->right = right;
    return node;
}

// Função para gerar uma árvore de expressões aleatória
Node* generate_expression(int depth) {
    if (depth == 0) {
        // Retorna um nó constante ou de coordenada
        double r = (double)rand() / RAND_MAX;
        if (r < 0.5) {
            return create_constant_node();
        } else if (r < 0.75) {
            return create_coordinate_node('x');
        } else {
            return create_coordinate_node('y');
        }
    } else {
        // Retorna um nó de operação
        double r = (double)rand() / RAND_MAX;
        if (r < 0.5) {
            return create_operation_node('+', generate_expression(depth - 1), generate_expression(depth - 1));
        } else {
            return create_operation_node('*', generate_expression(depth - 1), generate_expression(depth - 1));
        }
    }
}

// Função para avaliar uma árvore de expressões
double evaluate_expression(Node* node, double x, double y) {
    switch (node->type) {
        case 'c': return node->value;
        case 'x': return x;
        case 'y': return y;
        case '+': return evaluate_expression(node->left, x, y) + evaluate_expression(node->right, x, y);
        case '*': return evaluate_expression(node->left, x, y) * evaluate_expression(node->right, x, y);
        default: return 0.0;
    }
}

// Função para gerar uma imagem a partir de uma árvore de expressões
void generate_image(Node* node, char* filename) {
    FILE* file = fopen(filename, "w");
    fprintf(file, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double x = (double)j / WIDTH * 2.0 - 1.0;
            double y = (double)i / HEIGHT * 2.0 - 1.0;
            double value = evaluate_expression(node, x, y);

            // Normaliza o valor para o intervalo [0, 255]
            int color = (int)((value + 1.0) * 127.5);
            fprintf(file, "%d %d %d ", color, color, color);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Função para converter PPM para PNG usando ImageMagick (comando "magick")
void convert_to_png(char* ppm_filename, char* png_filename) {
    char command[256];
    snprintf(command, sizeof(command), "magick %s %s", ppm_filename, png_filename);
    system(command);
}

int main() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    // Gera uma árvore de expressões aleatória
    Node* root = generate_expression(DEPTH);

    // Gera uma imagem PPM a partir da árvore de expressões
    char ppm_filename[] = "output.ppm";
    generate_image(root, ppm_filename);

    // Converte o arquivo PPM para PNG
    char png_filename[] = "output.png";
    convert_to_png(ppm_filename, png_filename);

    printf("Imagem gerada e salva como 'output.png'\n");
    
    return 0;
}

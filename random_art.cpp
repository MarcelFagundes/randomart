#include <iostream>
#include <memory>
#include <random>
#include <fstream>
#include <cmath>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // Inclua o cabeçalho da stb_image_write

constexpr int WIDTH  {1000}
constexpr int HEIGHT {1000}
constexpr int DEPTH  {150}

// Estrutura para representar um nó na árvore de expressões
struct Node {
    char type; // 'c' para constante, 'x' para coordenada x, 'y' para coordenada y, '+' para add, '*' para mult
    double value; // Valor para constantes
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(char type, double value = 0.0, std::unique_ptr<Node> left = nullptr, std::unique_ptr<Node> right = nullptr)
        : type(type), value(value), left(std::move(left)), right(std::move(right)) {}
};

// Função para gerar um número aleatório entre -1 e 1
double random_double() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-1.0, 1.0);
    return dis(gen);
}

// Função para criar um nó constante
std::unique_ptr<Node> create_constant_node() {
    return std::make_unique<Node>('c', random_double());
}

// Função para criar um nó de coordenada (x ou y)
std::unique_ptr<Node> create_coordinate_node(char type) {
    return std::make_unique<Node>(type);
}

// Função para criar um nó de operação (add ou mult)
std::unique_ptr<Node> create_operation_node(char type, std::unique_ptr<Node> left, std::unique_ptr<Node> right) {
    return std::make_unique<Node>(type, 0.0, std::move(left), std::move(right));
}

// Função para gerar uma árvore de expressões aleatória
std::unique_ptr<Node> generate_expression(int depth) {
    if (depth == 0) {
        // Retorna um nó constante ou de coordenada
        double r = random_double();
        if (r < 0.5) {
            return create_constant_node();
        } else if (r < 0.75) {
            return create_coordinate_node('x');
        } else {
            return create_coordinate_node('y');
        }
    } else {
        // Retorna um nó de operação
        double r = random_double();
        if (r < 0.5) {
            return create_operation_node('+', generate_expression(depth - 1), generate_expression(depth - 1));
        } else {
            return create_operation_node('*', generate_expression(depth - 1), generate_expression(depth - 1));
        }
    }
}

// Função para avaliar uma árvore de expressões
double evaluate_expression(const Node* node, double x, double y) {
    switch (node->type) {
        case 'c': return node->value;
        case 'x': return x;
        case 'y': return y;
        case '+': return evaluate_expression(node->left.get(), x, y) + evaluate_expression(node->right.get(), x, y);
        case '*': return evaluate_expression(node->left.get(), x, y) * evaluate_expression(node->right.get(), x, y);
        default: return 0.0;
    }
}

// Função para gerar uma imagem a partir de uma árvore de expressões
void generate_image(const Node* node, const std::string& filename) {
    std::vector<unsigned char> image(WIDTH * HEIGHT * 3); // Vetor para armazenar os dados da imagem (RGB)

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double x = static_cast<double>(j) / WIDTH * 2.0 - 1.0;
            double y = static_cast<double>(i) / HEIGHT * 2.0 - 1.0;
            double value = evaluate_expression(node, x, y);

            // Normaliza o valor para o intervalo [0, 255]
            int color = static_cast<int>((value + 1.0) * 127.5);
            int index = (i * WIDTH + j) * 3;
            image[index] = color;     // R
            image[index + 1] = color; // G
            image[index + 2] = color; // B
        }
    }

    // Salva a imagem como PNG
    stbi_write_png(filename.c_str(), WIDTH, HEIGHT, 3, image.data(), WIDTH * 3);
}

int main() {
    // Gera uma árvore de expressões aleatória
    std::unique_ptr<Node> root = generate_expression(DEPTH);

    // Gera uma imagem a partir da árvore de expressões
    generate_image(root.get(), "output.png");

    std::cout << "Imagem gerada e salva como 'output.png'\n";

    return 0;
}

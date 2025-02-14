# **Hash Visualization com Random Art**

Este projeto implementa a técnica de  **Hash Visualization** proposta no artigo **"Hash Visualization: a New Technique to improve Real-World Security"**, escrito por Adrian Perrig e Dawn Song. A técnica visa melhorar a segurança de sistemas do mundo real ao substituir strings sem significado (como impressões digitais de chaves criptográficas ou senhas) por imagens estruturadas, que são mais fáceis para os humanos compararem e lembrarem.

O código implementa o algoritmo **Random Art**, que gera imagens a partir de strings usando uma gramática probabilística. Essas imagens podem ser usadas para validação de chaves raiz ou autenticação de usuários.

---

## **Tabela de Conteúdos**
1. [Como Funciona](#como-funciona)
2. [Aplicações](#aplicações)
3. [Como Usar](#como-usar)
4. [Exemplo de Saída](#exemplo-de-saída)
5. [Fonte de Pesquisa](#fonte-de-pesquisa)
6. [Licença](#licença)

---

## **Como Funciona**

O código gera uma imagem a partir de uma expressão matemática aleatória, criada usando uma gramática probabilística. A expressão é avaliada para cada pixel da imagem, gerando um valor que é mapeado para uma cor.

### **Passos do Algoritmo**
1. **Geração de Expressões Aleatórias**:
   - O algoritmo usa uma gramática probabilística para gerar expressões matemáticas.
   - As expressões podem incluir operações como `sin`, `cos`, `add`, `mult`, etc.
   - A profundidade da árvore de expressões é limitada para garantir que as imagens geradas sejam regulares e não caóticas.

2. **Avaliação das Expressões**:
   - Para cada pixel `(x, y)`, a expressão é avaliada para gerar um valor.
   - O valor é normalizado para o intervalo `[0, 255]` e usado para definir a cor do pixel.

3. **Geração da Imagem**:
   - A imagem é gerada no formato PPM (Portable PixMap).
   - O arquivo PPM pode ser convertido para PNG usando o ImageMagick.

---

## **Aplicações**

### **1. Validação de Chaves Raiz**
- **Problema**: Os usuários precisam comparar strings hexadecimais longas e sem significado para validar chaves raiz.
- **Solução**: Substituir as strings por imagens geradas por **Random Art**. Os usuários podem comparar as imagens visualmente, o que é mais fácil e confiável.
- **Exemplo**: Um usuário pode comparar a imagem gerada a partir da impressão digital de uma chave raiz com uma imagem de referência publicada em um jornal.

### **2. Autenticação de Usuários**
- **Problema**: Os usuários têm dificuldade em lembrar senhas fortes ou PINs.
- **Solução**: Substituir a memorização de senhas por reconhecimento de imagens. O usuário memoriza um conjunto de imagens (portfólio de imagens) e as reconhece durante a autenticação.
- **Exemplo**: Durante a autenticação, o usuário é apresentado a um conjunto de imagens, algumas do seu portfólio e outras aleatórias. O usuário deve identificar corretamente as imagens do seu portfólio.

---

## **Como Usar**

### **Pré-requisitos**
- **Compilador C**: Instale o GCC ou outro compilador C.
- **ImageMagick**: Instale o ImageMagick para converter o arquivo PPM para PNG.
  - No Linux:
    ```bash
    sudo apt-get install imagemagick
    ```
  - No macOS:
    ```bash
    brew install imagemagick
    ```

### **Compilação e Execução**
1. Clone o repositório ou baixe o código.
2. Compile o código:
   ```bash
   gcc -o random_art random_art.c -lm
   ```
3. Execute o programa:
   ```bash
   ./random_art
   ```
4. O programa gerará dois arquivos:
   - `output.ppm`: O arquivo PPM original.
     
5. Converta o arquivo para PNG:
   ```bash
   feh output.png
   ```
   - `output.png`: O arquivo PNG convertido.

6. Visualize a imagem:
   - Use um visualizador de imagens como o GIMP, Feh, ou navegadores web para abrir `output.png`.

---

## **Exemplo de Saída**

A imagem gerada será uma representação visual da função matemática aleatória criada pelo programa. Dependendo da semente aleatória, a imagem pode variar entre padrões geométricos, gradientes ou formas abstratas.

Exemplo de saída:
```
Imagem gerada e salva como 'output.png'
```

---

## **Fonte de Pesquisa**

O código e as explicações são baseados no artigo:
- **Título**: Hash Visualization: a New Technique to improve Real-World Security
- **Autores**: Adrian Perrig e Dawn Song
- **Instituição**: Carnegie Mellon University
- **Link**: [Artigo Original](https://www.cs.cmu.edu/~adrian/Papers/2000-hashvis.pdf)

---

O código e a implementação do código:
- **Título**: RandomArt
- **Autor**: Alexey Kutepov
- **Link**: [Artigo Original](https://github.com/tsoding/randomart/blob/main/README.md)

---

## **Licença**

Este projeto está licenciado sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.

---

### **Contribuições**
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.

---

### **Contato**
Para dúvidas ou sugestões, entre em contato:
- **Email**: marcelfagundes@hotmail.com
- **GitHub**: [marcelfagundes](https://github.com/marcelfagundes)

---

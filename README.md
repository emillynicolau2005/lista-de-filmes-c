# 🎬 Lista de Filmes — Projeto em C

Projeto prático desenvolvido para a disciplina *Programação Estruturada*, aplicando manipulação de arquivos binários, modularização e uso de struct em C.

O sistema funciona como uma pequena lista de filmes, permitindo *cadastrar* e *consultar* registros armazenados em um arquivo binário (filmes.dat).

---

## 📌 Funcionalidades

✔ Cadastro de filmes  
✔ Consulta de filmes pelo código (posição no arquivo)  
✔ Manipulação de arquivos binários (fseek, fread, fwrite)  
✔ Leitura segura de strings com fgets()  
✔ Uso de struct com três tipos diferentes  
✔ Modularização completa das funções  
✔ Contagem de registros por meio da função tamanho()  

---

## 🧱 Estrutura do Registro

Cada filme é armazenado como:

```c
typedef struct {
    char titulo[50];
    char genero[30];
    int ano;
} filme;

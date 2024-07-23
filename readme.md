<h1 align="center">PID control of the
<p>satellite-camera system with Arduino<p></h1>


<div align="center">
  <strong>🚀 add descrição (resumo do projeto) </strong>
</div>

<div align="center">
  <p>palavras-chave</p>
  <p></p>
</div>

## 📖 Index

- [Overview](#overview)
- [Technologies](#technologies)
- [Environment Setting](#environment-setting)
- [How to Contribute](#how-to-contribute)

## 🔭 Overview

falar sobre a comunicação entre os códigos (muito provavelmente só pelas pastas GUI e arduino, os outros arquivos não fazem parte do projeto principal, são complementos) e da visualização do artigo em LaTex

## 💻 Technologies

- C/C++ for arduino (.ino)
- Python (.py)
- MATLAB (.m)
- ...

[![Tec](https://skillicons.dev/icons?i=py,cpp,vscode,blender,matlab,arduino)](https://skillicons.dev)

add links para as respectivas documentações ou sites oficiais

## ⚙️ Environment Setting

Configuração do Ambiente: fornecer instruções claras e detalhadas sobre como configurar o ambiente de desenvolvimento localmente (com imagens):

- Pré-requisitos
- Instalação de dependências
- Configuração do banco de dados
- Configuração de variáveis de ambiente
- Execução de migrações ou scripts de inicialização
- ...

fornecer exemplos de comandos ou scripts necessários para executar o projeto corretamente

## How to Contribute

If you want to contribute to the project, follow these steps:

1. Fork the repository and clone it to your local machine.

2. Create a new branch for your modifications:
   ```
   git checkout -b my-branch
   ```
3. Make the desired changes and add them to the stage:
   ```
   git add .
   ```
4. Commit your changes:
   ```
   git commit -m "My modifications"
   ```
5. Push your changes to the remote repository:
   ```
   git push origin my-branch
   ```
6. Open a pull request to have your changes reviewed and incorporated into the project.

<b><br>Enjoy the project!  :) </br></b>




<h1 align="center">Satellite Camera System Control</h1>

<div align="center">
  <strong>🚀 Controle e monitoramento de câmeras de satélite</strong>
</div>

<div align="center">
  <p>satélite, controle de câmera, monitoramento, captura de imagem, gestão de dados</p>
</div>

## 📖 Index

- [Overview](#overview)
- [Technologies](#technologies)
- [Environment Setting](#environment-setting)
- [How to Contribute](#how-to-contribute)

## 🔭 Overview

O **Satellite Camera System Control** é um projeto que permite o controle de câmeras em satélites, facilitando o monitoramento, captura de imagens e gestão de dados. Este sistema se comunica principalmente através dos módulos de controle de câmeras e interface de usuário, enquanto outros arquivos são complementares. A documentação detalhada do projeto está disponível em LaTeX.

## 💻 Technologies

- C/C++ para Arduino (.ino)
- Python (.py)
- MATLAB (.m)

[![Tec](https://skillicons.dev/icons?i=py,cpp,vscode,blender,matlab,arduino)](https://skillicons.dev)

- [Python](https://www.python.org/)
- [C++](https://isocpp.org/)
- [MATLAB](https://www.mathworks.com/products/matlab.html)
- [Arduino](https://www.arduino.cc/)

## ⚙️ Environment Setting

Configuração do Ambiente: fornecer instruções claras e detalhadas sobre como configurar o ambiente de desenvolvimento localmente.

### Pré-requisitos

- Python 3.x
- Arduino IDE
- MATLAB
- Docker
- Git

### Instalação de Dependências

1. Clone o repositório:
    ```bash
    git clone https://github.com/el-pitchula/satellite-camera-system-control.git
    ```
2. Navegue até o diretório do projeto:
    ```bash
    cd satellite-camera-system-control
    ```
3. Instale as dependências Python:
    ```bash
    pip install -r requirements.txt
    ```

### Configuração do Banco de Dados

1. Configure o banco de dados MySQL/PostgreSQL:
    ```sql
    CREATE DATABASE satellite_camera;
    ```

2. Defina as variáveis de ambiente:
    ```bash
    export DB_NAME=satellite_camera
    export DB_USER=seu_usuario
    export DB_PASSWORD=sua_senha
    ```

### Execução de Migrações ou Scripts de Inicialização

1. Execute as migrações do banco de dados:
    ```bash
    python manage.py migrate
    ```

### Exemplos de Comandos

1. Inicie o sistema de controle:
    ```bash
    python src/main.py
    ```

2. Acesse a interface de usuário através do navegador:
    ```plaintext
    http://localhost:8000
    ```

## How to Contribute

If you want to contribute to the project, follow these steps:

1. Fork the repository and clone it to your local machine.
2. Create a new branch for your modifications:
    ```bash
    git checkout -b my-branch
    ```
3. Make the desired changes and add them to the stage:
    ```bash
    git add .
    ```
4. Commit your changes:
    ```bash
    git commit -m "My modifications"
    ```
5. Push your changes to the remote repository:
    ```bash
    git push origin my-branch
    ```
6. Open a pull request to have your changes reviewed and incorporated into the project.

<b><br>Enjoy the project!  :) </br></b>

tic-tac-toe/
│
├── src/                     # Código-fonte principal
│   ├── main.c               # Arquivo principal que inicializa o programa
│   ├── game.c               # Implementação das funções do jogo
│   ├── game.h               # Declaração das funções e structs usadas no jogo
│   ├── utils.c              # Funções auxiliares (ex.: tratamento de erros)
│   └── utils.h              # Declaração das funções auxiliares
│
│
│
├── assets/                  # Recursos adicionais
│   ├── ranking.txt          # Arquivo para salvar o ranking (persistência)
│   └── (outros arquivos necessários, como créditos)
│
├── docs/                    # Documentação do projeto
│   ├── relatorio.pdf        # Relatório descritivo
│   └── prints/              # Prints das telas de execução
│
├── tests/                   # Testes (opcional)
│   ├── test_cases.c         # Código para validar funções específicas
│   └── test_cases.h
│
├── .gitignore               # Arquivos e pastas que não devem ser enviados ao Git
├── Makefile                 # Automação da compilação com `make`
└── README.md                # Explicação do projeto e como rodar o código

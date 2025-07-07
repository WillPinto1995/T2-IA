# T2-IA

# Comparativo de Tabelas Hash: Hash Simples vs Hash Duplo com Dados de CEPs

Este projeto implementa uma tabela hash em C com suporte a **sondagem linear (hash simples)** e **hashing duplo**, usando uma base real de **CEPs do Brasil**. O sistema também realiza **redimensionamento dinâmico** e **avalia o desempenho** em tempo de busca e inserção com diferentes taxas de ocupação.

## Estrutura do Projeto

```

.
├── hash.c                  # Implementação da tabela hash
├── hash.h                  # Header da tabela hash
├── main\_hash\_tests.c       # Código principal com testes de busca/inserção
├── ceps\_formatados.txt     # Arquivo de entrada gerado pelo script Python
├── extrair\_ceps.py         # Script para extrair dados do Excel
├── Lista\_de\_CEPs.xlsx      # Base de dados original (Kaggle)
├── Makefile                # Compilação e profiling com gprof
└── README.md

```

---

## 🛠️ Funcionalidades

- Suporte a:
  - Hash Simples (Sondagem Linear)
  - Hash Duplo (com segunda função de hash)
- Redimensionamento Dinâmico da Tabela Hash
- Limite de taxa de ocupação (`threshold`) configurável
- Armazenamento de dados de CEP com cidade e estado
- Suporte a leitura de dados formatados a partir de Excel (.xlsx)
- Testes automatizados com `gprof` para medir desempenho

---

## Entrada esperada (`ceps_formatados.txt`)

Formato por linha:
```

12345;São Paulo;SP
13083;Campinas;SP
30100;Belo Horizonte;MG

````

Esse arquivo é gerado automaticamente pelo script Python a partir do Excel original.

---

## Compilação e Execução

### Compilar com suporte ao `gprof`

```bash
make
````

### Executar

```bash
./main_hash
```

### Analisar desempenho com `gprof`

```bash
make profile
```

Saída gerada: `profile.txt` com tempos de execução de cada função (busca e inserção).

---

## Gerar os Dados Formatados

### Pré-requisitos:

* Python 3
* Pandas

### Executar:

```bash
python extrair_ceps.py
```

Gera `ceps_formatados.txt` a partir do `Lista_de_CEPs.xlsx`.

---

# Experimentos

### Comparativos:

1. **Tempo de Busca x Ocupação**:

   * Testes com ocupação de 10% até 99%
   * Busca por CEPs existentes e inexistentes
   * Comparação hash simples vs hash duplo

2. **Overhead de Redimensionamento**:

   * Inserção com tabela de 6100 buckets (fixa)
   * Inserção com tabela de 1000 buckets (com resize dinâmico)
   * Medida do tempo total e cálculo do overhead

Resultados devem ser planilhados e representados em gráfico:

* **X**: taxa de ocupação
* **Y**: tempo de execução (ms)

---

# Referência da Base de Dados

[Kaggle - Lista de CEPs do Brasil](https://www.kaggle.com/datasets/arvati/lista-de-ceps-do-brasil)

---

# Autor

Weslley Will — Projeto de Estrutura de Dados — 2025

```


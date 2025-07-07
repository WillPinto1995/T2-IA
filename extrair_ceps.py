import pandas as pd

# Caminho do arquivo Excel
arquivo = 'Lista_de_CEPs.xlsx'

# Lê o arquivo (assume que a primeira planilha contém os dados)
df = pd.read_excel(arquivo)

# Verifica colunas
print("Colunas encontradas:", df.columns)

# Ajusta os nomes abaixo conforme as colunas reais do seu Excel
coluna_cep = 'CEP'        # exemplo: 'CEP'
coluna_cidade = 'Cidade'  # exemplo: 'Cidade'
coluna_estado = 'UF'      # exemplo: 'Estado' ou 'UF'

# Remove linhas com dados ausentes
df = df[[coluna_cep, coluna_cidade, coluna_estado]].dropna()

# Garante que o CEP seja string com no mínimo 5 dígitos
df[coluna_cep] = df[coluna_cep].astype(str).str.zfill(8).str[:5]

# Remove duplicatas se quiser
df = df.drop_duplicates(subset=[coluna_cep])

# Exporta para arquivo de texto no formato necessário
with open('ceps_formatados.txt', 'w', encoding='utf-8') as f:
    for _, row in df.iterrows():
        linha = f"{row[coluna_cep]};{row[coluna_cidade]};{row[coluna_estado]}\n"
        f.write(linha)

print("Arquivo 'ceps_formatados.txt' gerado com sucesso!")

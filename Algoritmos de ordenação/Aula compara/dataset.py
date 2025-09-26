import csv
import random
from datetime import datetime, timedelta

# parâmetros do dataset
N_REGISTROS = 100  # quantidade de linhas
ARQUIVO_SAIDA = "dataset_%0d.csv"%N_REGISTROS

# ranges de valores simulados
RANGE_TEMPERATURA = (15.0, 40.0)    # graus Celsius
RANGE_LUMINOSIDADE = (0.0, 1000.0)  # lumens
RANGE_UMIDADE = (20.0, 100.0)       # %
RANGE_VELX_VENTO = (0.0, 15.0)      # m/s

# gera dataset
def gerar_dataset(n_registros):
    dados = []
    inicio = datetime.now()
    for i in range(n_registros):
        registro = {
            "id_no": random.randint(1, 20),
            "temperatura": round(random.uniform(*RANGE_TEMPERATURA), 2),
            "luminosidade": round(random.uniform(*RANGE_LUMINOSIDADE), 2),
            "umidade": round(random.uniform(*RANGE_UMIDADE), 2),
            "velx_vento": round(random.uniform(*RANGE_VELX_VENTO), 2),
            "marca_tempo": (inicio + timedelta(seconds=i*60)).strftime("%Y-%m-%d %H:%M:%S")
        }
        dados.append(registro)
    return dados

# salva em CSV
def salvar_csv(dados, arquivo):
    with open(arquivo, mode="w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=dados[0].keys())
        writer.writeheader()
        writer.writerows(dados)

if __name__ == "__main__":
    dataset = gerar_dataset(N_REGISTROS)
    salvar_csv(dataset, ARQUIVO_SAIDA)
    print(f"✅ Dataset gerado com {N_REGISTROS} registros em '{ARQUIVO_SAIDA}'")

import csv
import re
from typing import List, Dict, Any

def process_csv(
    csv_data: str,
    selected_columns: str,
    row_filter_definitions: str
) -> str:
    """
    __Description__:
    A função recebe dados de um arquivo csv como tipo string
    pelo parametro 'csv_data',
    uma lista de colunas selecionadas no parametro 'selected_columns' e
    definições de filtros no parametro 'row_filter_definitions'.
    Possui a responsábilidade de processar esses dados.

    __Returns__:
        Retorna os dados processados em formato string
        representando o csv processado.
    """


    # Processa os dados csv
    rows = list(csv.reader(csv_data.splitlines()))
    # Denomina a primeira linha como o cabeçalho das colunas
    headers = rows[0]
    # Exclui linha de cabeçalho, separando o restante como dados do csv
    data = rows[1:]

    # Divide a string selected_columns em uma lista de colunas selecionadas
    if selected_columns:
        selected_columns = selected_columns.split(',')
    else:
        selected_columns = headers

    # Define 'filters' como ma lista que irá armazenar
    # os filtros a serem aplicados
    filters = list()
    if row_filter_definitions:
        for line in row_filter_definitions.splitlines():
            header, operator, value = re.split(r'(<=|>=|!=|=|>|<)', line)
            filters.append((header, operator, value))

    def row_matches(row):
        """
        __Description__:
            A função verifica se uma linha atende
        aos critérios de todos os filtros.
        __Returns__:
            Retorna um valor boleano onde 'True' indica
        que a linha passou por todos os filtros e
        'false' sefalho em algum dos filtros.
        """
        for header, operator, value in filters:
            cell_value = row[headers.index(header)]
            if operator == '=' and not cell_value == value:
                return False
            elif operator == '!=' and not cell_value != value:
                return False
            elif operator == '>' and not cell_value > value:
                return False
            elif operator == '<' and not cell_value < value:
                return False
            elif operator == '>=' and not cell_value >= value:
                return False
            elif operator == '<=' and not cell_value <= value:
                return False
        return True

    # Filtra as linhas dos dados, mantendo apenas as linhas que
    # satisfazem todos os filtros
    filtered_data = [row for row in data if row_matches(row)]

    # Obtém os índices das colunas selecionadas a partir dos cabeçalhos
    selected_indices = [headers.index(col) for col in selected_columns]

    #Cria uma nova lista de listas contendo apenas as colunas selecionadas
    # das linhas filtradas
    result_data = [
        [row[idx] for idx in selected_indices] for row in filtered_data
    ]

    # Constrói uma string CSV final, juntando todas as linhas de
    # output com vírgulas e linhas novas
    output = [selected_columns]
    output.extend(result_data)
    output_csv = '\n'.join([','.join(row) for row in output])

    return output_csv

def process_csv_file(
    csv_file_path: str,
    selected_columns: str,
    row_filter_definitions: str
) -> str:
    """
    __Description__:
        A função ré responsável por ler os dados de um
    arquivo csv 'csv_file_path'
    __Returns__:
        A resposta da execução a função process_csv para processamento
    """
    with open(csv_file_path, 'r') as f:
        csv_data = f.read()
    return process_csv(csv_data, selected_columns, row_filter_definitions)

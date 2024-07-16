import ctypes

# Carrega a biblioteca compartilhada
libcsv = ctypes.CDLL('./libcsv.so')

# Define os tipos das funções
libcsv.process_csv.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
libcsv.process_csv_file.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]

# Exemplo de uso das funções
csv_data = "header1,header2\n1,2\n3,4"
selected_columns = "header1"
filter_definitions = "header2>2"

libcsv.process_csv(csv_data.encode(), selected_columns.encode(), filter_definitions.encode())

csv_file_path = "data.csv"
libcsv.process_csv_file(csv_file_path.encode(), selected_columns.encode(), filter_definitions.encode())

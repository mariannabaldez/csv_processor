import unittest
from io import StringIO
import csv
import os
from your_module import process_csv, process_csv_file

class TestCSVProcessing(unittest.TestCase):

    def setUp(self):
        """
        Configura os dados CSV de exemplo que
        serão usados em todos os testes.
        """

        self.csv_data = \
            """
            name,age,city
            Alice,30,New York
            Bob,25,Los Angeles
            Charlie,35,Chicago
            David,30,New York
            """

    def test_process_csv_no_filters_no_columns(self):
        """
        Testa a função process_csv sem filtros e sem
        seleção de colunas. Espera-se que todos os
        dados sejam retornados.
        """

        expected_output = \
            """
            name,age,city
            Alice,30,New York
            Bob,25,Los Angeles
            Charlie,35,Chicago
            David,30,New York
            """
        output = process_csv(self.csv_data, "", "")
        self.assertEqual(output, expected_output)

    def test_process_csv_select_columns(self):
        """
        Testa a seleção de colunas específicas
        """

        selected_columns = "name,city"
        expected_output = \
            """
            name,city
            Alice,New York
            Bob,Los Angeles
            Charlie,Chicago
            David,New York
            """
        output = process_csv(self.csv_data, selected_columns, "")
        self.assertEqual(output, expected_output)

    def test_process_csv_apply_filters(self):
        """
        Testa a aplicação de filtros nas linhas do CSV.
        """

        row_filter_definitions = "age=30"
        expected_output = \
            """
            name,age,city
            Alice,30,New York
            David,30,New York
            """
        output = process_csv(self.csv_data, "", row_filter_definitions)
        self.assertEqual(output, expected_output)

    def test_process_csv_select_columns_and_filters(self):
        """
        Testa a seleção de colunas junto com a aplicação de filtros.
        """

        selected_columns = "name,city"
        row_filter_definitions = "age=30"
        expected_output = \
            """
            name,city
            Alice,New York
            David,New York
            """
        output = process_csv(
            self.csv_data, selected_columns, row_filter_definitions
        )
        self.assertEqual(output, expected_output)

    def test_process_csv_file(self):
        """
        Testa a função process_csv_file lendo dados
        de um arquivo CSV. Cria um arquivo CSV temporário
        para o teste e o remove após a execução do teste.
        """

        csv_file_path = "test.csv"
        with open(csv_file_path, 'w') as f:
            f.write(self.csv_data)

        expected_output = \
            """
            name,age,city
            Alice,30,New York
            Bob,25,Los Angeles
            Charlie,35,Chicago
            David,30,New York
            """
        output = process_csv_file(csv_file_path, "", "")
        self.assertEqual(output, expected_output)

        os.remove(csv_file_path)

if __name__ == "__main__":
    unittest.main()

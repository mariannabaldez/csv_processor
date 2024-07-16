#include <stdio.h>
#include "libcsv.h"

int main() {
    const char csv[] = "header1,header2,header3\n1,2,3\n4,5,6\n7,8,9";
    processCsv(csv, "header1,header3", "header1>1\nheader3<9");

    const char csvFile[] = "data.csv";
    processCsvFile(csvFile, "col1,col3,col4,col7", "col1>l1c1\ncol3>l1c3");

    return 0;
}

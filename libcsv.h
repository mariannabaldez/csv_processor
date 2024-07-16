#include <Python.h>
#include <stdio.h>
#include <string.h>

void processCsv(
    const char csv[],
    const char selectedColumns[],
    const char rowFilterDefinitions[]
){
    Py_Initialize();

    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    pName = PyUnicode_DecodeFSDefault("csv_processor");

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "process_csv");

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_Pack(
                3,
                PyUnicode_FromString(csv),
                PyUnicode_FromString(selectedColumns),
                PyUnicode_FromString(rowFilterDefinitions)
            );

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != NULL) {
                printf("%s\n", PyUnicode_AsUTF8(pValue));
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
            }
        } else {
            if (PyErr_Occurred()) PyErr_Print();
        }

        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    Py_Finalize();
}


void processCsvFile(
    const char[]csvFilePath,
    const char selectedColumns[],
    const char rowFilterDefinitions[]
){
     Py_Initialize();

    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    pName = PyUnicode_DecodeFSDefault("csv_processor");

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "process_csv_file");

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_Pack(
                3,
                PyUnicode_FromString(csvFilePath),
                PyUnicode_FromString(selectedColumns),
                PyUnicode_FromString(rowFilterDefinitions)
            );

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != NULL) {
                printf("%s\n", PyUnicode_AsUTF8(pValue));
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
            }
        } else {
            if (PyErr_Occurred()) PyErr_Print();
        }

        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    Py_Finalize();
}

int main() {
    const char csv[] = "header1,header2,header3\n1,2,3\n4,5,6\n7,8,9";
    const char selectedColumns[] = "header1,header3";
    const char rowFilterDefinitions[] = "header1>1\nheader3<8";

    processCsv(csv, selectedColumns, rowFilterDefinitions);

    return 0;
}
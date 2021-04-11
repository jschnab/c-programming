#include <Python.h>

#include "../../c-library/data_types.h"
#include "../../c-library/dynamic_array.h"


static PyObject *method_quicksort(PyObject *self, PyObject *args) {
    PyObject *list;
    PyObject *item;
    int value;

    /* parse arguments */
    if (!PyArg_ParseTuple(args, "O", &list)) {
        return NULL;
    }

    /* check if argument is list */
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "argument must be list");
        return NULL;
    }

    /* iterate through list elements and build a dynamic array */
    DArray *array = darray_init(INT);
    for (Py_ssize_t i = 0; i < PyList_Size(list); i++) {
        item = PyList_GetItem(list, i);
        if (!PyLong_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "list item must be integer");
            return NULL;
        }
        value = (int)PyLong_AsLong(item);
        darray_append(array, &value);
    }

    /* sort dynamic array and put items back in input list */
    darray_quicksort(array, 0, array->count-1);
    for (int i = 0; i < array->count; i++) {
        item = PyLong_FromLong(((int *)array->items)[i]);
        PyList_SetItem(list, i, item);
    }

    darray_delete(array);

    Py_RETURN_NONE;
}


static PyMethodDef SortutilsMethods[] = {
    {"quicksort", method_quicksort, METH_VARARGS, "Return a sorted list of integers using quicksort"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef sortutilsmodule = {
    PyModuleDef_HEAD_INIT,
    "sortutils",
    "Sorting utilities",
    -1,
    SortutilsMethods
};


PyMODINIT_FUNC PyInit_sortutils(void) {
    return PyModule_Create(&sortutilsmodule);
}

from random import randint
from time import time

from sortutils import quicksort


def time_builtin_sort(array):
    """
    Calculate average sorting time of builtin sort function.
    """
    start = time()
    array.sort()
    stop = time()
    return stop - start


def time_quicksort(array):
    """
    Calculate average sorting time of home made quicksort.
    """
    start = time()
    quicksort(array)
    stop = time()
    return stop - start


def benchmark():
    repetitions = 1000
    builtin_times = []
    quicksort_times = []
    for _ in range(repetitions):
        array = [randint(-10000, 10000) for __ in range(10000)]
        builtin_times.append(time_builtin_sort(array.copy()))
        quicksort_times.append(time_quicksort(array.copy()))
    print(f"Builtin sort: {sum(builtin_times)/repetitions*1000:.3f} milliseconds")
    print(f"Quicksort: {sum(quicksort_times)/repetitions*1000:.3f} milliseconds")


def main():
    a = [randint(-100, 100) for _ in range(50)]
    quicksort(a)
    print(a)
    benchmark()


if __name__ == "__main__":
    main()

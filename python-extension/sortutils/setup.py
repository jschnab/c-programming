from distutils.core import setup, Extension


def main():
    setup(
        name="sortutils",
        version="1.0.0",
        description="Sorting utilities",
        ext_modules=[
            Extension(
                "sortutils",
                [
                    "sort.c",
                    "../../c-library/dynamic_array.c",
                ]
            )
        ],
    )


if __name__ == "__main__":
    main()

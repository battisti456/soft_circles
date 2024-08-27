from setuptools import setup, Extension

def main():
    setup(
        ext_modules = [
            Extension(
                "soft_circles.soft_circles_module",
                [
                    "lib/soft_circles_module.cpp"
                ],
                include_dirs=['lib'],
                extra_compile_args=["/std:c++20"]
            )
        ]
    )

if __name__ == "__main__":
    main()
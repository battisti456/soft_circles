from setuptools import setup, Extension

def main():
    setup(
        ext_modules = [
            Extension(
                "soft_circles.soft_circles_module",
                [
                    "lib/soft_circles_module.cpp"
                ],
                include_dirs=['lib']
            )
        ]
    )

if __name__ == "__main__":
    main()
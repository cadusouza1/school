def progressiva(f, x0, h):
    return (f(x0 + h) - f(x0)) / h


def regressiva(f, x0, h):
    return (f(x0) - f(x0 - h)) / h


def central(f, x0, h):
    return (f(x0 + h) - f(x0 - h)) / (2 * h)


if __name__ == "__main__":
    print(f"{progressiva(lambda x: x ** 2, 1, 0.1)=}")
    print(f"{regressiva(lambda x: x ** 2, 1, 0.1)=}")
    print(f"{central(lambda x: x ** 2, 1, 0.1)=}")

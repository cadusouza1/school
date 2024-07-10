def bissecao(f, a, b):
    if a - b < 0.01:
        return a

    c = (a + b) / 2
    if f(c) == 0:
        return c

    if f(c) * f(a) > 0:
        return bissecao(f, c, b)

    if f(c) * f(b) > 0:
        return bissecao(f, a, c)


def newton_raphson(f, x0): ...


def secante(f, x0, x1):
    if x1 - x0 < 0.01:
        return x1

    x2 = x1 - f(x1) * ((x1 - x0) / (f(x1) - f(x0)))
    return secante(f, x1, x2)


def falsa_posicao(f, a, b):
    if a - b < 0.01:
        return a

    c = a - f(a) * ((b - a) / (f(b) - f(a)))

    if f(c) == 0:
        return c

    if f(c) * f(a) > 0:
        return falsa_posicao(f, c, b)

    if f(c) * f(b) > 0:
        return falsa_posicao(f, a, c)


if __name__ == "__main__":
    print(f"{bissecao(lambda x: x ** 3 - x - 2, 1, 2)=}")
    print(f"{secante(lambda x: x ** 3 - x - 2, 1, 2)=}")
    print(f"{falsa_posicao(lambda x: x ** 3 - x - 2, 1, 2)=}")

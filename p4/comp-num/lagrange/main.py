# Retorna yi/Li
def lagrange_coefs(x: list[float], y: list[float]) -> list[float]:
    num_pontos = len(x)
    coefs = []

    for i in range(0, num_pontos):
        prod = 1
        for j in range(0, num_pontos):
            if i != j:
                prod *= x[i] - x[j]

        ci = y[i] / prod
        coefs.append(ci)

    return coefs


def polinomio_lagrange(t: float, x: list[float], coefs: list[float]) -> float:
    soma = 0

    for i in range(0, len(coefs)):
        prod = 1
        for j in range(0, len(coefs)):
            if i != j:
                prod *= t - x[j]

        prod *= coefs[i]
        soma += prod

    return soma


def lagrange(x, coefs):
    def f(t):
        return polinomio_lagrange(t, x, coefs)

    return f


if __name__ == "__main__":
    x = [1.0, 2.0, 4.0]
    y = [0, 3.0, -1.0]

    coefs = lagrange_coefs(x, y)
    poli = lagrange(x, coefs)
    for i in range(0, 10):
        print(f"poli({i}) = {poli(i)}")

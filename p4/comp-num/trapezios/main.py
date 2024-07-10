from math import pi, sin


def trapezios(f, a, b, n):
    h = (b - a) / n
    x = [a + i * h for i in range(0, n)]

    sum = f(x[0]) + f(x[n - 1])

    for i in range(1, n - 1):
        sum += 2 * f(x[i])

    return sum * h / 2


if __name__ == "__main__":
    print(trapezios(sin, 0, pi, 128))

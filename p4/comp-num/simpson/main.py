from math import pi, sin


def simpson(f, a, b, n):
    h = (b - a) / 2
    x = [a + i * h for i in range(0, n)]
    sum = f(x[0]) + f(x[n - 1])

    for i in range(1, n - 1):
        if i % 2 == 0:
            sum += 2 * f(x[i])
        else:
            sum += 4 * f(x[i])

    return sum * h / 3


if __name__ == "__main__":
    print(simpson(sin, 0, pi, 1024))

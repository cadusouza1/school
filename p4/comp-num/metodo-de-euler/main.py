def euler(f, x0, y0, h, n):
    for k in range(0, n):
        y0 += h * f(x0, y0)
        x0 += h

        print(f"x_{k + 1} = {x0}")
        print(f"y_{k + 1} = {y0}")
        print()


def f(x, y):
    return x + y


if __name__ == "__main__":
    x0 = 0
    y0 = 1
    h = 0.5
    n = 10

    euler(f, x0, y0, h, n)

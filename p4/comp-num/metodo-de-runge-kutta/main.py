def runge_kutta_2nd_order(f, x0, y0, h, n):
    x_vals = [x0]
    y_vals = [y0]

    for k in range(0, n):
        x = x_vals[-1]
        y = y_vals[-1]

        k1 = f(x, y)
        k2 = f(x + h, y + h * f(x, y))

        y_next = y + (h / 2) * (k1 + k2)
        x_next = x + h

        x_vals.append(x_next)
        y_vals.append(y_next)

        print(f"x_{k + 1} = {x_next}")
        print(f"y_{k + 1} = {y_next}")
        print()

    return x_vals, y_vals


def f(x, y):
    return (x**2 + 2 * y) / x


if __name__ == "__main__":
    x0 = 1
    y0 = 2
    h = 0.3
    n = 1

    runge_kutta_2nd_order(f, x0, y0, h, n)

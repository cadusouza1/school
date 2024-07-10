# Alunos: Gabriel Guimarães Henrici - 122137997
#         Carlos Eduardo de Souza - 122121661

import math

from matplotlib import pyplot as plt


def exact(t, y0, alpha):
    return y0 / ((1 - y0) * math.exp(-alpha * t) + y0)


def f(t, y, alpha):
    return alpha * y * (1 - y)


def euler_method(f, t0, y0, alpha, h, n):
    t_vals = [t0]
    y_vals = [y0]
    err_abs = [0]
    err_rel = [0]

    for _ in range(0, n):
        t = t_vals[-1]
        y = y_vals[-1]

        t_new = t + h
        y_new = y + h * f(t, y, alpha)

        t_vals.append(t_new)
        y_vals.append(y_new)

        y_exact = exact(t0, y0, alpha)
        abs_err = abs(y_exact - y_new)
        err_abs.append(abs_err)

        rel_err = abs_err / abs(y_exact)
        err_rel.append(rel_err)

    return t_vals, y_vals, err_abs, err_rel


t0 = 0
y0 = 10 / 10_000
h = 0.1
n = 10
alphas = [0.5, 1, 1.5]

# exact_solutions = [exact(t) for t in t_vals]

plt.figure(figsize=(15, 5))
for alpha in alphas:
    t_vals, y_vals, err_abs, err_rel = euler_method(
        f, t0, y0, alpha, h, n
    )

    exact_solutions = [exact(t, y0, alpha) for t in t_vals]

    plt.subplot(1, 3, 1)
    plt.plot(
        t_vals,
        exact_solutions,
        label=f"t x y(t_i) ({alpha=})",
    )
    plt.plot(t_vals, y_vals, label=f"t x y_i ({alpha=})")
    plt.legend()

    plt.xlabel("t")
    plt.ylabel("y(t)")
    plt.title(f"Soluções aproximadas e exatas")

    plt.subplot(1, 3, 2)
    plt.plot(t_vals, err_abs, label=f"t x E_abs ({alpha=})")
    plt.xlabel("t")
    plt.ylabel("E_abs")
    plt.title("Erro Absoluto")
    plt.legend()

    # Gráfico t x E_rel
    plt.subplot(1, 3, 3)
    plt.plot(t_vals, err_rel, label=f"t x E_rel ({alpha=})")
    plt.xlabel("t")
    plt.ylabel("E_rel")
    plt.title("Erro Relativo")
    plt.legend()

plt.tight_layout()
plt.show()

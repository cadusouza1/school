# Alunos: Gabriel Guimarães Henrici - 122137997
#         Carlos Eduardo de Souza - 122121661

import math

from matplotlib import pyplot as plt


def exact(t):
    return math.exp(t)


def f(t, y):
    return y


def euler_method(f, t0, y0, h, n):
    t_vals = [t0]
    y_vals = [y0]
    err_abs = [0]
    err_rel = [0]

    for _ in range(0, n):
        t = t_vals[-1]
        y = y_vals[-1]

        t_new = t + h
        y_new = y + h * f(t, y)

        t_vals.append(t_new)
        y_vals.append(y_new)

        y_exact = exact(t_new)
        abs_err = abs(y_exact - y_new)
        err_abs.append(abs_err)

        rel_err = abs_err / abs(y_exact)
        err_rel.append(rel_err)

    return t_vals, y_vals, err_abs, err_rel


t0 = 0
y0 = 1
h = 0.1
n = 10


t_vals, y_vals, err_abs, err_rel = list(
    euler_method(f, t0, y0, h, n)
)

exact_solutions = [exact(t) for t in t_vals]

print("Solução usando o método de Euler:")
for t, y, abs_err, rel_err in zip(
    t_vals, y_vals, err_abs, err_rel
):
    print(
        f"t = {t:.1f}, y = {y:.6f}, E_abs = {abs_err:.6f}, E_rel = {rel_err:6f}"
    )

plt.plot(t_vals, exact_solutions, label="t x y(t)")
plt.plot(
    t_vals,
    y_vals,
    label="t x y_i",
    linestyle="--",
    marker="o",
)
plt.plot(t_vals, err_abs, label="E_abs", color="red")
plt.plot(t_vals, err_rel, label="E_rel", color="pink")

plt.xlabel("t")
plt.ylabel("y")
plt.legend()
plt.show()

public class Atividade {
    public static void main(String[] args) {
        for (int i = 0; i < 15; i++) {
            System.out.println("Factorial(" + i + ") = " + factorial(i));
        }
    }

    public static int factorial(int n) {
        if (n == 1 || n == 0) {
            return 1;
        }

        return n * factorial(n - 1);
    }
}

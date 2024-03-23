import java.util.Scanner;

public class Atividade {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Nota 1: ");
        float nota1 = scanner.nextFloat();

        System.out.print("Nota 2: ");
        float nota2 = scanner.nextFloat();

        float media = (nota1 + nota2) / 2;

        if (media >= 7) {
            System.out.println("Aprovado com media: " + media);
        } else if (media >= 3) {
            System.out.println("Prova Final com media: " + media);
        } else {
            System.out.println("Reprovado com media: " + media);
        }

        scanner.close();
    }
}

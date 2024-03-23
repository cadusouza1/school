import java.util.Scanner;

class Atividade {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("R: ");
        int R = scanner.nextInt();
        System.out.print("r: ");
        int r = scanner.nextInt();

        System.out.println("A = " + 3.14159 * (R * R - r * r));
        scanner.close();
    }
}

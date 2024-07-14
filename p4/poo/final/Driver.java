import java.io.*;
import java.util.List;
import java.util.Scanner;

public class Driver {
    public static void main(String[] args) {
        Agenda agenda = Agenda.getInstance();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Escolha uma opção:");
            System.out.println("adicionar");
            System.out.println("remover");
            System.out.println("editar");
            System.out.println("buscar");
            System.out.println("listar");
            System.out.println("encerrar");

            System.out.print("Opção: ");
            String opcao = scanner.nextLine();
            System.out.println();

            MenuOption menuOption = MenuOption.fromString(opcao);

            if (menuOption == null) {
                System.out.println("Opção inválida.");
                continue;
            }

            switch (menuOption) {
                case ADICIONAR:
                    System.out.print("Nome: ");
                    String nomeAdicionar = scanner.nextLine();

                    System.out.print("Telefone: ");
                    String telefoneAdicionar = scanner.nextLine();

                    adicionarContato(agenda, nomeAdicionar, telefoneAdicionar);
                    break;

                case REMOVER:
                    System.out.print("Nome: ");
                    String nomeRemover = scanner.nextLine();

                    removerContato(agenda, nomeRemover);
                    break;

                case EDITAR:
                    System.out.print("Nome: ");
                    String nomeEditar = scanner.nextLine();

                    editarContato(agenda, scanner, nomeEditar);
                    break;

                case BUSCAR:
                    System.out.print("Nome: ");
                    String nomeBuscar = scanner.nextLine();

                    buscarContato(agenda, nomeBuscar);
                    break;

                case LISTAR:
                    listarContatos(agenda);
                    break;

                case ENCERRAR:
                    scanner.close();
                    return;

                default:
                    System.out.println("Opção inválida.");
                    break;
            }

            System.out.println();
        }
    }

    private static void adicionarContato(Agenda agenda, String nome, String telefone) {
        Contato contato = new Contato(nome, telefone);
        try {
            if (agenda.adicionar(contato)) {
                System.out.println("Contato adicionado com sucesso.");
            }
        } catch (ContatoDuplicadoException
                | AgendaCheiaException
                | NomeInvalidoException
                | TelefoneInvalidoException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void removerContato(Agenda agenda, String nome) {
        try {
            agenda.remover(nome);
            System.out.println("Contato removido com sucesso.");
        } catch (ContatoNaoEncontradoException | IOException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void editarContato(Agenda agenda, Scanner scanner, String nome) {
        List<Contato> contatosEncontrados = agenda.buscar(nome);

        if (contatosEncontrados.isEmpty()) {
            System.out.println("Nenhum contato encontrado.");
        } else {
            Contato contatoParaEditar = contatosEncontrados.get(0);

            System.out.print("Novo Nome (deixe vazio para manter): ");
            String novoNome = scanner.nextLine();

            System.out.print("Novo Telefone (deixe vazio para manter): ");
            String novoTelefone = scanner.nextLine();

            try {
                agenda.atualizar(contatoParaEditar, novoNome, novoTelefone);
                System.out.println("Contato atualizado com sucesso.");
            } catch (TelefoneInvalidoException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    private static void buscarContato(Agenda agenda, String nome) {
        List<Contato> resultados = agenda.buscar(nome);

        if (resultados.isEmpty()) {
            System.out.println("Nenhum contato encontrado.");
        } else {
            for (Contato c : resultados) {
                System.out.println(c);
            }
        }
    }

    private static void listarContatos(Agenda agenda) {
        List<Contato> todosContatos = agenda.contatos();

        if (todosContatos.isEmpty()) {
            System.out.println("Nenhum contato encontrado.");
        } else {
            for (Contato c : todosContatos) {
                System.out.println(c);
            }
        }
    }
}

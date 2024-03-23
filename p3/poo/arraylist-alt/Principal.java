import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

class Pessoa {
    private String nome;
    private int identificador;

    public Pessoa(String nome, int identificador) {
        this.nome = nome;
        this.identificador = identificador;
    }

    public String getNome() { return nome; }

    public int getIdentificador() { return identificador; }

    @Override
    public String toString() {
        return "ID: " + identificador + ", Nome: " + nome;
    }
}

class Evento {
    private String descricao;
    private int identificador;
    private List<Pessoa> pessoasRelacionadas;
    private int quantidadeDeVezes;

    public Evento(String descricao, int identificador) {
        this.descricao = descricao;
        this.identificador = identificador;
        this.pessoasRelacionadas = new ArrayList<>();
        this.quantidadeDeVezes = 0;
    }

    public String getDescricao() { return descricao; }

    public int getIdentificador() { return identificador; }

    public List<Pessoa> getPessoasRelacionadas() { return pessoasRelacionadas; }

    public int getQuantidadeDeVezes() { return quantidadeDeVezes; }

    public void incrementarQuantidadeDeVezes() { quantidadeDeVezes++; }

    @Override
    public String toString() {
        return "ID: " + identificador + ", Descrição: " + descricao +
            ", Quantidade de Vezes: " + quantidadeDeVezes;
    }
}

public class Principal {
    private static Evento[] eventos = new Evento[1024];
    private static int eventos_size = 1024;
    private static int eventos_last_index = 0;

    private static Pessoa[] pessoas = new Pessoa[1024];
    private static int pessoas_size = 1024;
    private static int pessoas_last_index = 0;

    private static Map<Integer, Evento> eventosMap = new HashMap<>();
    private static Map<Integer, Pessoa> pessoasMap = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            imprimirOrdemAtualDosEventos();

            System.out.println("\nMenu:");
            System.out.println("0: Sair");
            System.out.println("-1: Cadastrar Pessoa");
            System.out.println("-2: Cadastrar Evento");
            System.out.println("-3: Listar Pessoas com Eventos");
            System.out.println("Numero postivo: Ocorrencia de Evento");

            int opcao = scanner.nextInt();
            scanner.nextLine(); // Limpar o buffer de entrada

            switch (opcao) {
            case 0:
                System.out.println("Saindo do programa.");
                System.exit(0);
                break;
            case -1:
                cadastrarPessoa(scanner);
                break;
            case -2:
                cadastrarEvento(scanner);
                break;
            case -3:
                listarPessoasComEventos();
                break;
            default:
                if (opcao > 0) {
                    registrarOcorrenciaDeEvento(opcao);
                } else {
                    System.out.println("Opção inválida.");
                }
            }
        }
    }

    private static void cadastrarPessoa(Scanner scanner) {
        System.out.print("Digite o nome da pessoa: ");
        String nome = scanner.nextLine();
        System.out.print("Digite o identificador da pessoa: ");
        int identificador = scanner.nextInt();

        if (pessoasMap.containsKey(identificador)) {
            System.out.println("Já existe uma pessoa com esse identificador.");
            return;
        }

        Pessoa pessoa = new Pessoa(nome, identificador);
        pessoas[pessoas_last_index] = pessoa;
        pessoasMap.put(identificador, pessoa);

        pessoas_last_index++;

        System.out.println("Pessoa cadastrada com sucesso.");

        // Associar eventos à pessoa
        System.out.println("Deseja associar eventos a esta pessoa? (S/N)");
        String associarEventos = scanner.next();

        if (associarEventos.equalsIgnoreCase("S")) {
            associarEventosAPessoa(pessoa, scanner);
        }
    }

    private static void associarEventosAPessoa(Pessoa pessoa, Scanner scanner) {
        System.out.println("Lista de Eventos Disponíveis:");
        for (Evento evento : eventos) {
            if(!(evento == null)) {
                System.out.println(evento.getIdentificador() + ": " +
                                   evento.getDescricao());
            }
        }

        while (true) {
            System.out.println(
                "Digite o identificador do evento que deseja associar (ou 0 para sair): ");
            int identificadorEvento = scanner.nextInt();

            if (identificadorEvento == 0) {
                break;
            }

            Evento evento = eventosMap.get(identificadorEvento);

            if (evento == null) {
                System.out.println("Evento não encontrado.");
            } else if (evento.getPessoasRelacionadas().contains(pessoa)) {
                System.out.println(
                    "Essa pessoa já está associada a este evento.");
            } else {
                evento.getPessoasRelacionadas().add(pessoa);
                System.out.println("Evento associado com sucesso.");
            }
        }
    }

    private static void cadastrarEvento(Scanner scanner) {
        System.out.print("Digite a descrição do evento: ");
        String descricao = scanner.nextLine();
        System.out.print("Digite o identificador do evento: ");
        int identificador = scanner.nextInt();

        if (eventosMap.containsKey(identificador)) {
            System.out.println("Já existe um evento com esse identificador.");
            return;
        }

        Evento evento = new Evento(descricao, identificador);
        eventos[eventos_last_index] = evento;
        eventosMap.put(identificador, evento);

        eventos_last_index++;

        System.out.println("Evento cadastrado com sucesso.");
    }

    private static int encontrarIndexEvento(Evento[] eventos, Evento e) {
        for(int i = 0; i < eventos_size; i++) {
            if(eventos[i] == e) {
                return i;
            }
        }

        return -1;
    }

    private static void swap(Evento[] eventos, int i, int j) {
        Evento temp = eventos[i];
        eventos[i] = eventos[j];
        eventos[j] = eventos[i];
    }

    private static void registrarOcorrenciaDeEvento(int identificadorEvento) {
        Evento evento = eventosMap.get(identificadorEvento);

        if (evento == null) {
            System.out.println("Evento não encontrado.");
        } else {
            evento.incrementarQuantidadeDeVezes();
            swap(eventos, encontrarIndexEvento(eventos, evento), 0);
            System.out.println("Ocorrência de evento registrada.");
            imprimirOrdemAtualDosEventos();
        }
    }

    private static void listarPessoasComEventos() {
        for (Pessoa pessoa : pessoas) {
            if(pessoa != null) {
                System.out.println("\n" + pessoa.getNome() + ":");
                for (Evento evento : eventos) {
                    if(evento != null) {
                        if (evento.getPessoasRelacionadas().contains(pessoa)) {
                            System.out.println(evento);
                        }
                    }
                }
            }
        }
    }

    private static void imprimirOrdemAtualDosEventos() {
        System.out.println("\nOrdem Atual dos Eventos:");
        for (Evento evento : eventos) {
            if(!(evento == null)) {
                System.out.println(evento);
            }
        }
    }
}


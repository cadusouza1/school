import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Agenda {
    private static Agenda instance;
    private List<Contato> contatos;
    private static final int LIMITE = 1000;
    private static final String ARQUIVO = "contatos.txt";

    private Agenda() {
        contatos = new ArrayList<>();
        carregarContatos();
    }

    public static Agenda getInstance() {
        if (instance == null) {
            instance = new Agenda();
        }

        return instance;
    }

    public boolean adicionar(Contato c)
            throws ContatoDuplicadoException,
                    AgendaCheiaException,
                    NomeInvalidoException,
                    TelefoneInvalidoException {
        validarContato(c);

        if (contatos.size() >= LIMITE) {
            throw new AgendaCheiaException("A agenda está cheia.");
        }

        for (Contato contato : contatos) {
            if (contato.getTelefone().equals(c.getTelefone())) {
                throw new ContatoDuplicadoException("Contato duplicado.");
            }
        }

        contatos.add(c);
        salvarContatos();
        return true;
    }

    public void remover(String nomeContato) throws ContatoNaoEncontradoException, IOException {
        for (Contato contato : contatos) {
            if (contato.getNome().equals(nomeContato)) {
                contatos.remove(contato);
                salvarContatos();
                return;
            }
        }

        throw new ContatoNaoEncontradoException("Contato não encontrado: " + nomeContato);
    }

    public void atualizar(Contato c, String novoNome, String novoTel)
            throws TelefoneInvalidoException {
        if (novoNome != null && !novoNome.isEmpty()) {
            c.setNome(novoNome);
        }

        if (novoTel != null && !novoTel.isEmpty()) {
            validarTelefone(novoTel);
            c.setTelefone(novoTel);
        }

        salvarContatos();
    }

    public List<Contato> buscar(String nome) {
        List<Contato> resultado = new ArrayList<>();

        for (Contato contato : contatos) {
            if (contato.getNome().equalsIgnoreCase(nome)) {
                resultado.add(contato);
            }
        }

        return resultado;
    }

    public List<Contato> contatos() {
        return contatos;
    }

    private void salvarContatos() {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(ARQUIVO))) {
            for (Contato contato : contatos) {
                writer.write(contato.getNome() + "," + contato.getTelefone());
                writer.newLine();
            }
        } catch (IOException e) {
            System.err.println("Erro ao salvar contatos: " + e.getMessage());
        }
    }

    private void carregarContatos() {
        File file = new File(ARQUIVO);
        if (!file.exists()) {
            try {
                file.createNewFile();
            } catch (IOException e) {
                System.err.println("Erro ao criar o arquivo de contatos: " + e.getMessage());
                return;
            }
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String linha;

            while ((linha = reader.readLine()) != null) {
                String[] partes = linha.split(",");
                if (partes.length == 2) {
                    contatos.add(new Contato(partes[0], partes[1]));
                }
            }
        } catch (IOException e) {
            System.err.println("Erro ao carregar contatos: " + e.getMessage());
        }
    }

    private void validarContato(Contato c) throws NomeInvalidoException, TelefoneInvalidoException {
        validarNome(c.getNome());
        validarTelefone(c.getTelefone());
    }

    private void validarNome(String nome) throws NomeInvalidoException {
        if (nome == null || nome.isEmpty()) {
            throw new NomeInvalidoException("Nome inválido: O nome não pode ser vazio.");
        }
    }

    private void validarTelefone(String telefone) throws TelefoneInvalidoException {
        if (!telefone.matches("\\d{9,13}")) {
            throw new TelefoneInvalidoException(
                    "Telefone inválido: O número deve conter 9 ou 13 dígitos.");
        }
    }
}

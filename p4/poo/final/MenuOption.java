public enum MenuOption {
    ADICIONAR,
    REMOVER,
    EDITAR,
    BUSCAR,
    LISTAR,
    ENCERRAR;

    public static MenuOption fromString(String option) {
        try {
            return MenuOption.valueOf(option.toUpperCase());
        } catch (IllegalArgumentException e) {
            return null;
        }
    }
}

enum RobotState { STOP, GO_CENTER, CLOCKWISE, COUNTER_CW, ALTERNATING }

public class Robot {
    private GPS gps;
    private int id;
    private int DRE = 122121661;
    private String name = "Carlos Eduardo Carvalho de Souza";
    private RobotState state;
    private int centerL;
    private int centerC;

    public Robot(int id, GPS gps) {
        this.id = id;
        this.gps = gps;
        this.state = RobotState.GO_CENTER;

        // Indicates that the center is not known at this point
        this.centerL = -1;
        this.centerC = -1;
    }

    public Move MOVE() {
        int l = this.gps.getL(this.id);
        int c = this.gps.getC(this.id);
        Move move = Move.STOP;

        switch (this.state) {
        case ALTERNATING:
            move = move_alternating(l, c);
            break;
        case CLOCKWISE:
            move = move_clockwise(l, c);
            break;
        case COUNTER_CW:
            move = move_counter_cw(l, c);
            break;
        case GO_CENTER:
            move = move_center(l, c);
            break;
        case STOP:
            move = Move.STOP;
            break;
        default:
            move = Move.STOP;
            break;
        }

        return move;
    }

    private Move move_alternating(int l, int c) {
        Move m = Move.STOP;

        return m;
    }

    private Move move_clockwise(int l, int c) {
        Move m = Move.STOP;

        return m;
    }

    private Move move_counter_cw(int l, int c) {
        Move m = Move.STOP;

        return m;
    }

    private Move move_center(int l, int c) {
        Move m = Move.STOP;

        if (this.centerL == -1) {
            this.gps.move(Move.RIGHT);

            int newL = this.gps.getL(this.id);
            if (newL == l) {
                this.centerL = newL / 2;
            } else {
                this.gps.move(Move.LEFT);
            }
        }

        if (this.centerC == -1) {
            this.gps.move(Move.DOWN);

            int newC = this.gps.getC(this.id);
            if (newC == l) {
                this.centerC = newC / 2;
            } else {
                this.gps.move(Move.UP);
            }
        }

        return m;
    }

    public void go_center() { this.state = RobotState.GO_CENTER; }

    public void stop() { this.state = RobotState.STOP; }

    public void clockwise() { this.state = RobotState.CLOCKWISE; }

    public void counter_cw() { this.state = RobotState.COUNTER_CW; }

    public void alternating() { this.state = RobotState.ALTERNATING; }

    public void print() {
        System.out.println("Nome: " + this.name);
        System.out.println("DRE: " + this.DRE);
    }
}

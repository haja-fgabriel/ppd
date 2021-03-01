public class Message {
    private int rand;
    private int loc;

    public Message(int rand, int loc) {
        this.rand = rand;
        this.loc = loc;
    }

    public int getRand() {
        return rand;
    }

    public void setRand(int rand) {
        this.rand = rand;
    }

    public int getLoc() {
        return loc;
    }

    public void setLoc(int loc) {
        this.loc = loc;
    }
}

import java.util.ArrayList;
import java.util.List;

public class Catalog  {
    private List<Cursant> cursanti;

    public Catalog() {
        this.cursanti = new ArrayList<>();
    }

    public synchronized void addCursant(Cursant c) {
        cursanti.add(c);
    }

    public synchronized List<Cursant> getAll() {
        return cursanti;
    }
}

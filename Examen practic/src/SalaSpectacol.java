import java.util.logging.Logger;

public class SalaSpectacol {
    private final static Logger logger = Logger.getLogger(SalaSpectacol.class.getName());

    private char ocupat[][];
    private int nrRanduri;
    private int nrLocuri;

    public SalaSpectacol(int nrRanduri, int nrLocuri) {
        this.nrRanduri = nrRanduri;
        this.nrLocuri = nrLocuri;

        ocupat = new char[nrRanduri][];
        for (int i = 0; i < nrRanduri; i++) {
            ocupat[i] = new char[nrLocuri];
            for (int j = 0; j < nrLocuri; j++) {
                ocupat[i][j] = 'O';
            }
        }
    }

    public synchronized boolean adaugaLoc(int idRand, int idLoc) {
        logger.info("Adauga locul la randul " + idRand + ", locul " + idLoc);
        if (ocupat[idRand][idLoc] == 'O') {
            ocupat[idRand][idLoc] = 'X';
            logger.info("Locul este liber");
            return true;
        }
        return false;
    }

    public synchronized void iterare() {
        for (int i = 0; i < nrRanduri; i++) {
            for (int j = 0; j < nrLocuri; j++) {
                System.out.println("Randul " + i + ", locul " + j + " - " + ocupat[i][j]);
            }
        }
    }
}

public class Cursant {
    private int id;
    private float media;

    public Cursant(int id, float media) {
        this.id = id;
        this.media = media;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public float getMedia() {
        return media;
    }

    public void setMedia(float media) {
        this.media = media;
    }

    @Override
    public String toString() {
        return "Cursant{" +
                "id=" + id +
                ", media=" + media +
                '}';
    }
}

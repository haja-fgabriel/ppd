public class VectorAdd extends Thread {
    int[] a;
    int[] b;
    int[] c;
    int start, end;

    public VectorAdd(int[] a, int[] b, int[] c, int start, int end, int i) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.start = start;
        this.end = end;
        setName("Thread " + i);
    }

    @Override
    public void run() {
        System.out.println(getName());
        for (int i = start; i < end; i++) {
            c[i] = a[i] + b[i];
        }
    }
}

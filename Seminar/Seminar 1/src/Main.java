public class Main {
    public static void main(String[] args) {

        int a[] = {1,2,3,4,5,6,7,8,9,10};
        int b[] = {2,3,4,5,6,7,8,9,10,11};

        int result[] = new int[10];

        // number of threads
        int p = 8;
        Thread[] t = new VectorAdd[p];

        int start = 0, end = 0;
        int chunk = a.length / p;
        int rest = a.length % p;

        for (int i = 0; i < p; i++) {
            end = start + chunk;

            if (rest > 0) {
                rest--;
                end++;
            }

            t[i] = new VectorAdd(a, b, result, start, end, i);
            t[i].start();

            start = end;
        }

        for (int x : result) {
            System.out.printf("%d ", x);
        }

        System.out.print("\nMain thread\n");
    }
}

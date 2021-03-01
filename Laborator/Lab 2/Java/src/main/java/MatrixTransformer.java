import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

class MatrixTransformer implements Runnable {
    private float input[][];
    private float kernel[][];

    private int n;
    private int m;
    private int start;
    private int end;
    private CyclicBarrier barrier;

    public MatrixTransformer(float[][] input, float[][] kernel, int n, int m, int start, int end, CyclicBarrier barrier) {
        this.input = input;
        this.kernel = kernel;
        this.n = n;
        this.m = m;
        this.start = start;
        this.end = end;
        this.barrier = barrier;
    }

    @Override
    public void run() {
        int i = start / m, j = start % m;
        int imid = kernel.length / 2;
        int jmid = kernel[0].length / 2;
        float buffer[] = new float[end-start];

        for (int step = start; step < end; step++) {
            buffer[step-start] = 0.0f;
            for (int ii = 0; ii < kernel.length; ii++) {
                for (int jj = 0; jj < kernel[0].length; jj++) {
                    int k = i + ii - imid;
                    if (k < 0) k = 0;
                    if (k >= n) k = n - 1;
                    int l = j + jj - jmid;
                    if (l < 0) l = 0;
                    if (l >= m) l = m - 1;

                    buffer[step-start] += input[k][l] * kernel[ii][jj];
                }
            }

            j++;
            if (j == m) {
                j = 0;
                i++;
            }
        }
        i = start / m;
        j = start % m;

        if (barrier != null) {
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }

        for (int step = start; step < end; step++) {
            input[i][j] = buffer[step-start];

            j++;
            if (j == m) {
                j = 0;
                i++;
            }
        }
    }
}

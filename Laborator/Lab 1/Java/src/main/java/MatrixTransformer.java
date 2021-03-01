
class MatrixTransformer implements Runnable {
    private float input[][];
    private float output[][];
    private float kernel[][];

    private static float coeffs[][] = new float[][]{
            new float[]{1.0f / 9, 1.0f / 9, 1.0f / 9},
            new float[]{1.0f / 9, 1.0f / 9, 1.0f / 9},
            new float[]{1.0f / 9, 1.0f / 9, 1.0f / 9}
    };
    private int n;
    private int m;
    private int start;
    private int end;

    public MatrixTransformer(float[][] input, float[][] kernel, float[][] output, int n, int m, int start, int end) {
        this.input = input;
        this.output = output;
        this.kernel = kernel;
        this.n = n;
        this.m = m;
        this.start = start;
        this.end = end;
    }

    @Override
    public void run() {
        int i = start / m, j = start % m;
        int imid = kernel.length / 2;
        int jmid = kernel[0].length / 2;

        for (int step = start; step < end; step++) {
            output[i][j] = 0.0f;
            for (int ii = 0; ii < kernel.length; ii++) {
                for (int jj = 0; jj < kernel[0].length; jj++) {
                    int k = i + ii - imid;
                    if (k < 0) k = 0;
                    if (k >= n) k = n - 1;
                    int l = j + jj - jmid;
                    if (l < 0) l = 0;
                    if (l >= m) l = m - 1;

                    output[i][j] += input[k][l] * kernel[ii][jj];
                }
            }

            j++;
            if (j == m) {
                j = 0;
                i++;
            }
        }

    }
}
